## Blynk_Async_GSM_Manager

[![arduino-library-badge](https://www.ardu-badge.com/badge/Blynk_Async_GSM_Manager.svg?)](https://www.ardu-badge.com/Blynk_Async_GSM_Manager)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Blynk_Async_GSM_Manager.svg)](https://github.com/khoih-prog/Blynk_Async_GSM_Manager/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Blynk_Async_GSM_Manager/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Blynk_Async_GSM_Manager.svg)](http://github.com/khoih-prog/Blynk_Async_GSM_Manager/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.2.1](#releases-v121)
  * [Major Releases v1.2.0](#major-releases-v120)
  * [Major Releases v1.1.0](#major-releases-v110)
  * [Releases v1.0.10](#releases-v1010)

---
---

## Changelog

### Releases v1.2.1

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix

### Major Releases v1.2.0

1. To permit autoreset after configurable timeout if DRD/MRD or non-persistent forced-CP. Check [**Good new feature: Blynk.resetAndEnterConfigPortal() Thanks & question #27**](https://github.com/khoih-prog/Blynk_WM/issues/27)
2. Fix rare Config Portal bug not updating Config and dynamic Params data successfully in very noisy or weak WiFi situation
3. Add functions to control Config Portal from software or Virtual Switches. Check [How to trigger a Config Portal from code #25](https://github.com/khoih-prog/Blynk_WM/issues/25)
4. Add the new Virtual ConfigPortal SW feature to examples.
5. Disable the GSM/GPRS modem initialization which blocks the operation of Config Portal when using Config Portal.

### Major Releases v1.1.0

1. Add support to LittleFS for ESP32 using [LittleFS_esp32](https://github.com/lorol/LITTLEFS) Library
2. Add support to MultiDetectDetector. **MultiDetectDetector** feature to force Config Portal when configurable multi-reset is detected within predetermined time.
3. Clean-up all compiler warnings possible.
4. Add Table of Contents
5. Add Version String
6. Add MRD-related examples.

### Releases v1.0.10

1. Initial coding to use (ESP)AsyncWebServer instead of (ESP8266)WebServer. 
2. Bump up to v1.0.10 to sync with [BlynkGSM_Manager library v1.0.10](https://github.com/khoih-prog/BlynkGSM_Manager).


