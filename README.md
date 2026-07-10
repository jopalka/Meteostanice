# Meteostanice⛅
My first major project

<p align="center">
  <img src="Photos/MeteostaniceSocialPreview.jpg" alt="Meteostanice Banner" width="100%">
</p>

### Description
#### **"Meteostanice"** is my first major project. It measures real-time weather data and sends it to my own Kodular app. It is based on Arduino, a BME280 sensor, a Bluetooth module, an RTC module for showing time, and an I2C LCD display.
---
### Technologies
![Arduino Uno](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)


![Kodular](https://img.shields.io/badge/-Kodular-5B17B5?style=for-the-badge&logo=Kodular&logoColor=white)


![Supabase](https://img.shields.io/badge/-Supabase-3ECF8E?style=for-the-badge&logo=Supabase&logoColor=white)


![Bluetooth HC-05 module](https://img.shields.io/badge/-Bluetooth-0082FC?style=for-the-badge&logo=Bluetooth&logoColor=white)


![Bosch BME280](https://img.shields.io/badge/-Bosch%20BME280-EA0016?style=for-the-badge&logo=Bosch&logoColor=white)

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
#### Hardware Photos
![Main Hardware Setup](Photos/HardwarePhotos/Hardware.jpg)
##### *Main hardware setup(I will add 3D case for it...)*
![LCD Display Detail](Photos/HardwarePhotos/Hardware-LCD-Main.jpg)
##### *LCD display - main screen(showing real-time)*
![Chantim Mode](Photos/HardwarePhotos/Hardware-Chantim.jpg)
##### *chantim(CHANging TIMe) in progress)*
---
#### App Screenshots
![Main screen](Photos/AppScreenshots/App-MainScreen.jpg)
##### *Main screen*
![Afterpasswordentering](Photos/AppScreenshots/App-Afterpasswordentering-main.png)
##### *Afterpasswordentering - my name for screen, which is coming AFTER PASSWORD ENTERING in Main Screen*
![Successful Connection](Photos/AppScreenshots/App-APE-SuccessfullyConnected.png)
##### *Displaying notifier with message of successful connection to HC-05.*
![Viewer - Tester GitHub profile](Photos/AppScreenshots/App-Viewer-TestGH-New.jpg)
##### *Displaying testing profile in Viewer - my screen for displaying selected user*
![User Manager](Photos/AppScreenshots/App-UserManager-main.png)
##### *Screenshot of UserManager - screen, which is supposed for adding new users*
---
### Author
##### Jan Opálka
###### GitHub: @jopalka
