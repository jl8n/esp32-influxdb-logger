#ifndef SEND_DATA_H
#define SEND_DATA_H

#include <Arduino.h>
#include "ServerInfo.h"
#include "BME280_helper.h"


ServerInfo getServerInfo(const char* filename);
String constructJsonBody(SensorData data);
void sendData(SensorData data);


#endif /* SEND_DATA_H */
