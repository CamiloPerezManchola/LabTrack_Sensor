# Dashboard: Monitoreo de Sensores

Este directorio contiene la definición exportada del dashboard creado en la nube **Nodrix** (Cloudflare Workers) a través del protocolo **Nodrix MCP**.

---

## Metadatos del Dashboard

- **ID del Dashboard:** `dsh_9oOUFs5IEnsH`
- **Proyecto:** `labtrack` (`prj_0gE5nb29t9EJ`)
- **Nombre:** Monitoreo de Laboratorios

## Disposición de Widgets (Grid de 16 Columnas)

```
+---------------------------------------------------+
|        FILA 1: TARJETAS DE VALOR INSTANTÁNEO      |
|     [Temp: °C] (w=5)   | [Humedad: % HR] (w=6)    |
+---------------------------------------------------+
|        FILA 2: INDICADORES RADIALES (GAUGES)      |
| [Gauge 0-100 °C] (w=5) | [Gauge 0-100 % HR] (w=6) |
+---------------------------------------------------+
|        FILA 3: GRÁFICO HISTÓRICO MULTIVARIABLE    |
|        [Líneas de Temperatura, Humedad] (w=16)    |
+---------------------------------------------------+
```

### Detalle de Widgets

| ID | Tipo | Variable | Rango / Unidad | Propósito |
|---|---|---|---|---|
| `wid_Dr2xLXvzSZzA` | `iot-value` | `temperatura` | °C | Lectura numérica instantánea |
| `wid_Q4Clm23L0iw6` | `iot-value` | `humedad` | % HR | Lectura numérica instantánea |
| `wid_zYPhsLLTmH6Z` | `iot-gauge` | `temperatura` | 0 a 100 °C | Dial analógico con aguja |
| `wid_3j4U5BKHiLtv` | `iot-gauge` | `humedad` | 0 a 100 % HR | Dial analógico con aguja |
| `wid_Ov2M8Hn9cPCi` | `iot-chart` | `temperatura`, `humedad` | Ventana 24 hora | Curvas temporales continuas |
