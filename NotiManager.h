#ifndef Noti_Manager
#define Noti_Manager
#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiClientSecureAxTLS.h>
#elif defined(ESP32)
  #include <Wifi.h>
  #include <WiFiClientSecure.h>
#endif

class NotiManager {
    protected:
    String _token;

    public:
    NotiManager();
    bool isConnected();
    // virtual void addValue(const char* msg) {};
    // virtual void upload() {};
    virtual void notify(const char* msg) = 0;
};

class NotiTG : public NotiManager {
    protected:
    String _chatid;
    public:
    NotiTG(const char* token, const char* chatid);
    void notify(const char* msg);
};

class NotiLine : public NotiManager {
    public:
    NotiLine(const char* token);
    void notify(const char* msg);
};

class NotiTS : public NotiManager {
    protected:
    int    _index;    
    String _data;
    public:
    NotiTS(const char* token);
    void notify(const char* msg);
    void addValue(const char* msg);
    void upload();
};

#endif
