
#pragma once
#include <string>

enum class EventType {
    TEMP,
    BUTTON,
    MOTION
};

std::string to_string(EventType t);

struct Event {
    int timestamp;  // increasing
    int sensorId;
    EventType type;
    int value;
};

// Random event generator (producer)
Event generateRandomEvent();
