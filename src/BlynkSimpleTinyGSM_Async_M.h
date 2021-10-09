/****************************************************************************************************************************
  BlynkSimpleTinyGSM_Async_M.h
  For ESP32/ESP8266 with GSM/GPRS and WiFi running simultaneously, with WiFi config portal

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

#ifndef BlynkSimpleTinyGSM_ASYNC_M_h
#define BlynkSimpleTinyGSM_ASYNC_M_h

#if !defined(BLYNK_ASYNC_GSM_MANAGER_VERSION)
  #define BLYNK_ASYNC_GSM_MANAGER_VERSION       "Blynk_Async_GSM_Manager v1.2.1"
#endif

#ifdef ESP32
  #include <Adapters/BlynkGsm_ESP32M_Async.h>
#else
  #ifdef ESP8266
    #include <Adapters/BlynkGsm_ESP8266M_Async.h>
  #else
    #error This code is intended to run on the ESP32 or ESP8266 platform! Please check your Tools->Board setting.
  #endif
#endif

static BlynkArduinoClient _blynkTransport;

BlynkSIM Blynk_GSM(_blynkTransport);

#define Blynk Blynk_GSM

#include <BlynkWidgets.h>

#endif    // BlynkSimpleTinyGSM_ASYNC_M_h
