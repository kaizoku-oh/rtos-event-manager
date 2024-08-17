# State machine Service communication

This example demonstrates the use of state machine enabled active objects (services) that handle events.

The project uses a [port](https://github.com/oldrev/esp-idf-smf) of Zephyr SMF (State Machine Framework) for ESP-IDF.

```mermaid

sequenceDiagram
    participant Object1 as main
    participant EventManager as EventManager
    participant Object2 as ServiceA
    participant Object3 as ServiceB
    participant Object4 as ISR

    Object1->>EventManager: Publish <TIME_AVAILABLE>
    EventManager->>Object2: Forward <TIME_AVAILABLE>

    Object1->>EventManager: Publish <WIFI_CONNECTED>
    EventManager->>Object3: Forward <WIFI_CONNECTED>

    Object4->>EventManager: Publish <BUTTON_PRESSED>
    EventManager->>Object2: Forward <BUTTON_PRESSED>
    EventManager->>Object3: Forward <BUTTON_PRESSED>
```
