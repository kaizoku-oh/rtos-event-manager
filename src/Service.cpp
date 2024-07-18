#include <esp_log.h>

#include "Service.h"

#define TAG "[Service]"

Service::Service(const char* name, UBaseType_t priority, uint32_t stackSize, UBaseType_t queueSize)
  : taskHandle(nullptr),
    taskName(name),
    taskPriority(priority),
    taskStackSize(stackSize),
    queueHandle(nullptr),
    eventQueueSize(queueSize) {

  ESP_LOGD(TAG, "Service object is created");
}

void Service::run() {
  this->queueHandle = xQueueCreate(this->eventQueueSize, sizeof(EventType));
  xTaskCreate(task, this->taskName, this->taskStackSize, this, this->taskPriority, &(this->taskHandle));
  ESP_LOGD(TAG, "%s is started", this->taskName);
}

void Service::notify(EventType event) {
  if (xPortInIsrContext()) {
    // Sending event from inside ISR context
    xQueueSendFromISR(this->queueHandle, &event, NULL);
  } else {
    // Sending event from inside task/thread context
    xQueueSend(this->queueHandle, &event, 0);
  }
}

const char* Service::getName(void) {
  return this->taskName;
}

void Service::task(void* params) {
  Service* self = static_cast<Service*>(params);
  EventType event;

  self->onStart();
  ESP_LOGD(TAG, "%s is waiting for an event...", self->taskName);
  while (true) {
    if (xQueueReceive(self->queueHandle, &event, portMAX_DELAY)) {
      self->onEvent(event);
    }
  }
}

Service::~Service() {
  if (this->taskHandle) {
    vTaskDelete(this->taskHandle);
    ESP_LOGD(TAG, "Task %s deleted", this->taskName);
  }

  if (this->queueHandle) {
    vQueueDelete(this->queueHandle);
    ESP_LOGD(TAG, "Queue for task %s deleted", this->taskName);
  }
}
