
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

#include "Event.h"
#include "EventLog.h"
#include "EventQueue.h"
#include "AlarmSet.h"
#include "SortStrategy.h"

// Producer/consumer tick
void doTick(EventQueue& q, EventLog& log, AlarmSet& alarms) {
    // Producer: generate event if queue not full
    if (!q.isFull()) {
        Event e = generateRandomEvent();
        q.enqueue(e);
    }

    // Consumer: move one event from queue -> log
    Event e;
    if (q.dequeue(e)) {
        log.append(e);
        alarms.processEvent(e);
    }
}

void printHelp() {
    std::cout << "Commands:\n"
        << "  tick <n>             - run n tick iterations (producer + consumer)\n"
        << "  print                - print full event log\n"
        << "  sort <name>          - sort log by timestamp using strategy\n"
        << "                         name: insertion | selection | timestamp\n"
        << "  find <sensorId>      - list all events with given sensor id\n"
        << "  alarms               - show active temperature alarms\n"
        << "  set-threshold <val>  - set temperature alarm threshold\n"
        << "  help                 - show this help\n"
        << "  exit                 - quit program\n";
}

void cmdFind(const EventLog& log, int sensorId) {
    bool found = false;
    for (std::size_t i = 0; i < log.size(); ++i) {
        const Event& e = log[i];
        if (e.sensorId == sensorId) {
            if (!found) {
                std::cout << "Events for sensor " << sensorId << ":\n";
                std::cout << "Idx  "
                    << "Time  "
                    << "Sensor "
                    << "Type    "
                    << "Value\n";
                std::cout << "-----------------------------------------\n";
            }
            found = true;
            std::cout << std::setw(4) << i << "  "
                << std::setw(4) << e.timestamp << "  "
                << std::setw(6) << e.sensorId << "  "
                << std::setw(7) << to_string(e.type) << "  "
                << std::setw(5) << e.value << "\n";
        }
    }
    if (!found) {
        std::cout << "[find] no events found for sensor " << sensorId << "\n";
    }
}

int main() {
    // kernel ADT
    EventQueue queue(32);   // fast capacity (ringbuffer)
    EventLog   log(64);     // dynamic log
    AlarmSet   alarms(50);  // Modul A

    std::cout << "Embedded Event Logger (C++)\n";
    printHelp();

    std::string cmd;
    while (true) {
        std::cout << "> ";
        if (!(std::cin >> cmd)) {
            break; 
        }

        if (cmd == "tick") {
            int n = 0;
            if (!(std::cin >> n) || n < 0) {
                std::cout << "[error] usage: tick <non-negative int>\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            for (int i = 0; i < n; ++i) {
                doTick(queue, log, alarms);
            }
            std::cout << "[tick] ran " << n << " iterations, log size=" << log.size() << "\n";
        }
        else if (cmd == "print") {
            log.print();
        }
        else if (cmd == "sort") {
            std::string name;
            if (!(std::cin >> name)) {
                std::cout << "[error] usage: sort <name>\n";
                continue;
            }
            SortFn sorter = chooseSortStrategy(name);
            if (!sorter) {
                std::cout << "[error] unknown sort strategy: " << name
                    << " (use insertion | selection | timestamp)\n";
                continue;
            }
            sorter(log);
            std::cout << "[sort] done using strategy '" << name << "'\n";
            if (isSortedByTimestamp(log)) {
                std::cout << "[sort] log is sorted by timestamp\n";
            }
            else {
                std::cout << "[sort] WARNING: log not sorted correctly\n";
            }
        }
        else if (cmd == "find") {
            int sensorId = 0;
            if (!(std::cin >> sensorId)) {
                std::cout << "[error] usage: find <sensorId>\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            cmdFind(log, sensorId);
        }
        else if (cmd == "alarms") {
            alarms.printAlarms();
        }
        else if (cmd == "set-threshold") {
            int val = 0;
            if (!(std::cin >> val)) {
                std::cout << "[error] usage: set-threshold <int>\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            alarms.setThreshold(val);
            std::cout << "[alarms] threshold set to " << val << "\n";
        }
        else if (cmd == "help") {
            printHelp();
        }
        else if (cmd == "exit") {
            std::cout << "Bye!\n";
            break;
        }
        else {
            std::cout << "[error] unknown command: " << cmd << "\n";
            printHelp();
        }
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
