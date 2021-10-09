/****************************************************************************************************************************
  BlynkSimpleESP8266_GSM_Async_WF.h
  For ESP8266 with GSM/GPRS and WiFi running simultaneously, with WiFi config portal

  Blynk_Async_GSM_Manager is a library, using AsyncWebServer instead of (ESP8266)WebServer to enable GSM/GPRS and WiFi 
  running simultaneously, with WiFi config portal.

  Based on and modified from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_Async_GSM_Manager
  Licensed under MIT license

  Original Blynk Library author:
  @file       BlynkSimpleESP8266.h
  @author     Volodymyr Shymanskyy
  @license    This project is released under the MIT License (MIT)
  @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
  @date       Oct 2016
  @brief
  
  Version: 1.2.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.10   K Hoang      25/08/2020 Initial coding to use (ESP)AsyncWebServer instead of (ESP8266)WebServer. 
                                   Bump up to v1.0.10 to sync with BlynkGSM_Manager v1.0.10.
  1.1.0    K Hoang      03/01/2021 Add support to ESP32 LittleFS. Remove possible compiler warnings. Update examples. Add MRD
  1.2.0    K Hoang      02/02/2021 Add functions to control Config Portal (CP) from software or Virtual Switches
                                   Fix CP and Dynamic Params bugs. To permit autoreset after timeout if DRD/MRD or forced CP
  1.2.1    K Hoang      13/08/2021 Update `platform.ini` and `library.json`
 *****************************************************************************************************************************/

#pragma once

#ifndef BlynkSimpleESP8266_GSM_ASYNC_WF
#define BlynkSimpleESP8266_GSM_ASYNC_WF

#ifndef ESP8266
  #error This code is intended to run on the ESP8266 platform! Please check your Tools->Board setting.
#endif

#if !defined(BLYNK_ASYNC_GSM_MANAGER_VERSION)
  #define BLYNK_ASYNC_GSM_MANAGER_VERSION       "Blynk_Async_GSM_Manager v1.2.1"
#endif

#define BLYNK_SEND_ATOMIC

// KH
#define BLYNK_TIMEOUT_MS     30000UL

#include <version.h>

#if ESP_SDK_VERSION_NUMBER < 0x020200
  #error Please update your ESP8266 Arduino Core
#endif

#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <Adapters/BlynkArduinoClient.h>
#include <ESP8266WiFi.h>

class BlynkWifi
  : public BlynkProtocol<BlynkArduinoClient>
{
    typedef BlynkProtocol<BlynkArduinoClient> Base;
  public:
    BlynkWifi(BlynkArduinoClient& transp)
      : Base(transp)
    {}

    void connectWiFi(const char* ssid, const char* pass)
    {
      BLYNK_LOG2(BLYNK_F("Con2:"), ssid);
      WiFi.mode(WIFI_STA);
      if (WiFi.status() != WL_CONNECTED) {
        if (pass && strlen(pass)) {
          WiFi.begin(ssid, pass);
        } else {
          WiFi.begin(ssid);
        }
      }
      while (WiFi.status() != WL_CONNECTED) {
        BlynkDelay(500);
      }
      BLYNK_LOG1(BLYNK_F("Conn2WiFi"));

      IPAddress myip = WiFi.localIP();
      BLYNK_LOG_IP("IP:", myip);
    }

    void config(const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
      Base::begin(auth);
      this->conn.begin(domain, port);
    }

    void config(const char* auth,
                IPAddress   ip,
                uint16_t    port = BLYNK_DEFAULT_PORT)
    {
      Base::begin(auth);
      this->conn.begin(ip, port);
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               const char* domain = BLYNK_DEFAULT_DOMAIN,
               uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
      connectWiFi(ssid, pass);
      config(auth, domain, port);
      while (this->connect() != true) {}
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               IPAddress   ip,
               uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
      connectWiFi(ssid, pass);
      config(auth, ip, port);
      while (this->connect() != true) {}
    }

};

static WiFiClient _blynkWifiClient;

// KH
static BlynkArduinoClient _blynkTransport_WF(_blynkWifiClient);
BlynkWifi Blynk_WF(_blynkTransport_WF);

#if defined(Blynk)
  #undef Blynk
  #define Blynk Blynk_WF
#endif
//

#include <BlynkWidgets.h>

#endif    // BlynkSimpleESP8266_GSM_ASYNC_WF
