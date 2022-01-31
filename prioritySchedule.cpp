#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include "helper.h"

int main()
{
    std::vector<PProcess> processes {
        { 1, 0, 4, 50, -1, -1, -1, -1 }, // P1
        { 2, 1, 7, 40, -1, -1, -1, -1 }, // P2
        { 3, 2, 8, 20, -1, -1, -1, -1 }, // P3
        { 4, 3, 3, 30, -1, -1, -1, -1 }, // P4
        { 5, 4, 2, 10, -1, -1, -1, -1 }, // P5
        { 5, 5, 9, 60, -1, -1, -1, -1 }  // P6
    };

    sortArrivalTime(processes);

    int pRT = processes[0].AT;

    std::vector<int> readyQueue;

    addToRQ_P(processes, readyQueue, pRT);

    while (!isCompleated(readyQueue, -1)) {
        int index = findMinIndex(readyQueue, -1);
        if (processes[index].RT == -1)
            processes[index].RT = pRT;
        pRT += processes[index].BT;
        if (processes[index].CT == -1)
            processes[index].CT = pRT;
        readyQueue[index] = -1;
        addToRQ_P(processes, readyQueue, pRT);
    }

    for (auto& p : processes) p.exec();

    std::cout << "PID\tAT\tBT\tPR\tRT\tCT\tTAT\tWT\n";

    for (const auto& p : processes)
        std::cout << p << "\n";

    std::cout << "Avg. TAT = " << getAverageTAT(processes) << "\n";

    std::cout << "Avg. WT = " << getAverageWT(processes) << "\n";

    return 0;
}