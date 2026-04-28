# Simulación Wokwi — SitRight Vest

## Requisitos

- VS Code con extensión **Wokwi Simulator** instalada
- **Arduino CLI** instalado (`winget install ArduinoSA.CLI`)
- Backend corriendo localmente en `localhost:8000`

## Pasos

### 1. Primera vez — instalar placa y librerías

Desde la raíz del repo (`sitright-firmware-vest/`):

```powershell
.\compile.ps1 -setup
```

Instala `esp32:esp32`, `Adafruit MPU6050`, `Adafruit Unified Sensor`, `ArduinoJson`.

### 2. Levantar el backend local

```powershell
# En sitright-backend-api/
.\venv\Scripts\uvicorn src.main:app --port 8000
```

### 3. Compilar el sketch

```powershell
.\compile.ps1
```

Genera `build/sitright_vest.ino.elf` y `build/sitright_vest.ino.bin`.

### 4. Iniciar la simulación

Abre VS Code en la carpeta `sitright-firmware-vest/` y ejecuta:

```
F1 → Wokwi: Start Simulator
```

Wokwi usará el `wokwi.toml` en esta carpeta para cargar el diagrama y el firmware.

---

## Cómo funciona la red en Wokwi

El `wokwi.toml` tiene:

```toml
[[net.forward]]
from = "localhost:8000"
to = "localhost:8000"
```

Esto redirige las peticiones del ESP32 simulado a tu backend local. El chaleco enviará datos reales que aparecerán en el dashboard (`http://localhost:5173`).

---

## Para deploy a producción (Render)

Cambiar en `sitright_vest/config.h`:

```cpp
#define BACKEND_URL      "https://sitright-backend-api.onrender.com/api/v1/readings"
#define BACKEND_USE_HTTPS 1
```

---

## Diagrama

| Sensor | Bus I2C | Dirección |
|---|---|---|
| Cervical | Wire (GPIO 21/22) | 0x68 (AD0=GND) |
| Dorsal | Wire (GPIO 21/22) | 0x69 (AD0=3.3V) |
| Lumbar | Wire1 (GPIO 16/17) | 0x68 (AD0=GND) |
