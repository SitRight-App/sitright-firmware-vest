# compile.ps1 — Compila el sketch para Wokwi
# Requisito: arduino-cli instalado (winget install ArduinoSA.CLI)
#
# Primera vez (instalar placa y librerias):
#   .\compile.ps1 -setup
#
# Compilar:
#   .\compile.ps1

param([switch]$setup)

$FQBN = "esp32:esp32:esp32"
$SKETCH = "sitright_vest"
$BUILD_DIR = "build"

if ($setup) {
  Write-Host "Instalando placa ESP32..."
  arduino-cli core update-index
  arduino-cli core install esp32:esp32

  Write-Host "Instalando librerias..."
  arduino-cli lib install "Adafruit MPU6050"
  arduino-cli lib install "Adafruit Unified Sensor"
  arduino-cli lib install "ArduinoJson"
  Write-Host "Setup completado."
  exit
}

Write-Host "Compilando $SKETCH para $FQBN ..."
arduino-cli compile --fqbn $FQBN $SKETCH --output-dir $BUILD_DIR

if ($LASTEXITCODE -eq 0) {
  Write-Host ""
  Write-Host "Compilacion exitosa. Archivos generados en build/:"
  Get-ChildItem $BUILD_DIR | Select-Object Name, Length
  Write-Host ""
  Write-Host "Abre VS Code en esta carpeta y ejecuta F1 -> 'Wokwi: Start Simulator'"
} else {
  Write-Host "Error en la compilacion."
}
