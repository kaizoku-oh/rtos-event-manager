#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "Service.h"

// Forward declaration to avoid circular dependencies between header files
class Service;

enum class EventType {
  EVENT_WIFI_CONNECTED = 0,
  EVENT_WIFI_DISCONNECTED,
  EVENT_BUTTON_PRESSED,
  EVENT_TIME_AVAILABLE,
  // Add other event types here
  MAX_EVENTS // Sentinel value for size of event list
};

constexpr uint8_t MAX_SUBSCRIPTIONS_COUNT = 10;

class EventManager {
public:
  static EventManager& getInstance();
  void publish(EventType event) const;
  void subscribe(Service* service, const EventType events[], uint8_t count);
  void unsubscribe(Service* service);

private:
  EventManager();
  void lock() const;
  void unlock() const;

  struct Subscription {
    Service* service;
    const EventType* events;
    uint8_t eventsCount;
  };
  Subscription subscriptions[MAX_SUBSCRIPTIONS_COUNT];
  uint8_t subscriptionsCount;
  SemaphoreHandle_t semaphoreHandle;
};

#endif // EVENT_MANAGER_H
