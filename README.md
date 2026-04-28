# sitright-firmware-vest

Firmware del chaleco inteligente **SitRight**. ESP32 DevKit V1 + 3× MPU6050.  
Lee posturas cada 5 segundos y las envía al backend vía HTTPS.

## Hardware

| Componente | Función |
|---|---|
| ESP32 DevKit V1 | Microcontrolador WiFi |
| MPU6050 cervical | Sensor acelerómetro (I2C bus 1, addr 0x68) |
| MPU6050 dorsal | Sensor acelerómetro (I2C bus 1, addr 0x69) |
| MPU6050 lumbar | Sensor acelerómetro (I2C bus 2, addr 0x68) |
| LiPo 3.7V 1000mAh | Batería |

## Simular en Wokwi.com (recomendado — sin instalaciones)

> El backend debe estar desplegado en Render antes de simular.

1. Ir a **[wokwi.com](https://wokwi.com)** → New Project → **ESP32**
2. Reemplazar `diagram.json` con el contenido de [`wokwi/diagram.json`](wokwi/diagram.json)
3. Crear los siguientes archivos en el editor (botón `+`):

| Archivo | Contenido |
|---|---|
| `sitright_vest.ino` | `sitright_vest/sitright_vest.ino` |
| `config.h` | `sitright_vest/config.h` |
| `sensors.h` | `sitright_vest/sensors.h` |
| `sensors.cpp` | `sitright_vest/sensors.cpp` |
| `network.h` | `sitright_vest/network.h` |
| `network.cpp` | `sitright_vest/network.cpp` |
| `battery.h` | `sitright_vest/battery.h` |
| `battery.cpp` | `sitright_vest/battery.cpp` |
| `libraries.txt` | `wokwi/libraries.txt` |

4. Verificar que en `config.h` la URL apunta al backend de Render:
   ```cpp
   #define BACKEND_URL "https://sitright-backend-api.onrender.com/api/v1/readings"
   #define BACKEND_USE_HTTPS 1
   ```
5. Click **▶ Run** — el simulador compila y arranca automáticamente.

**Lo que verás en el Serial Monitor:**
```
[SITRIGHT] Iniciando chaleco SitRight...
[SENSORS] OK: 3x MPU6050 inicializados
[WIFI] Conectando a Wokwi-GUEST......
[WIFI] Conectado. IP: 10.10.0.2
[NET] Enviando: {"vest_id":"vest-wokwi-001","cervical":[...],"battery_percent":85}
[NET] Respuesta 201: {"id":"...","posture_class":"adequate","confidence":0.91}
```

Cada 5 segundos el ESP32 simulado envía datos reales al backend en Render.  
El dashboard en Netlify se actualiza en tiempo real.

## Cómo funciona la red en Wokwi.com

El SSID `Wokwi-GUEST` es la WiFi virtual de Wokwi — provee acceso real a internet  
a través de los servidores de Wokwi. El ESP32 simulado puede hacer peticiones HTTPS  
a cualquier URL pública igual que el hardware real.

## Simular localmente con VS Code (opcional)

Ver [`wokwi/README.md`](wokwi/README.md) para instrucciones con la extensión Wokwi.

## Relación con otros repos

- **sitright-backend-api** — recibe `POST /api/v1/readings` desde este firmware.
- **sitright-workspace** — documentación, ADRs y backlog (privado).

## Licencia

Proyecto académico — UPC 2026.
