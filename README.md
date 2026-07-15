# Meteostanice⛅
My first major project

<p align="center">
  <img src="Photos/MeteostaniceNewSocialPreview.jpg" alt="Meteostanice Banner" width="100%">
</p>

### Description
#### **"Meteostanice"** is my first major project. It measures real-time weather data and sends it to my own Kodular app. It is based on Arduino, a BME280 sensor, a Bluetooth module, an RTC module for showing time, and an I2C LCD display.
---
### Technologies
![Arduino Uno](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)

*Hardware control, weather station logic, and reading values from the sensor.*

![C++](https://img.shields.io/badge/-C%2B%2B-00599C?style=for-the-badge&logo=C%2B%2B&logoColor=white)

*Programming language for Arduino.*

![Kodular](https://img.shields.io/badge/-Kodular-5B17B5?style=for-the-badge&logo=Kodular&logoColor=white)

*Platform for programming my app.*

![Supabase](https://img.shields.io/badge/-Supabase-3ECF8E?style=for-the-badge&logo=Supabase&logoColor=white)

*Database for uploading users' info(username, hashed password by SHA-256, email for communication and sending new versions of app, and full name).*

![Bluetooth HC-05 module](https://img.shields.io/badge/-Bluetooth%20HC--05-0082FC?style=for-the-badge&logo=Bluetooth&logoColor=white)

*Smart and easy way to send data from Arduino to Kodular app and back.*

![Bosch BME280](https://img.shields.io/badge/-Bosch%20BME280-EA0016?style=for-the-badge&logo=Bosch&logoColor=white)

*Great sensor which measures temperature, humidity and pressure.*

---

### Features
#### Part 1: Arduino
* Measuring temperature
* Measuring humidity
* Measuring pressure
* Calculating altitude
* Displaying real-time based on an RTC module
* Displaying data on the LCD display with I2C
* Sending data to my own Kodular app
#### ----------------------------------
#### Part 2: Kodular app
* Receiving data from Arduino via Bluetooth
* Displaying data in CardView
* User authentication with username and password
* Hashing password by SHA-256
* Cloud database powered by Supabase
* Admin mode
#### ----------------------------------
#### Part 3: 3D case for weather-station
##### *Still in progress*.
---
###  Hardware
* Arduino
* Bosch BME280 sensor
* LCD display with I2C
* BT HC-05 module
* RTC module
* Buttons for controlling the LCD display
---
### Photos

<details>
  <summary><b>Hardware Photos<b></summary>
  
  <p align="center">
    <img src="Photos/Hardware.jpg" alt="Hardware Setup" width="35%" />
    <img src="Photos/Hardware-LCD-Main.jpg" alt="LCD Display Detail" width="35%" />
    <img src="Photos/Hardware-Chantim.jpg" alt="Chantim Mode" width="35%" />
  </p>
</details>

<details>
  <summary><b>App Screenshots<b></summary>
  <p align="center">
    <img src="Photos/AppScreenshots/App-MainScreen.jpg" alt="Main screen" width="35%" />
    <img src="Photos/AppScreenshots/App-Afterpasswordentering-main.png" alt="Afterpasswordentering" width="35%" />
    <img src="Photos/AppScreenshots/App-APE-SuccessfullyConnected.png" alt="Successful Connection" width="35%" />
    <img src="Photos/AppScreenshots/App-Viewer-TestGH-New.jpg" alt="Viewer - Tester GitHub profile" width="35%" />
    <img src="Photos/AppScreenshots/App-UserManager-main.png" alt="User Manager" width="35%" />
  </p>
</details>

---
### Future ideas for version 2.0:
- [ ] Displaying history of weather data in charts

- [ ] Replacing Arduino Uno by Arduino Nano
---
## License
#### MIT License
---
### Author
##### Jan Opálka
###### GitHub: @jopalka
