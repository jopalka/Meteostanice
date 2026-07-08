/*
Project: Meteostanice
Version: BETA
Author: Jan Opalka(jopalka)
Description: showing real-time weather data(temperature, humidity, pressure, altitude(calculated)) on an I2C LCD display and sending them to my own Kodular app.
Note: Because I am from Czechia, some prompts for LCD display are in Czech Language. All prompts are translated.
*/

//Initializing variables
int altitude;
int button;
int buttonchantim;
int buttonplus;
int buttonminus;
int buttonselect;
int pressure;
int temperature;
int humidity;
int buttonstate;
int buttonstatepre;//Previous buttonstate
int timestate;
int daymax;//Maximal amount of days in each month
int year;
int month;
int day;
int hour;
int minute;
int second;
char BluetoothClient;
String DateStr;
String TimeStr;
String DataString;
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SoftwareSerial.h>
#define BME280_ADRESA (0x76)//"BME280_ADRESA" is in Czech Language. Translation to English: "BME280_ADRESS"
#define SEALEVELPRESSURE_HPA 1013.25

Adafruit_BME280 bme;

LiquidCrystal_I2C lcd(0x27, 20, 4);

SoftwareSerial BTSerial(10, 11);
const long BT_BAUD_RATE = 9600;
const char separator = '|';
const char enter = '\n';
DS3231 rtc;
RTCDateTime datumCas;

