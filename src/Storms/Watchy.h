#ifndef WATCHY_H
#define WATCHY_H

#include <Arduino.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <DS3232RTC.h>
#include <GxEPD2_BW.h>
#include <Wire.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "DSEG7_Classic_Bold_53.h"
#include "BLE.h"
#include "bma.h"
#include "config.h"    
#include "Seven_Segment10pt7b.h"
#include "DSEG7_Classic_Regular_15.h"
#include "DSEG7_Classic_Bold_25.h"
#include "DSEG7_Classic_Regular_39.h"
#include "icons.h"

typedef struct weatherData{
    int8_t temperature;
    int16_t weatherConditionCode;
}weatherData;

class Watchy {
    public:
        static DS3232RTC RTC;
        static GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display;
        tmElements_t currentTime;
    public:
        Watchy();
        void init(String datetime = "");
        void deepSleep();
        float getBatteryVoltage();
        void vibMotor(uint8_t intervalMs = 100, uint8_t length = 20);

        void handleButtonPress();
        void showMenu(byte menuIndex, bool partialRefresh);
        void showFastMenu(byte menuIndex);
        void showBattery();
        void showBuzz();
        void showAccelerometer();
        void showUpdateFW();
        void setTime();
        void showVerse();
        weatherData getWeatherData();
        void updateFWBegin();

        void showWatchFace(bool partialRefresh);
        virtual void drawWatchFace(); //override this method for different watch faces
        void drawTime();
        void drawDate();
        void drawSteps();
        void drawWeather();
        void drawBattery();

    private:
        void _rtcConfig(String datetime);    
        void _bmaConfig();
        static void _configModeCallback(WiFiManager *myWiFiManager);
        static uint16_t _readRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len);
        static uint16_t _writeRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len);
};

extern RTC_DATA_ATTR int guiState;
extern RTC_DATA_ATTR int menuIndex;
extern RTC_DATA_ATTR BMA423 sensor;
extern RTC_DATA_ATTR bool WIFI_CONFIGURED;
extern RTC_DATA_ATTR bool BLE_CONFIGURED;

#endif
