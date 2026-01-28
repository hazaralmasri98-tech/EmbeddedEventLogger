
#include "SortStrategy.h"

void insertionSort(EventLog& log) {
    std::size_t n = log.size();
    for (std::size_t i = 1; i < n; ++i) {
        Event key = log.get(i);
        std::size_t j = i;
        while (j > 0 && log.get(j - 1).timestamp > key.timestamp) {
            log.set(j, log.get(j - 1));
            --j;
        }
        log.set(j, key);
    }
}

void selectionSort(EventLog& log) {
    std::size_t n = log.size();
    for (std::size_t i = 0; i + 1 < n; ++i) {
        std::size_t minIndex = i;
        for (std::size_t j = i + 1; j < n; ++j) {
            if (log.get(j).timestamp < log.get(minIndex).timestamp) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Event tmp = log.get(i);
            log.set(i, log.get(minIndex));
            log.set(minIndex, tmp);
        }
    }
}

SortFn chooseSortStrategy(const std::string& name) {
    if (name == "insertion") {
        return &insertionSort;
    }
    if (name == "selection") {
        return &selectionSort;
    }
    // default: treat "timestamp" or unknown as insertion
    if (name == "timestamp") {
        return &insertionSort;
    }
    return nullptr;
}
