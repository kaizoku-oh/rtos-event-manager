#include <esp_log.h>

#include "ServiceA.h"
#include "EventManager.h"

#define TAG "[ServiceA]"

// List of events
const Event ServiceA::events[] = {
  Event::BUTTON_PRESSED,
  Event::TIME_AVAILABLE,
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

void ServiceA::onEvent(Event event) {
  ESP_LOGI(TAG, "Received event %d", static_cast<int>(event));
  switch (event) {
    case Event::BUTTON_PRESSED:
      ESP_LOGI(TAG, "Button is pressed");
      break;
    case Event::WIFI_CONNECTED:
      ESP_LOGI(TAG, "WiFi is connected");
      break;
    default:
      ESP_LOGW(TAG, "Unsupported event (%d)", static_cast<int>(event));
      break;
  }
}
