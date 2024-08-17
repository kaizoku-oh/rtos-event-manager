#ifndef USER_EVENTS_H
#define USER_EVENTS_H

enum class Event {
  WIFI_CONNECTED = 0,
  WIFI_DISCONNECTED,
  BUTTON_PRESSED,
  TIME_AVAILABLE,
  // Add other event types here
  MAX_EVENTS // Sentinel value for size of event list
};

#endif // USER_EVENTS_H
