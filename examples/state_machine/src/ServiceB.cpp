#include <esp_log.h>

#include "ServiceB.h"
#include "EventManager.h"

#define TAG "[ServiceB]"

static const Event events[] = {
  Event::BUTTON_PRESSED,
  Event::WIFI_CONNECTED,
};

ServiceB::ServiceB() : Service("ServiceB", tskIDLE_PRIORITY + 1, 2048, 8) {
  EventManager::getInstance().subscribe(this, events, 2);
  ESP_LOGD(TAG, "ServiceB object is created");
}

void ServiceB::onEvent(Event event) {
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

ServiceB::~ServiceB() {
  ESP_LOGD(TAG, "ServiceB object is destroyed");
  EventManager::getInstance().unsubscribe(this);
}
