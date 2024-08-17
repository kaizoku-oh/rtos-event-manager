#ifndef SERVICE_B_H
#define SERVICE_B_H

#include "Service.h"

class ServiceB : public Service {
public:
  ServiceB();
  ~ServiceB();
protected:
  void onEvent(Event event) override;
};

#endif // SERVICE_B_H
