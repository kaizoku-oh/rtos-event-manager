#include <esp_log.h>

#include "ServiceB.h"
#include "EventManager.h"

#define TAG "[ServiceB]"

static const EventType events[] = {
  EventType::EVENT_BUTTON_PRESSED,
  EventType::EVENT_WIFI_CONNECTED,
};

ServiceB::ServiceB() : Service("ServiceB", tskIDLE_PRIORITY + 1, 2048, 8) {
  EventManager::getInstance().subscribe(this, events, 2);
  ESP_LOGD(TAG, "ServiceB object is created");
}

void ServiceB::onEvent(EventType event) {
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

ServiceB::~ServiceB() {
  ESP_LOGD(TAG, "ServiceB object is destroyed");
  EventManager::getInstance().unsubscribe(this);
}
