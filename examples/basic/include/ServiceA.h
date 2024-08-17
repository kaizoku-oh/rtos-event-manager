#ifndef SERVICE_A_H
#define SERVICE_A_H

#include "Service.h"

class ServiceA : public Service {
public:
  ServiceA();
  ~ServiceA();
protected:
  void onEvent(Event event) override;
private:
  static const Event events[static_cast<int>(Event::MAX_EVENTS)];
};

#endif // SERVICE_A_H
