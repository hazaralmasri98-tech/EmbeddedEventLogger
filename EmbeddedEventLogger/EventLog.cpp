
#include "EventLog.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>

EventLog::EventLog(std::size_t initialCapacity) {
    events_.reserve(initialCapacity);
}

std::size_t EventLog::size() const {
    return events_.size();
}

void EventLog::append(const Event& e) {
    events_.push_back(e);
}

Event EventLog::get(std::size_t index) const {
    if (index >= events_.size()) {
        throw std::out_of_range("EventLog::get index out of range");
    }
    return events_[index];
}

void EventLog::set(std::size_t index, const Event& e) {
    if (index >= events_.size()) {
        throw std::out_of_range("EventLog::set index out of range");
    }
    events_[index] = e;
}

Event& EventLog::operator[](std::size_t index) {
    return events_.at(index);
}

const Event& EventLog::operator[](std::size_t index) const {
    return events_.at(index);
}

void EventLog::print() const {
    if (events_.empty()) {
        std::cout << "[log] (empty)\n";
        return;
    }

    std::cout << "Idx  "
        << "Time  "
        << "Sensor "
        << "Type    "
        << "Value\n";
    std::cout << "-----------------------------------------\n";

    for (std::size_t i = 0; i < events_.size(); ++i) {
        const Event& e = events_[i];
        std::cout << std::setw(4) << i << "  "
            << std::setw(4) << e.timestamp << "  "
            << std::setw(6) << e.sensorId << "  "
            << std::setw(7) << to_string(e.type) << "  "
            << std::setw(5) << e.value << "\n";
    }
}

bool isSortedByTimestamp(const EventLog& log) {
    if (log.size() <= 1) return true;
    for (std::size_t i = 1; i < log.size(); ++i) {
        if (log[i - 1].timestamp > log[i].timestamp) {
            return false;
        }
    }
    return true;
}
