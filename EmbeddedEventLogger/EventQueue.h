
#pragma once
#include <vector>
#include "Event.h"

class EventQueue {
public:
    explicit EventQueue(std::size_t capacity);

    bool isEmpty() const;
    bool isFull() const;
    bool enqueue(const Event& e);
    bool dequeue(Event& out);

private:
    std::vector<Event> buffer_;
    std::size_t head_;
    std::size_t tail_;
    std::size_t count_;
};
