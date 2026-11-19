# Monitoreo ambiental de laboratorios

Prototipo IoT de bajo costo que mide **temperatura** y **humedad relativa** de un laboratorio y envía los datos a un panel en línea mediante una conexión **cifrada (TLS) con verificación del certificado del servidor**.

Proyecto de la asignatura Sensórica, Universidad Surcolombiana. Autor: Camilo Andrés Pérez Manchola (19 de noviembre de 2026).

## Motivación

En la universidad, la revisión de las condiciones de un laboratorio depende de una persona y se hace de forma manual, puntual y subjetiva. No existe un registro histórico de temperatura ni de humedad.

Este prototipo **no reemplaza** el criterio del profesor ni del personal del laboratorio: aporta datos objetivos y continuos que respaldan la revisión manual.

## Arquitectura

```
DHT22  →  ESP32  →  Wi-Fi + TLS (WebSocket)  →  Nodrix en Cloudflare  →  Panel en tiempo real
```

- **Nodo de sensado:** ESP32-DevKitC (ESP32-WROOM-32) + sensor DHT22.
- **Nube y panel:** [Nodrix](https://github.com/decoded-cipher/nodrix) (código abierto, licencia MIT) desplegado en una cuenta propia de Cloudflare. Registra las variables `temperatura` y `humedad` automáticamente con el primer envío.
- **Firmware:** parte de [sensorica_blueprint](https://github.com/oscar88leonardo/sensorica_blueprint), adaptado a hardware real y a los dos canales del proyecto.

## Hardware

| Componente | Detalle |
|---|---|
| Microcontrolador | ESP32-DevKitC (ESP32-WROOM-32) |
| Sensor | DHT22 |
| Alimentación del sensor | Desde la propia placa; tierra compartida |
| Pin de datos | GPIO23 |
| Conexión al computador | USB (programación, alimentación y salida serie) |

## Estructura del firmware

| Archivo | Función |
|---|---|
| `config.h` | Pines, intervalo de publicación y rangos válidos de las lecturas |
| `sensors.cpp` | Lectura del DHT22 y validación de cada valor |
| `telemetry.cpp` | Conexión Wi-Fi, sincronización de hora, conexión a Nodrix y envío de datos |
| `secrets.h` | Credenciales y certificados (**excluido del control de versiones**) |
| `main.cpp` | Ciclo principal: lee y publica con la periodicidad configurada |

### Decisiones de diseño

- **Intervalo de 12 segundos.** El DHT22 admite como mínimo una lectura cada 2 s; un intervalo mayor cuida la cuota de la capa gratuita de Cloudflare.
- **Validación de lecturas.** Si el sensor devuelve un valor inválido se hace un único reintento; si persiste, ese canal se omite del envío para no mandar datos de relleno.
- **Rangos válidos.** Se descartan valores fuera de −40 a 80 °C (temperatura) y de 0 a 100 % (humedad).

## Requisitos

- [Visual Studio Code](https://code.visualstudio.com/) con la extensión [PlatformIO](https://platformio.org/)
- Una instancia de Nodrix desplegada en tu cuenta de Cloudflare
- Una red Wi-Fi de **2,4 GHz** sin portal cautivo ni autenticación por usuario

### Versiones utilizadas

| Componente | Versión |
|---|---|
| Plataforma Espressif 32 (PlatformIO) | 8.0.0 |
| Framework Arduino para ESP32 | 3.3.12 |
| Librería Nodrix | 0.1.2 |
| ArduinoJson | 7.4.3 |
| DHT sensor library (Adafruit) | 1.4.7 |
| Adafruit Unified Sensor | 1.1.15 |

## Puesta en marcha

1. Clona el repositorio y ábrelo con PlatformIO.
2. Crea el archivo `secrets.h` con tus credenciales Wi-Fi, los datos de tu instancia de Nodrix (incluido el token del proyecto) y los certificados raíz. **No lo subas al repositorio**: verifica que esté en `.gitignore`.
3. Conecta el DHT22 al GPIO23 del ESP32, con alimentación y tierra de la placa.
4. Compila y carga el firmware por USB.
5. Abre el monitor serie para ver las lecturas y revisa el panel de Nodrix: las variables aparecerán tras el primer envío.

## Seguridad

La primera versión cifraba el tráfico sin verificar el servidor. Para corregirlo:

- Se fijaron en el firmware los certificados raíz **ISRG Root X2** e **ISRG Root X1** (Let's Encrypt), que corresponden a la cadena del servidor del proyecto.
- Se fija la **raíz** y no el certificado del servidor, porque este se renueva cada pocos meses y la raíz permanece estable.
- El firmware **sincroniza la hora por NTP** antes de conectarse, porque validar un certificado requiere conocer la fecha.

Así, el token del proyecto queda protegido frente a un atacante que se interponga en la red Wi-Fi.

## Selección tecnológica

Se usaron matrices de selección ponderadas (puntajes de 1 a 5; total sobre 100).

| Componente | Elegido | Puntaje |
|---|---|---|
| Microcontrolador | ESP32-DevKitC | 91 / 100 |
| Sensor | DHT22 | 86 / 100 |
| Plataforma de datos | Nodrix | 88 / 100 |

Alternativas evaluadas: ESP32-S3, ESP32-C3, Raspberry Pi Pico W y Arduino Uno R4 WiFi (microcontrolador); AHT20 y BME280 (sensor); Blynk y Node-RED local (plataforma).

## Pruebas y resultados

- **Lectura base:** ~29,7 °C y ~82 % HR, coherentes con un día de lluvia reciente.
- **Exhalar sobre el sensor:** la humedad subió de ~82 % a 100 % en pocas lecturas y volvió a ~82 % en unos 40 s; la temperatura subió hasta 30,0 °C.
- **Objeto congelado y soplar contra él:** la temperatura bajó de 29,9 a 28,4 °C; la humedad subió a ~85 % y llegó a ~96 % con una nueva exhalación.
- **Lecturas inválidas intermitentes** tras las perturbaciones (causa probable: condensación sobre el sensor e intervalo de 2 s, en el límite del DHT22). Se resolvió con el intervalo de 12 s, el reintento y la omisión del canal.
- **Panel:** las variables se registraron automáticamente y respondieron a las perturbaciones.
- **TLS verificado:** tras fijar los certificados raíz, el nodo se conectó con verificación del servidor y los datos siguieron llegando al panel.

## Limitaciones

- **Sin validación metrológica:** no se comparó con un instrumento de referencia; la precisión absoluta, incluido el nivel de humedad base observado, está por determinar.
- **Certificados:** la fijación funciona mientras Cloudflare emita sus certificados desde esas autoridades; si cambiara, habría que actualizar el firmware.
- **Red:** el ESP32 solo usa Wi-Fi de 2,4 GHz y no funciona con portal cautivo o autenticación por usuario, lo que puede condicionar la instalación en la red de la universidad.
- **Alcance:** solo temperatura y humedad.
- **Madurez de Nodrix:** su primera versión estable se publicó en junio de 2026.

## Trabajo futuro

- Comparar el prototipo con un instrumento de referencia.
- Operación prolongada en el laboratorio.
- Ampliar a luminancia, ruido y disponibilidad del espacio.

## Referencias

1. *Prototipo IoT para el monitoreo de temperatura, humedad y ruido en laboratorios de calibración.* Populer. <https://journal.unimar-amni.ac.id/index.php/Populer/article/view/5572>
2. *IoT-Based Classroom Temperature Monitoring and Missing Data Prediction Using Raspberry Pi and ESP32.* Journal of Robotics and Control, 6(1), 2025. DOI: 10.18196/jrc.v6i1.24345
3. Azmee, N. A., Roslan, H. y Sari, S. (2025). *Real-Time IoT-Based Lecture Room Occupancy and Indoor Air Quality Monitoring System.* UTHM. <https://periodical.uthm.edu.my/index.php/peat/article/view/21265>
4. Hernández, W. y Cañas, N. (2024). *Sensing Classroom Temperature, Relative Humidity, Illuminance, CO2, and Noise…* Sensors, 24(16). DOI: 10.3390/s24165129
5. Rocha Ribeiro, R., Bauer, E. y Lameiras, R. (2021). *Higroterm: An open-source and low-cost temperature and humidity monitoring system for laboratory applications.* Inventions, 6(4), 84.
6. Nodrix: <https://github.com/decoded-cipher/nodrix> · Documentación: <https://nodrix.live/docs>
7. sensorica_blueprint: <https://github.com/oscar88leonardo/sensorica_blueprint>

## Licencia

[Completar: elige una licencia para el repositorio, por ejemplo MIT.]
