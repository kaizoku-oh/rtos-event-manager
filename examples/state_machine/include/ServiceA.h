#ifndef SERVICE_A_H
#define SERVICE_A_H

#include "Service.h"
#include "smf/smf.h"

// Used to facilitate indexing/enumerating the states[] list
typedef enum {
  STATE_0 = 0,
  STATE_1,
  STATE_MAX,
} state_t;

// State machine global context (contains SMF context + user data)
typedef struct {
  // This must be first
  struct smf_ctx ctx;
  // Variable to hold the event message
  EventType event;
  // Other state specific data add here...
} state_machine_t;

class ServiceA : public Service {
public:
  ServiceA();
  ~ServiceA();
protected:
  void onEvent(EventType event) override;
private:
  static void state0EventHandler(void* machine);
  static void state1EventHandler(void* machine);
  static const struct smf_state states[STATE_MAX];
  static const EventType events[static_cast<int>(EventType::MAX_EVENTS)];
  state_machine_t stateMachine;
};

#endif // SERVICE_A_H
