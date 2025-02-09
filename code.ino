
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include<Wire.h>             //
#include<Adafruit_GFX.h>     //ダウンロードしたライブラリをインクルード, include your libraries
#include<Adafruit_SSD1306.h>
#include <TimeLib.h> // this keeps you sane, lol jk, you can get the present time through internet. 
//NTP関連
struct tm timeInfo;
int now_hour; // this is presumably the hour passed from 0am. 24h system (maybe, im not sure)
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(128, 64, &Wire, -1); // oled setting up 

const char* ssid = "";/your wifi ssid
const char* password =  "";/pw

const String endpoint = ""; // your website url 
const String key = ""; // your api key for the open weather map. 
const String endpointone = "";

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

}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, endpoint + key); //URLを指定 , define url
    int httpCode = http.GET();  //GETリクエストを送信 send get request 

    if (httpCode > 0) { //返答がある場合,if there is a response

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

      String temp_str = String(temp - 273.15);
      display.print(temp_str);
      display.print((char)247);
      display.println("C");
      Serial.println(weather);
      Serial.println(temp_str);

      display.print(humidity);
      display.print("%");
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
      int data_number = now_hour / 3 + 4;
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
        
        String temp_f = String(tempf - 273.15);
        display.print(temp_f);
        display.print((char)247);
        display.print("C");
        display.display();
        delay(3000);
      }

      http.end(); //Free the resources
    }
    delay(5000);
  }
}
