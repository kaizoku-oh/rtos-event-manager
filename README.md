# ⚡ Event Driven Architecture for MCUs in C++ using EventManager and ActiveObject Services

This project demonstrates a system using an RTOS and employing an `EventManager` and `ActiveObject` design pattern in C++.

## Concepts

### EventManager

The `EventManager` is a singleton class responsible for managing events within the system. It allows services to subscribe to specific events and publishes these events to all subscribed services when they occur. This decouples the event producers from the event consumers, leading to a more modular and maintainable codebase.

### Service

The `ActiveObject` pattern here is used to encapsulate each service in its own thread of execution, allowing them to process events asynchronously. Each `Service` has its own event queue and a task that processes incoming events. This pattern helps to avoid blocking operations and keeps the system responsive.

## ✅ TODO

- [x] Add the ability for services to unsubscribe

- [x] Add thread safety to EventManager

- [x] Add event-driven state machine using SMF (State Machine Framework)

- [ ] Optimize state machine code

- [ ] Add error handling

- [ ] Use esp-idf-smf as a submodule

- [ ] Add OSAL layer to abstract the FreeRTOS APIs (Probably CMSIS OS)

- [ ] Add portability layer for logging

- [ ] Add config layer

- [ ] Add examples for Zephyr and Arduino Core

- [ ] Add unit tests

- [ ] Add CI workflow

- [ ] Publish repo to the ESP-IDF component registry

- [ ] Package repo as a PlatformIO library and publish it

- [ ] Package repo as Zephyr module

## License

This project is licensed under the MIT License - see the LICENSE file for details.
