#include "NotiManager.h"

NotiManager::NotiManager() {
}

bool NotiManager::isConnected() {
  if (WiFi.status() != WL_CONNECTED)
    return false;
  else 
    return true;
}

NotiTG::NotiTG(const char* token, const char* chatid): NotiManager() {
    _token  = String(token);
    _chatid = String(chatid);
};

void NotiTG::notify(const char* msg) {
  WiFiClientSecure client;
  if (!isConnected()) {
    Serial.println("WIFI is not connected");
    return;
  }
#if defined(ESP8266)  
  client.setInsecure();
#endif  
  if (!client.connect("api.telegram.org", 443)) {
    Serial.println ("ERROR Connection failed");
    return;
  };
  
  String req = "GET /bot" + _token
             + "/sendmessage?chat_id=" + _chatid
             + "&text=" + String(msg)
             + " HTTP/1.1\r\n";
  req += "Host: api.telegram.org\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "\r\n";
  client.print(req);
  Serial.print(req);

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
    Serial.println(line);
  }    
};

NotiLine::NotiLine(const char* token): NotiManager() {
    _token = String(token);
};
void NotiLine::notify(const char* msg) {
 WiFiClientSecure client;
  if (!isConnected()) {
    Serial.println("WIFI is not connected");
    return;
  }

#if defined(ESP8266)  
  client.setInsecure();
#endif  

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println ("ERROR Connection failed");
    return;
  }
  String message = "message="+String(msg);
  String req = "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + _token + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(message.length()) + "\r\n";
  req += "\r\n";
  req += message;
  client.print(req);
  Serial.print(req);

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
//        delay(20000);
      break;
    }
    Serial.println(line);
  };
}

NotiTS::NotiTS(const char* token): NotiManager() {
  _data  = "";
  _index = 0;
  _token = String(token);
};
void NotiTS::notify(const char* msg) {
};

void NotiTS::addValue(const char* msg) {
  _index++;
  _data += "&field"+ String(_index) + "=" + String(msg);
  Serial.println(_data);
};

void NotiTS::upload() {
  WiFiClient client;

  _index = 0;
  if (!isConnected()) {
    Serial.println("WIFI is not connected");
    return;
  }

  if (!client.connect("api.thingspeak.com", 80)) {
    Serial.println ("ERROR Connection failed");
    return;
  }
//  char datetime_str[25];
  // Format : https://api.thingspeak.com/update.json?api_key=<write_api_key>&field1=123
  String getStr = "GET /update.json?api_key=" + _token
                + _data
                + " HTTP/1.0";
  Serial.println( getStr );
  client.println( getStr );
  client.println();

  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }
 
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
//        delay(20000);
      break;
    }
    Serial.println(line);
  };
};