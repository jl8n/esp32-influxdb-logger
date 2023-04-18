#ifndef WIFI_CONNECT_H
#define WIFI_CONNECT_H

#include <Arduino.h>


std::pair<String, String> getWifiCreds(const char* filename);
void connectToWifi(String ssid, String password);


#endif /* WIFI_CONNECT_H */
