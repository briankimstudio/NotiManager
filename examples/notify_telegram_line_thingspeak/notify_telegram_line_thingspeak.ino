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