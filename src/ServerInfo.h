#ifndef SERVER_INFO_H
#define SERVER_INFO_H

#include <Arduino.h>

struct ServerInfo {
  String url;
  uint16_t port;
  String endpoint;
  String influx_api_key;
};

#endif /* SERVER_INFO_H */