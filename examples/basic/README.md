# Basic Service communication

This example is an ESP-IDF-based application that demonstrates the use of event management and FreeRTOS tasks in an embedded system. The project includes two services, ServiceA and ServiceB, which handle different events published by an EventManager. The application also sets up a button interrupt to trigger events.

```mermaid
sequenceDiagram
    participant Object1 as main
    participant EventManager as EventManager
    participant Object2 as ServiceA
    participant Object3 as ServiceB
    participant Object4 as ISR

    Object1->>EventManager: Publish <EVENT_TIME_AVAILABLE>
    EventManager->>Object2: Forward <EVENT_TIME_AVAILABLE>

    Object1->>EventManager: Publish <EVENT_WIFI_CONNECTED>
    EventManager->>Object3: Forward <EVENT_WIFI_CONNECTED>

    Object4->>EventManager: Publish <EVENT_BUTTON_PRESSED>
    EventManager->>Object2: Forward <EVENT_BUTTON_PRESSED>
    EventManager->>Object3: Forward <EVENT_BUTTON_PRESSED>
```
