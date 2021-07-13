#include "Watchy.h"

Watchy watchy;

void setup(){
  watchy.init();
  //Turn off my radios
  WiFi.mode(WIFI_OFF);
  btStop();
}

void loop(){}
