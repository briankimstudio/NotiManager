# NotiManager

This is an ESP8266/ESP32 library for sending notificiation to Telegram, Line, ThingSpeak.

**Precondition**

WiFi is supposed to be connected before calling `notify()` method, otherwise, it won't send notification. Take a look `callWifi()` function for more detail about WiFi connection.

**How to use**

1. Include header file
```
#include "credentials.h"
#include "NotiManager.h"
```
2. Create an object with required credentials
```
NotiTG* tgNoti = new NotiTG(TG_TOKEN, TG_CHAT_ID);
```
3. Call notify method with message
```
tgNoti->notify("Hello world");
```

**Example code**

Example code consists of two files. credentials.h contains required credential information. notify_telegram_line_thingspeak.ino is a source code to send notification to Telegram, Line, and ThingSpeak.

credentials.h
```
/**
 * Telegram credentials
 */
#define TG_TOKEN   "telegram_token"
#define TG_CHAT_ID "telegram_chatid"

/**
 * LINE Notify credential
 */
#define LINE_TOKEN "line_token"

/**
 * Thingspeak credentials
 */
#define TS_KEY     "thingspeak_key"
#define TS_CHANNEL "thingspeak_channel"

/**
 * WiFi credentials
 */
#define WIFI_SSID "wifi_ssid"
#define WIFI_PASS "wifi_password"
```
notify_telegram_line_thingspeak.ino

For ThingSpeak, call `addValue()` method as much as possible to meet the number of field in channel. Then, call `upload()` method to send data to ThingSpeak cloud.

```
/**
 * Example for NotiManager library
 * 
 * notify_telegram_line_thingspeak.ino
 *
 * February , 2020  Brian Kim
 */

#include "credentials.h"
#include "NotiManager.h"

// For Telegram
NotiTG* tgNoti = new NotiTG(TG_TOKEN, TG_CHAT_ID);

// For Line
NotiLine* lnNoti = new NotiLine(LINE_TOKEN);

// For ThingSpeak
NotiTS* tsNoti = new NotiTS(TS_KEY);

void connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
}

void setup() {
    Serial.begin(115200);
    Serial.println("Hello");
    connectWifi();

    // Telegram
    tgNoti->notify("Hello world");

    // Line
    lnNoti->notify("Hello world");

    // ThingSpeak
    // Add values as much as it needs
    tsNoti->addValue("111");     // Add value
    tsNoti->addValue("432.234"); // Add value
    tsNoti->upload();            // Upload to ThingSpeak cloud
}

void loop() {

}
```
