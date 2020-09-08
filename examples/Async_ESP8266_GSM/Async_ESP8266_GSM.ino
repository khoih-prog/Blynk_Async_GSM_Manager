/****************************************************************************************************************************
  Async_ESP8266_GSM.ino
  For ESP8266 boards to run GSM/GPRS and WiFi simultaneously, using config portal feature
  
  Blynk_Async_GSM_Manager is a library, using AsyncWebServer instead of (ESP8266)WebServer to enable GSM/GPRS and WiFi 
  running simultaneously, with WiFi config portal.
  
  Based on and modified from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/Blynk_Async_GSM_Manager
  Licensed under MIT license
  Version: 1.0.10
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.6   K Hoang      25/08/2020 Initial coding to use (ESP)AsyncWebServer instead of (ESP8266)WebServer. 
                                  Bump up to v1.0.10 to sync with BlynkGSM_Manager v1.0.10.
 *****************************************************************************************************************************/

#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"


void heartBeatPrint(void)
{
  static int num = 1;

  if (Blynk_WF.connected())
  {
    Serial.print(F("B"));
  }
  else
  {
    Serial.print(F("F"));
  }

  if (Blynk_GSM.connected())
  {
    Serial.print(F("G"));
  }
  else
  {
    Serial.print(F("F"));
  }

  if (num == 40)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     60000L

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    // report status to Blynk
    heartBeatPrint();

    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

bool valid_apn = false;
bool GSM_CONNECT_OK = false;

void setup()
{
  // Set console baud rate
  SerialMon.begin(115200);
  while (!SerialMon);

  SerialMon.print(F("\nStart Async_ESP8266-WIFI-GSM using "));
  SerialMon.print(CurrentFileFS);
  SerialMon.println(" on " + String(ARDUINO_BOARD));
  
  // Set-up modem reset, enable, power pins
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);

  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);

  SerialMon.println(F("Set GSM module baud rate"));

  // Set GSM module baud rate
  SerialAT.begin(115200);

  delay(3000);

  Serial.println(F("Use WiFi to connect Blynk"));

#if USE_BLYNK_WM

  // Set config portal SSID and Password
  Blynk_WF.setConfigPortal("TestPortal-ESP8266", "TestPortalPass");
    
  // Use configurable AP IP, instead of default IP 192.168.4.1
  Blynk_WF.setConfigPortalIP(IPAddress(192, 168, 232, 1));
  // Set config portal channel, default = 1. Use 0 => random channel from 1-12 to avoid conflict
  Blynk_WF.setConfigPortalChannel(0);

  // Select either one of these to set static IP + DNS
  Blynk_WF.setSTAStaticIPConfig(IPAddress(192, 168, 2, 232), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0));
  //Blynk_WF.setSTAStaticIPConfig(IPAddress(192, 168, 2, 232), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0),
  //                           IPAddress(192, 168, 2, 1), IPAddress(8, 8, 8, 8));
  //Blynk_WF.setSTAStaticIPConfig(IPAddress(192, 168, 2, 232), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0),
  //                           IPAddress(4, 4, 4, 4), IPAddress(8, 8, 8, 8));
  
  // Use this to default DHCP hostname to ESP8266-XXXXXX or ESP32-XXXXXX
  //Blynk_WF.begin();
  // Use this to personalize DHCP hostname (RFC952 conformed)
  // 24 chars max,- only a..z A..Z 0..9 '-' and no '-' as last char
  Blynk_WF.begin("ESP8266-WiFi-GSM");
  
#else
  Blynk_WF.begin(wifi_blynk_tok, ssid, pass, blynk_server, BLYNK_HARDWARE_PORT);

  Blynk_GSM.config(modem, gsm_blynk_tok, blynk_server, BLYNK_HARDWARE_PORT);
  GSM_CONNECT_OK = Blynk_GSM.connectNetwork(apn, gprsUser, gprsPass);

  if (GSM_CONNECT_OK)
    Blynk_GSM.connect();
#endif

#if USE_BLYNK_WM
  Blynk_WF_Configuration localBlynkGSM_ESP8266_config;

  Blynk_WF.getFullConfigData(&localBlynkGSM_ESP8266_config);

  Serial.print(F("gprs apn = "));
  Serial.println(localBlynkGSM_ESP8266_config.apn);

  if (String(localBlynkGSM_ESP8266_config.apn) == NO_CONFIG)
  {
    Serial.println(F("No valid stored apn. Must run WiFi to Open config portal"));
    valid_apn = false;
  }
  else
  {
    valid_apn = true;

    for (int index = 0; index < NUM_BLYNK_CREDENTIALS; index++)
    {
      Blynk_GSM.config(modem, localBlynkGSM_ESP8266_config.Blynk_Creds[index].gsm_blynk_token,
                       localBlynkGSM_ESP8266_config.Blynk_Creds[index].blynk_server, localBlynkGSM_ESP8266_config.blynk_port);

      GSM_CONNECT_OK = Blynk_GSM.connectNetwork(localBlynkGSM_ESP8266_config.apn, localBlynkGSM_ESP8266_config.gprsUser,
                       localBlynkGSM_ESP8266_config.gprsPass);

      if (GSM_CONNECT_OK)
      {
        if ( Blynk_GSM.connect() == true )
          break;
      }
    }
  }
#endif
}

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
void displayCredentials(void)
{
  Serial.println("\nYour stored Credentials :");

  for (int i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
  }
}
#endif

void loop()
{
  Blynk_WF.run();

#if USE_BLYNK_WM
  if (valid_apn)
#endif
  {
    if (GSM_CONNECT_OK)
      Blynk_GSM.run();
  }

  check_status();

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
#endif
}