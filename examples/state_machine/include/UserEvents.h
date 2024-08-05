#ifndef USER_EVENTS_H
#define USER_EVENTS_H

enum class EventType {
  EVENT_WIFI_CONNECTED = 0,
  EVENT_WIFI_DISCONNECTED,
  EVENT_BUTTON_PRESSED,
  EVENT_TIME_AVAILABLE,
  // Add other event types here
  MAX_EVENTS // Sentinel value for size of event list
};

#endif // USER_EVENTS_H
