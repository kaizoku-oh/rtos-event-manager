#include "EventManager.h"
#include "Service.h"
#include <esp_log.h>

#define TAG "[EventManager]"

EventManager& EventManager::getInstance() {
  static EventManager instance;
  return instance;
}

EventManager::EventManager() : subscriptionsCount(0) {
  ESP_LOGD(TAG, "EventManager object is created");
  vSemaphoreCreateBinary(this->semaphoreHandle);
}

void EventManager::lock() const {
  if (xPortInIsrContext()) {
    xSemaphoreTakeFromISR(this->semaphoreHandle, nullptr);
  } else {
    xSemaphoreTake(this->semaphoreHandle, portMAX_DELAY);
  }
}

void EventManager::unlock() const {
  if (xPortInIsrContext()) {
    xSemaphoreGiveFromISR(this->semaphoreHandle, nullptr);
  } else {
    xSemaphoreGive(this->semaphoreHandle);
  }
}

void EventManager::publish(EventType event) const {
  uint8_t subscriptionIndex;
  uint8_t eventIndex;

  this->lock();

  // Iterate over each subscription
  for (subscriptionIndex = 0; subscriptionIndex < subscriptionsCount; subscriptionIndex++) {
    const Subscription& subscription = subscriptions[subscriptionIndex];
    // Check if the event matches any of the subscribed events
    for (eventIndex = 0; eventIndex < subscription.eventsCount; eventIndex++) {
      if (subscription.events[eventIndex] == event) {
        subscription.service->notify(event);
        break;
      }
    }
  }

  this->unlock();
}

void EventManager::subscribe(Service* service, const EventType events[], uint8_t count) {
  bool alreadySubscribed = false;
  uint8_t subscriptionIndex;

  this->lock();

  // Check if the subscription limit is not reached
  if (subscriptionsCount < MAX_SUBSCRIPTIONS_COUNT) {
    // Check if service is not already subscribed
    for (subscriptionIndex = 0; subscriptionIndex < subscriptionsCount; subscriptionIndex++) {
      if (subscriptions[subscriptionIndex].service == service) {
        alreadySubscribed = true;
        break;
      }
    }
    if (!alreadySubscribed) {
      // Add subscription
      subscriptions[subscriptionsCount++] = { service, events, count };
      ESP_LOGD(TAG, "subscription added");
    } else {
      ESP_LOGE(TAG, "Service already subscribed, won't add it");
    }
  } else {
    ESP_LOGE(TAG, "Max subscriptions limit reached, cannot add more");
  }

  this->unlock();
}

void EventManager::unsubscribe(Service* service) {
  uint8_t subscriptionIndex;
  uint8_t shiftIndex;
  bool removed = false;

  this->lock();

  // Iterate through the subscription list
  for (subscriptionIndex = 0; subscriptionIndex < subscriptionsCount; subscriptionIndex++) {
    // Find the subscription for the object that wants to subscribe
    if (subscriptions[subscriptionIndex].service == service) {
      // Shift remaining subscriptions left to fill the gap
      for (shiftIndex = subscriptionIndex; shiftIndex < subscriptionsCount - 1; shiftIndex++) {
        subscriptions[shiftIndex] = subscriptions[shiftIndex + 1];
      }
      // Decrement subscription count because 1 subscription was removed
      subscriptionsCount--;
      removed = true;
      ESP_LOGD(TAG, "Subscription removed");
      break;
    }
  }
  if (!removed) {
    ESP_LOGE(TAG, "Failed to unsubscribe: subscription not found");
  }

  this->unlock();
}
