
#include "Event.h"
#include <random>

std::string to_string(EventType t) {
    switch (t) {
    case EventType::TEMP:   return "TEMP";
    case EventType::BUTTON: return "BUTTON";
    case EventType::MOTION: return "MOTION";
    default:                return "UNKNOWN";
    }
}


static int g_timestamp_counter = 0;

Event generateRandomEvent() {
    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> sensorDist(1, 5);   // sensor IDs 1..5
    std::uniform_int_distribution<int> typeDist(0, 2);     // TEMP, BUTTON, MOTION
    std::uniform_int_distribution<int> valueDist(-10, 100);

    Event e;
    e.timestamp = g_timestamp_counter++;
    e.sensorId = sensorDist(rng);
    e.type = static_cast<EventType>(typeDist(rng));
    e.value = valueDist(rng);
    return e;
}
