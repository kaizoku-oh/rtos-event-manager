#include <esp_log.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "ServiceA.h"
#include "ServiceB.h"
#include "EventManager.h"

#define TAG "[MAIN]"
#define BOOT_BUTTON_GPIO_NUMBER (GPIO_NUM_0)

static void onButtonPress(void* arg);
static void setupButton(gpio_num_t gpio, gpio_isr_t callback);

extern "C" void app_main() {
  // Wait a little bit to open the pio serial monitor
  vTaskDelay(pdMS_TO_TICKS(3000));
  ESP_LOGI(TAG, "Creating event manager and services...");
  uint8_t secondsUntilExit = 60;
  EventManager& eventManager = EventManager::getInstance();
  ServiceA serviceA;
  ServiceB serviceB;

  // Setup BOOT button to be used as a regular user button
  setupButton(BOOT_BUTTON_GPIO_NUMBER, onButtonPress);

  ESP_LOGI(TAG, "Starting services...");
  serviceA.run();
  serviceB.run();

  ESP_LOGI(TAG, "Publishing events...");
  eventManager.publish(EventType::EVENT_TIME_AVAILABLE);
  eventManager.publish(EventType::EVENT_WIFI_CONNECTED);

  while (secondsUntilExit--) {
    ESP_LOGI(TAG, "Running...");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  // Objects will be deleted upon exiting the app_main() function
}

static void IRAM_ATTR onButtonPress(void* arg) {
  EventManager::getInstance().publish(EventType::EVENT_BUTTON_PRESSED);
}

static void setupButton(gpio_num_t gpio, gpio_isr_t callback) {
  // Setting GPIO configuration for the button
  gpio_config_t config = {
    .pin_bit_mask = BIT(gpio),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_NEGEDGE
  };

  // Setting an interrupt handler for the button
  ESP_ERROR_CHECK(gpio_config(&config));
  ESP_ERROR_CHECK(gpio_install_isr_service(0));
  ESP_ERROR_CHECK(gpio_isr_handler_add(gpio, callback, (void*)gpio));
}
