#include <esp_log.h>

#include "ServiceA.h"
#include "EventManager.h"
#include "smf/smf.h"

#define TAG "[ServiceA]"

// List of events
const EventType ServiceA::events[] = {
  EventType::EVENT_BUTTON_PRESSED,
  EventType::EVENT_TIME_AVAILABLE,
};
 
// List of states
const struct smf_state ServiceA::states[STATE_MAX] = {
  [STATE_0] = SMF_CREATE_STATE(nullptr, ServiceA::state0EventHandler, nullptr),
  [STATE_1] = SMF_CREATE_STATE(nullptr, ServiceA::state1EventHandler, nullptr),
};

ServiceA::ServiceA() : Service("ServiceA", tskIDLE_PRIORITY + 1, 2048, 8) {
  // Set initial state for the state machine as STATE_0
  smf_set_initial(SMF_CTX(&(this->stateMachine)), &states[STATE_0]);
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
  // Save event to be used later inside the state handler functions
  this->stateMachine.event = event;
  // Run one iteration of the state machine (including any parent states)
  smf_run_state(SMF_CTX(&(this->stateMachine)));
}

void ServiceA::state0EventHandler(void* machine) {
  state_machine_t* sm = static_cast<state_machine_t*>(machine);

  switch (sm->event) {
    case EventType::EVENT_BUTTON_PRESSED:
      ESP_LOGI(TAG, "Button is pressed");
      break;
    case EventType::EVENT_TIME_AVAILABLE:
      ESP_LOGI(TAG, "Time is available");
      break;
    default:
      ESP_LOGW(TAG, "Unsupported event (%d) in STATE_0", static_cast<int>(sm->event));
      break;
  }
}

void ServiceA::state1EventHandler(void* machine) {
  state_machine_t* sm = static_cast<state_machine_t*>(machine);

  switch (sm->event) {
    case EventType::EVENT_BUTTON_PRESSED:
      ESP_LOGI(TAG, "Button is pressed");
      break;
    case EventType::EVENT_TIME_AVAILABLE:
      ESP_LOGI(TAG, "Time is available");
      break;
    default:
      ESP_LOGW(TAG, "Unsupported event (%d) in STATE_1", static_cast<int>(sm->event));
      break;
  }
}
