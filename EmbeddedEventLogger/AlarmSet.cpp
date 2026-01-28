
#include "AlarmSet.h"
#include <iostream>

AlarmSet::AlarmSet(int threshold)
    : threshold_(threshold) {
}

void AlarmSet::setThreshold(int t) {
    threshold_ = t;
}

int AlarmSet::getThreshold() const {
    return threshold_;
}

void AlarmSet::processEvent(const Event& e) {
    if (e.type != EventType::TEMP) {
        return;
    }
    if (e.value > threshold_) {
        active_.insert(e.sensorId);
    }
    else {
        active_.erase(e.sensorId);
    }
}

void AlarmSet::printAlarms() const {
    if (active_.empty()) {
        std::cout << "[alarms] no active alarms (threshold=" << threshold_ << ")\n";
        return;
    }
    std::cout << "[alarms] active sensors (threshold=" << threshold_ << "): ";
    bool first = true;
    for (int id : active_) {
        if (!first) std::cout << ", ";
        std::cout << id;
        first = false;
    }
    std::cout << "\n";
}
