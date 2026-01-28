
#pragma once
#include <cstddef>
#include <vector>
#include "Event.h"

class EventLog {
public:
    explicit EventLog(std::size_t initialCapacity = 16);

    std::size_t size() const;
    void append(const Event& e);
    Event get(std::size_t index) const;
    void set(std::size_t index, const Event& e);

    Event& operator[](std::size_t index);
    const Event& operator[](std::size_t index) const;

    void print() const;

private:
    std::vector<Event> events_;
};

// helper for testing sort correctness
bool isSortedByTimestamp(const EventLog& log);
