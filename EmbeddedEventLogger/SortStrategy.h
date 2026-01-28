
#pragma once
#include <string>
#include "EventLog.h"

using SortFn = void(*)(EventLog&);

void insertionSort(EventLog& log);
void selectionSort(EventLog& log);

// Select strategy by name (for command: sort <name>)
SortFn chooseSortStrategy(const std::string& name);
