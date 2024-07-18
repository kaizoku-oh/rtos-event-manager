#include <esp_log.h>

#include "ServiceA.h"
#include "EventManager.h"

#define TAG "[ServiceA]"

// List of events
const EventType ServiceA::events[] = {
  EventType::EVENT_BUTTON_PRESSED,
  EventType::EVENT_TIME_AVAILABLE,
};

ServiceA::ServiceA() : Service("ServiceA", tskIDLE_PRIORITY + 1, 2048, 8) {
  // Subscribe to the list of events
  EventManager::getInstance().subscribe(this, events, 2);
  ESP_LOGD(TAG, "ServiceA object is created");
}

ServiceA::~ServiceA() {
  ESP_LOGD(TAG, "ServiceA object is destroyed");
  EventManager::getInstance().unsubscribe(this);
}

void ServiceA::onEvent(EventType event) {
  ESP_LOGI(TAG, "Received event %d", static_cast<int>(event));
  switch (event) {
    case EventType::EVENT_BUTTON_PRESSED:
      ESP_LOGI(TAG, "Button is pressed");
      break;
    case EventType::EVENT_WIFI_CONNECTED:
      ESP_LOGI(TAG, "WiFi is connected");
      break;
    default:
      ESP_LOGW(TAG, "Unsupported event (%d)", static_cast<int>(event));
      break;
  }
}
