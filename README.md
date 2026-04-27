# sitright-firmware-vest

Firmware del chaleco inteligente **SitRight**. ESP32 + 3× MPU6050.

## Sobre el proyecto

Parte de la tesis **SitRight**: aplicación web con machine learning e IoT para mejorar la ergonomía postural en trabajadores sedentarios limeños mediante chaleco inteligente.

**Equipo:** Christopher Lecca, Mariano Ames (UPC — Ingeniería de Software).

## Hardware

- ESP32 DevKit V1
- 3× MPU6050 (cervical, dorsal, lumbar)
- Batería LiPo 3.7V 1000mAh + módulo cargador TP4056

## Qué hace

1. Lee los 3 MPU6050 vía I2C (multiplexado por pin AD0).
2. Se conecta a WiFi.
3. Envía las 9 lecturas (X, Y, Z × 3 sensores) + timestamp al backend vía HTTP POST cada 5 segundos.

## Simulación

El sketch corre igual en hardware real (Arduino IDE) que en el simulador Wokwi. Abre la carpeta en VS Code con la extensión Wokwi instalada y ejecuta `Wokwi: Start Simulator`.

## Relación con otros repos

- **sitright-backend-api** — recibe los datos que este firmware envía.
- **sitright-workspace** — contiene documentación, ADRs y backlog (privado).

## Licencia

Proyecto académico — UPC 2026.
