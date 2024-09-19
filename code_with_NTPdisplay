//#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
//#include <time.h>
#include<Wire.h>             //
#include <WiFiUdp.h>
#include<Adafruit_GFX.h>     //ダウンロードしたライブラリをインクルード
#include<Adafruit_SSD1306.h>
#include <TimeLib.h>
//NTP関連
//Struct tm timeInfo;
//int now_hour;
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//#define JST     3600* 9
Adafruit_SSD1306 display(128, 64, &Wire, -1);

const char* ssid = "ENTER YOUR WIFI SSID";
const char* password =  "ENTER YOUR WIFI PASSWORD";

const String endpoint = "http://api.openweathermap.org/data/2.5/weather?q=chiba,jp&APPID=";
const String key = "ENTER YOUR OWN OPEN WEATHER MAY API KEY";
const String endpointone = "http://api.openweathermap.org/data/2.5/forecast?q=chiba,jp&APPID=";



// Array to store day names
const char* daysOfTheWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

// NTP server details
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600*9; // Set this to your timezone offset in seconds, 
// currently JST (UTC +9)

//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, updateInterval);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec);

void setup() {
  Serial.begin(115200);
  display.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);

  display.setTextColor(SSD1306_WHITE);


  int cursorPosition = 0;
  display.setCursor(0, 0);
  display.print("   Connecting");
  Serial.println("Connecting");
  display.display();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
    display.setCursor(0, 2);
    display.print(".");
    cursorPosition++;
    display.display();
  }
  display.clearDisplay();
  display.print("   Connected!");
  display.display();
  Serial.println("Connected to the WiFi network");
//  configTime( JST, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");
   // Initialize NTPClient to get time
  timeClient.begin();
}

void loop() {

    timeClient.update();

  // Get the current epoch time from the NTP client
  unsigned long epochTime = timeClient.getEpochTime();
  
  // Set the time in the TimeLib library
  setTime(epochTime);

          // Get the day of the week
  String dayOfWeek = String(daysOfTheWeek[weekday() - 1]);

  // Format the date and time
  String dateTime1 = String(year()) + "/" + String(month()) + "/" + String(day()) + "(" + dayOfWeek + ") " ;
  String dateTime2 = String(hour()) + ":" + String(minute());
  
  // Print the current time
  Serial.print("Year: ");
  Serial.print(year());
  Serial.print(" Month: ");
  Serial.print(month());
  Serial.print(" Day: ");
  Serial.print(day());
  Serial.print(" Hour: ");
  Serial.print(hour());
  Serial.print(" Minute: ");
  Serial.print(minute());
  Serial.print(" Second: ");
  Serial.println(second());
  
  if ((WiFi.status() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, endpoint + key); //URLを指定
    int httpCode = http.GET();  //GETリクエストを送信

    if (httpCode > 0) { //返答がある場合

      String payload = http.getString();  //返答（JSON形式）を取得
      Serial.println(httpCode);
      Serial.println(payload);
      const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + JSON_OBJECT_SIZE(13) + 470;
      DynamicJsonBuffer jsonBuffer(capacity);
      String json = payload;

      //jsonオブジェクトの作成


      JsonObject& weatherdata = jsonBuffer.parseObject(json);

      //パースが成功したかどうかを確認
      if (!weatherdata.success()) {
        Serial.println("parseObject() failed");
      }

      //各データを抜き出し
      const char* weather = weatherdata["weather"][0]["description"];
      const double temp = weatherdata["main"]["temp"];
      int humidity = weatherdata["main"]["humidity"];

      //LCDに表示
      display.clearDisplay();//画面を消去
      //天気を表示
      display.setCursor(0, 0);
      display.println("Current weather");
      display.println(weather);
      //気温を表示
      // String dateTime = String(year()) + "/" + String(month()) + "/" + String(day()) + " " + String(hour()) + ":" + String(minute());
//        // Get the day of the week
//  String dayOfWeek = String(daysOfTheWeek[weekday() - 1]);
//
//  // Format the date and time
//  String dateTime1 = String(year()) + "/" + String(month()) + "/" + String(day()) + "(" + dayOfWeek + ") " ;
//  String dateTime2 = String(hour()) + ":" + String(minute());

      String temp_str = String(temp - 273.15);
      display.print(temp_str);
      display.print((char)247);
      display.println("C");
      Serial.println(weather);
      Serial.println(temp_str);

      display.print(humidity);
      display.print("%");
      display.setCursor(0, 40);
      display.println(dateTime1);
      display.println(dateTime2);
    //  Serial.println(tm);
//       // Print the local time in a human-readable format
//{  Serial.print("Year: ");
//  Serial.println(1900 + tm->tm_year); // tm_year is the number of years since 1900
//  Serial.print("Month: ");
//  Serial.println(1 + tm->tm_mon); // tm_mon is 0-based (0 = January, ..., 11 = December)
//  Serial.print("Day: ");
//  Serial.println(tm->tm_mday);
//  Serial.print("Hour: ");
//  Serial.println(tm->tm_hour);
//  Serial.print("Minute: ");
//  Serial.println(tm->tm_min);
//  Serial.print("Second: ");
//  Serial.println(tm->tm_sec);

      display.display();
      delay(3000);
    }

    else {
      Serial.println("Error on HTTP request");
    }
  }
  if ((WiFi.status() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, endpointone + key); //URLを指定
    int httpCodeone = http.GET();  //GETリクエストを送信

    if (httpCodeone > 0) { //返答がある場合

      String payloadone = http.getString();  //返答（JSON形式）を取得
      Serial.println(httpCodeone);
      Serial.println(payloadone);

      const size_t capacity = 40 * JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(40) + 86 * JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 40 * JSON_OBJECT_SIZE(3) + 40 * JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 74 * JSON_OBJECT_SIZE(9) + 6 * JSON_OBJECT_SIZE(10) + 14380;
      DynamicJsonBuffer jsonBuffer(capacity);
      String json = payloadone;

      JsonObject& root = jsonBuffer.parseObject(json);
      int data_number = 4;
      if (!root.success()) {
        Serial.println("parseObject() failed");
      }
      if (root.success()) {
        const char* weatherf = root["list"][data_number]["weather"][0]["description"];
        const double tempf = root["list"][data_number]["main"]["temp"];

        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Forecast 12h later");
        display.println(weatherf);
//        Serial.println(now_hour);
        String temp_f = String(tempf - 273.15);
        display.print(temp_f);
        display.print((char)247);
        display.print("C");
        display.setCursor(0, 40);
        display.println(dateTime1);
        display.println(dateTime2);

        display.display();
        delay(3000);
      }

      http.end(); //Free the resources
    }
    delay(5000);
  }
}
