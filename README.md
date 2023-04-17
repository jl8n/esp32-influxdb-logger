# esp32-influxdb-logger

A project that logs temperature, humidity, and pressure data from a BME280 sensor to an InfluxDB database using an ESP32 Microcontroller.

Written in C++ using the [Arduino core](https://github.com/espressif/arduino-esp32) with [PlatformIO](https://platformio.org/).

## Setup

A `config.json` file located in `data/` need to fit the following format:

```json
{
    "ssid": "<wifi_ssid>",
    "password": "<ssid_password>",
    "url": "<influxdb_ip)>",  // no http://
    "port": <influxdb_port>,
    "endpoint": "/api/v2/write?org=<org>&bucket=<bucket>",  // replace <org> and <bucket>
    "influx_api_key": "xxxxxxxxx"
}
```

### Filesystem

The ESP32 uses a custom filesystem called [SPIFFS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/spiffs.html), which doesn't work with standard C++ I/O.

The filesystem needs to be built using the current directory structure state. The PlatformIO tasks `Build Filesystem Image` followed by `Upload Filesystem Image` are necessary when adding or editing a non-`src/` file, such as `config.json`.

### Baud Rate

`115200` bits-per-second is used as the baud rate. This is set in `main.cpp` using `Serial.begin(115200)`, and also configured in `platformio.ini` to allow serial monitoring via VS Code with PlatformIO tooling.