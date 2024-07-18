#ifndef SERVICE_B_H
#define SERVICE_B_H

#include "Service.h"

class ServiceB : public Service {
public:
  ServiceB();
  ~ServiceB();
protected:
  void onEvent(EventType event) override;
};

#endif // SERVICE_B_H
