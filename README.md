# 🌤️ ESP32 Weather Station & Clock

An ESP32-based desktop weather station with an SSD1306 OLED display. It fetches real-time weather data and 12-hour forecasts via the OpenWeatherMap API, synchronized with NTP precision time.

---

## 📸 Overview & Features

- **🕒 NTP Time Sync:** Automatically syncs real-time date, time, and day of the week over Wi-Fi (JST / UTC+9 configured).
- **🌡️ Live Weather:** Displays current weather conditions, temperature (°C), and relative humidity.
- **🔮 12-Hour Forecast:** Fetches and displays future weather predictions using OpenWeatherMap 5-day / 3-hour forecast data.
- **📺 Compact Display:** Clean UI layout built specifically for 128x64 SSD1306 OLED screens.

> 💡 **Tip:** Add a photo of your hardware setup right here!
> <img width="4000" height="3000" alt="IMG_20240707_141502" src="https://github.com/user-attachments/assets/910072d7-5720-4b11-9010-60f561a81d7f" />

---

## 🛠️ Hardware Requirements

- **ESP32 Development Board** (NodeMCU / WROOM-32)
- **SSD1306 OLED Display** (128x64 pixels, I2C interface)
- Jumper Wires & Breadboard

### Pin Connections (I2C)

| ESP32 Pin | SSD1306 OLED Pin |
| :--- | :--- |
| **3V3** | VCC |
| **GND** | GND |
| **GPIO 22** (SCL) | SCL |
| **GPIO 21** (SDA) | SDA |

---

## 📦 Required Arduino Libraries

Ensure you have installed the following libraries via the Arduino Library Manager:

1. **Adafruit SSD1306** & **Adafruit GFX Library**
2. **ArduinoJson** (Version 5.x)
3. **NTPClient** (by Fabrice Weinberg)
4. **Time** (by Michael Margolis / TimeLib)

---

## ⚙️ Setup & Configuration

1. **Clone the repository**
   ```bash
   git clone [https://github.com/Rabbit787/weather-station.git](https://github.com/Rabbit787/weather-station.git)
Open the sketch
Open code_with_NTPdisplay.ino in your Arduino IDE.

Configure Wi-Fi & API Credentials
Replace the placeholder values in the code with your network details and OpenWeatherMap API Key:

C++
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Change location query (q=chiba,jp) if needed
const String key     = "YOUR_OPENWEATHERMAP_API_KEY";
Upload to ESP32
Select your ESP32 board, select the correct COM port, and upload!

🤝 Contributing & Feedback
Feel free to open an Issue or submit a Pull Request if you have ideas to improve this project!
If you find this project helpful, don't forget to give it a ⭐️ star!

Created by Rabbit787
<img width="4000" height="3000" alt="IMG_20240707_141502" src="https://github.com/user-attachments/assets/910072d7-5720-4b11-9010-60f561a81d7f" />
<img width="4000" height="3000" alt="IMG_20240707_141511" src="https://github.com/user-attachments/assets/09c90eb0-b5aa-4763-8f3e-236c49417f53" />

This is the code of the weather station project using esp32 from rabbit787 domein website. 
I added the date and time to the ssd1306 screen on July 7th of 2024. 

Feel free to comment and share your ideas. Thank you. 

