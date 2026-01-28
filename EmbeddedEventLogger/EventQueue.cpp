
#include "EventQueue.h"

EventQueue::EventQueue(std::size_t capacity)
    : buffer_(capacity),
    head_(0),
    tail_(0),
    count_(0) {
}

bool EventQueue::isEmpty() const {
    return count_ == 0;
}

bool EventQueue::isFull() const {
    return count_ == buffer_.size();
}

bool EventQueue::enqueue(const Event& e) {
    if (isFull()) {
        return false;
    }
    buffer_[tail_] = e;
    tail_ = (tail_ + 1) % buffer_.size();
    ++count_;
    return true;
}

bool EventQueue::dequeue(Event& out) {
    if (isEmpty()) {
        return false;
    }
    out = buffer_[head_];
    head_ = (head_ + 1) % buffer_.size();
    --count_;
    return true;
}