byte stupen[8] = {//Because "°" is not legal symbol in "LCD world", I made my own symbol. "Stupen" is in Czech Language. Translation to English: degree
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
void setup() {
  BTSerial.begin(BT_BAUD_RATE);
  Serial.begin(9600);
  timestate = 1;
  buttonstate = 0;
  pinMode(13, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  bme.begin(BME280_ADRESA);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, stupen);
  rtc.begin();
  senload();
}

//I love loading screens, so I made my own one. 
void senload() {
  lcd.setCursor(0, 1);
  lcd.print("Nacitani sensoru...");//Prompt is in Czech Language. Translation to English: "Sensor Loading..."
  lcd.setCursor(8, 2);
  lcd.print("0%");
  delay(300);
  lcd.setCursor(8, 2);
  lcd.print("25%");
  delay(300);
  lcd.setCursor(8, 2);
  lcd.print("50%");
  delay(300);
  lcd.setCursor(8, 2);
  lcd.print("75%");
  delay(300);
  lcd.setCursor(7, 2);
  lcd.print("100%");
  delay(2000);
  lcd.clear();
  buttonstate = 0;
  timestate = 1;
}

void cas() {
  lcd.setCursor(0, 1);
  DateStr = "";
  if (day < 10) {
    DateStr = "0";
  }
  DateStr += day;
  DateStr += ".";
  if (month < 10) {
    DateStr += "0";
  }
  DateStr += month;
  DateStr += ".";
  DateStr += year;
  lcd.print(DateStr);
  lcd.setCursor(0, 2);
  TimeStr = "";
  if (hour < 10) {
    TimeStr = "0";
  }
  TimeStr += hour;
  TimeStr += ":";
  if (minute < 10) {
    TimeStr += "0";
  }
  TimeStr += minute;
  TimeStr += ":";
  if (second < 10) {
    TimeStr += "0";
  }
  TimeStr += second;
  lcd.print(TimeStr);
  delay(100);
}

void loop() {
  button = digitalRead(13);
  buttonplus = digitalRead(9);
  buttonminus = digitalRead(6);
  buttonselect = digitalRead(5);
  buttonchantim = digitalRead(12);
  int pressure = bme.readPressure() / 100.0F;  //Pa -- hPa
  int temperature = bme.readTemperature();     //Temperature in °C
  int humidity = bme.readHumidity();           //Humidity in %
  int altitude = 44330.0 * (1.0 - pow((bme.readPressure() / 100.0F) / SEALEVELPRESSURE_HPA, 0.1903));//Calculating altitude
  datumCas = rtc.getDateTime();
  //Year limits
  if (year < 2001) {
    year = 2099;
  }
  if (year > 2099) {
    year = 2001;
  }
  //Month limits
  if (month > 12) {
    month = 1;
  }
  if (month < 1) {
    month = 12;
  }
  //Day limits
  if ((month == 1) or (month == 3) or (month == 5) or (month == 7) or (month == 8) or (month == 10) or (month == 12)) {
    daymax = 31;
  }
  if ((month == 4) or (month == 6) or (month == 9) or (month == 11)) {
    daymax = 30;
  }
  if (month == 2) {
    if (year % 4 == 0) {
      daymax = 29;
    } else {
      daymax = 28;
    }
  }
  if (day > daymax) {
    day = 1;
  }
  if (day < 1) {
    day = daymax;
  }
  //Hour limits
  if (hour < 0) {
    hour = 23;
  }
  if (hour > 23) {
    hour = 0;
  }
  //Minute limits
  if (minute < 0) {
    minute = 59;
  }
  if (minute > 59) {
    minute = 0;
  }
  //Second limits
  if (second < 0) {
    second = 59;
  }
  if (second > 59) {
    second = 0;
  }

  if (buttonchantim == 0) {//Introducing "chantim" - CHANge TIMe » configuration RTC module
    buttonstate = 6;
    lcd.clear();
  }

  if ((button == 0) and (buttonstate == 6)) {
    buttonstate = 0;
    lcd.clear();
    delay(500);
  }

  //"Buttonstate" is an easy way to toggle between each values 
  if (buttonstate == 0) {
    if (buttonstatepre != 0) {//Keeping display srceen without lcd.clear(); all time.
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("Dnes je:");//Prompt is in Czech Language. Translation to English: "Today is:"
    lcd.setCursor(0, 1);
    DateStr = datumCas.day;
    DateStr += ".";
    DateStr += datumCas.month;
    DateStr += ".";
    DateStr += datumCas.year;
    lcd.print(DateStr);
    lcd.setCursor(0, 2);
    TimeStr = "";
    if (datumCas.hour < 10) {
      TimeStr = " ";
    }
    TimeStr += datumCas.hour;
    TimeStr += ":";
    if (datumCas.minute < 10) {
      TimeStr += "0";
    }
    TimeStr += datumCas.minute;
    TimeStr += ":";
    if (datumCas.second < 10) {
      TimeStr += "0";
    }
    TimeStr += datumCas.second;
    lcd.print(TimeStr);
    delay(100);
  }



  else if (buttonstate == 1) {
    if (buttonstatepre != 1) {
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("Teplota: ");//Prompt is in Czech Language. Translation to English: "Temperature: "
    lcd.setCursor(0, 1);
    lcd.print(temperature);
    lcd.print(" ");
    lcd.write(0);
    lcd.print("C");
    delay(100);
  }

  else if (buttonstate == 2) {
    if (buttonstatepre != 2) {
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("Vlhkost: ");//Prompt is in Czech Language. Translation to English: "Humidity: "
    lcd.setCursor(0, 1);
    lcd.print(humidity);
    lcd.print(" %    ");
    delay(100);
  }

  else if (buttonstate == 3) {
    if (buttonstatepre != 3) {
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("Tlak: ");//Prompt is in Czech Language. Translation to English: "Pressure: "
    lcd.setCursor(0, 1);
    lcd.print(pressure);
    lcd.print(" hPa");
    delay(100);
  }

  else if (buttonstate == 4) {
    if (buttonstatepre != 4) {
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("Nadmorska vyska:");//Prompt is in Czech Language. Translation to English: "Altitude: "
    lcd.setCursor(0, 1);
    lcd.print(altitude);
    lcd.print(" m.n.m.");
    delay(100);
  }

  if (buttonstate == 6) {
    lcd.setCursor(3, 1);
    lcd.print("Opravdu chcete");//Prompt is in Czech Language. Translation to English: "Do you really want to"
    lcd.setCursor(4, 2);
    lcd.print("zmenit cas?");//Prompt is in Czech Language. Translation to English: "change the time?"
    delay(50);
  }

  if ((buttonselect == 0) and (buttonstate == 6)) {//starting "chantim mode"
    year = datumCas.year;
    month = datumCas.month;
    day = datumCas.day;
    hour = datumCas.hour;
    minute = datumCas.minute;
    second = datumCas.second;
    buttonstate = 7;
    lcd.clear();
  }
  buttonstatepre = buttonstate;
  if (button == 0) {
    buttonstate = buttonstate + 1;
    delay(275);
  }

  if (buttonstate == 5) {
    buttonstate = 0;
  }

  if (buttonstate == 7) {//chantim proccess
    cas();
    if ((button == 0) and (buttonstate == 7)) {
      buttonstate = 0;
      buttonstatepre = 7;
      delay(500);
    }
    if ((buttonselect == 0) and (buttonstate == 7)) {
      timestate = timestate + 1;
      delay(100);
    }
    if (timestate == 8) {
      lcd.clear();
      lcd.setCursor(2, 1);
      lcd.print("Ukladani casu...");//Prompt is in Czech Language. Translation to English: "Saving time..."
      rtc.setDateTime(year, month, day, hour, minute, second);
      buttonstate = 0;
      timestate = 1;
      delay(3000);
    }

    if ((timestate == 2) and (buttonstate == 7)) {
      if (buttonplus == 0) {
        year = year + 1;
        delay(100);
      }

      else if (buttonminus == 0) {
        year = year - 1;
        delay(100);
      }
    }

    else if ((timestate == 3) and (buttonstate == 7)) {
      if (buttonplus == 0) {
        month = month + 1;
        delay(100);
      }

      else if (buttonminus == 0) {
        month = month - 1;
        delay(100);
      }
    }

    else if ((timestate == 4) and (buttonstate == 7)) {
      if (buttonplus == 0) {
        day = day + 1;
        delay(100);
      }

      else if (buttonminus == 0) {
        day = day - 1;
        delay(100);
      }
    }

    else if ((timestate == 5) and (buttonstate == 7)) {
      if (buttonplus == 0) {
        hour = hour + 1;
        delay(100);
      }

      else if (buttonminus == 0) {
        hour = hour - 1;
        delay(100);
      }
    }

    else if ((timestate == 6) and (buttonstate == 7)) {
      if (buttonplus == 0) {
        minute = minute + 1;
        delay(100);
      }

      else if (buttonminus == 0) {
        minute = minute - 1;
        delay(100);
      }
    }

    else if ((timestate == 7) and (buttonstate == 7)) {
      if (buttonplus == 0) {
        second = second + 1;
        delay(100);
      }

      else if (buttonminus == 0) {
        second = second - 1;
        delay(100);
      }
    }
  }

  if (BTSerial.available()) {//BT sending
    String command = BTSerial.readStringUntil('\n');  //Reading string
    command.trim();


    if (command == "Lze posilat informace") {//Prompt is in Czech Language. Translation to English: "It is possible to send data."


      String dataString = "";
      dataString += String(temperature);
      dataString += separator;
      dataString += String(humidity);
      dataString += separator;
      dataString += String(pressure);
      dataString += separator;
      dataString += String(altitude);
      dataString += enter;
      Serial.println(dataString);//If Bluetooth is not working, you can try show data in SerialMonitor.

      //Sending data by BT
      BTSerial.println(dataString);
    }
  }
}
