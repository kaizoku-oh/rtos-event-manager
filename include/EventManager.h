#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#ifdef USE_USER_EVENTS
#include "UserEvents.h"
#else
#include "DefaultEvents.h"
#endif // USE_USER_EVENTS

#include "Service.h"

// Forward declaration to avoid circular dependencies between header files
class Service;

constexpr uint8_t MAX_SUBSCRIPTIONS_COUNT = 10;

class EventManager {
public:
  static EventManager& getInstance();
  void publish(Event event) const;
  void subscribe(Service* service, const Event events[], uint8_t count);
  void unsubscribe(Service* service);

private:
  EventManager();
  void lock() const;
  void unlock() const;

  struct Subscription {
    Service* service;
    const Event* events;
    uint8_t eventsCount;
  };
  Subscription subscriptions[MAX_SUBSCRIPTIONS_COUNT];
  uint8_t subscriptionsCount;
  SemaphoreHandle_t semaphoreHandle;
};

#endif // EVENT_MANAGER_H
