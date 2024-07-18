#ifndef SERVICE_H
#define SERVICE_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "EventManager.h"

// Forward declaration to avoid circular dependencies between header files
enum class EventType;
class EventManager;

class Service {
public:
  Service(const char* name, UBaseType_t priority, uint32_t stackSize, UBaseType_t queueSize);
  virtual ~Service();
  void run();
  void notify(EventType event);
  const char* getName(void);

protected:
  virtual void onStart(void) = 0;
  virtual void onEvent(EventType event) = 0;

private:
  TaskHandle_t taskHandle;
  const char* taskName;
  UBaseType_t taskPriority;
  uint32_t taskStackSize;
  QueueHandle_t queueHandle;
  UBaseType_t eventQueueSize;

  static void task(void* params);
};

#endif // SERVICE_H
