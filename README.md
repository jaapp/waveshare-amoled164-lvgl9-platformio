# LVGL 9.x on Waveshare ESP32-S3-Touch-AMOLED-1.64 (PlatformIO)

This project demonstrates how to run **LVGL 9.x** with touch support on the **Waveshare ESP32-S3-Touch-AMOLED-1.64** board using **PlatformIO**. It includes a minimal FT3168 touch driver (via I²C) and a simple visualization (circle + crosshair lines) to show touch points clearly.

-----

## Features

- Display: **1.64" AMOLED (280×456), CO5300 driver IC**
- Touch: **FT3168 capacitive touch controller (I²C)**
- IMU: **QMI8658C 6-axis sensor**
- Flash: **W25Q128JVSI 128Mbit**
- Power: **MP1605GTF-Z buck converter + ETA6098 battery charger**
- GUI: **LVGL 9.x** with PlatformIO
- Example UI:
  - "Hello World" label
  - Circle + crosshair following finger touches

-----

## Project Structure

```
.
├── platformio.ini          # PlatformIO configuration
├── lv_conf.h               # LVGL configuration
├── src/
│   └── main.cpp            # Main application code
├── lib/                    # Local libraries (if needed)
├── include/                # Project headers
└── README.md
```

-----

## PlatformIO Configuration

The `platformio.ini` file is pre-configured with:

- **Board**: ESP32-S3 DevKit C1 (compatible)
- **Framework**: Arduino
- **CPU Frequency**: 240MHz
- **Flash Size**: 16MB
- **PSRAM**: Enabled
- **Libraries**: LVGL 9.x and Arduino_GFX (via Git)

Key settings:
- PSRAM enabled for graphics buffers
- Optimized build flags for ESP32-S3
- USB CDC debugging enabled
- Fast upload speed (921600 baud)

-----

## Dependencies

The project automatically handles dependencies via PlatformIO:

1. **LVGL 9.x**: Installed via PlatformIO registry (`lvgl/lvgl@^9.3.0`)
2. **Arduino_GFX**: Installed directly from GitHub (`https://github.com/moononournation/Arduino_GFX.git`)

No manual library installation required!

-----

## How to Build & Run

### Prerequisites
- [PlatformIO Core](https://platformio.org/install/cli) or [PlatformIO IDE](https://platformio.org/platformio-ide)
- ESP32-S3 board with USB-C cable

### Build and Upload
```bash
# Clone the repository
git clone <your-repo-url>
cd waveshare-amoled164-lvgl9-platformio

# Build the project
pio run

# Upload to board
pio run --target upload

# Monitor serial output
pio device monitor
```

### Using PlatformIO IDE
1. Open the project folder in VS Code with PlatformIO extension
2. Click "Build" (✓) in the PlatformIO toolbar
3. Click "Upload" (→) to flash the board
4. Click "Serial Monitor" to view output

-----

## Board Pin Usage

### Display (AMOLED, CO5300 driver)
- **GPIO9–14**: QSPI interface
  - GPIO9: OLED_CS
  - GPIO10: OLED_CLK
  - GPIO11: OLED_SIO0
  - GPIO12: OLED_SIO1
  - GPIO13: OLED_SIO2
  - GPIO14: OLED_SIO3
- **GPIO21**: OLED_RESET

### Touch Panel (FT3168, I²C)
- **GPIO47**: SDA
- **GPIO48**: SCL
- I²C Address: **0x38**

### Available for External Use
Safe GPIO pins for your project:
- **GPIO1, GPIO2, GPIO3**: ADC1 channels + Touch
- **GPIO5, GPIO6, GPIO7, GPIO8**: ADC1 channels + Touch
- **GPIO15, GPIO16**: ADC2 channels + XTAL_32K
- **GPIO17, GPIO18**: ADC2 channels
- **GPIO42**: Available
- **GPIO45**: Available

-----

## Touch Visualization

- **Circle**: shows precise touch coordinate
- **Crosshair lines**: span the entire width and height, intersecting at the touch point → useful if your finger blocks the view

-----

## Configuration Files

### `lv_conf.h`
LVGL configuration file located in project root. Key settings:
- Color depth: 16-bit (RGB565)
- Memory size: 64KB
- Widgets enabled: All standard widgets
- Themes: Default theme enabled
- Demo widgets: Enabled

### `platformio.ini`
PlatformIO configuration with ESP32-S3 specific settings:
- Board configuration matching Arduino IDE
- Automatic dependency management
- Build optimization flags
- Monitor and upload settings

-----

## Extending the Project

This project serves as a foundation for more complex applications:

1. **Add Sensors**: Use available GPIO pins for HX711, buttons, relays
2. **Custom UI**: Create professional interfaces with LVGL widgets
3. **Wireless**: Add WiFi/Bluetooth functionality
4. **Storage**: Use onboard SD card or SPIFFS
5. **Power Management**: Implement battery monitoring and sleep modes

-----

## Hardware Resources

### Board Documentation
- **Product Page**: [https://www.waveshare.com/esp32-s3-touch-amoled-1.64.htm](https://www.waveshare.com/esp32-s3-touch-amoled-1.64.htm)
- **Wiki/Documentation**: [https://www.waveshare.com/wiki/ESP32-S3-Touch-AMOLED-1.64](https://www.waveshare.com/wiki/ESP32-S3-Touch-AMOLED-1.64)

### Other Onboard Peripherals
- **USB**: GPIO19 (D-), GPIO20 (D+)
- **UART0**: GPIO43 (TX), GPIO44 (RX)
- **SD Card**: GPIO38–41 (CS, MOSI, MISO, CLK)
- **IMU (QMI8658C)**: GPIO47 (SDA), GPIO48 (SCL), GPIO46 (INT)
- **BOOT Button**: GPIO0
- **Power**:
  - 3V3 (regulated output)
  - 5V (USB/external)
  - BAT (battery input, charging supported)

