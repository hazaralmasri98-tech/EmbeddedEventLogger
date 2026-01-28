
#pragma once
#include <unordered_set>
#include "Event.h"

class AlarmSet {
public:
    explicit AlarmSet(int threshold = 50);

    void setThreshold(int t);
    int getThreshold() const;

    void processEvent(const Event& e);
    void printAlarms() const;

private:
    int threshold_;
    std::unordered_set<int> active_;
};
