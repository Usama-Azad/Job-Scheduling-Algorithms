#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include "helper.h"

int main()
{
    std::vector<Process> processes{
     //  #  AT, BT, RT, CT, TAT, WT;
        {1, 0, 7, -1, -1, -1, -1}, // P1
        {2, 1, 8, -1, -1, -1, -1}, // P2
        {3, 2, 4, -1, -1, -1, -1}, // P3
        {4, 3, 2, -1, -1, -1, -1}, // P4
        {5, 4, 9, -1, -1, -1, -1}, // P5
        {6, 5, 5, -1, -1, -1, -1}, // P6
        {7, 6, 4, -1, -1, -1, -1}  // P7
    };

    sortArrivalTime(processes);

    int pRT = processes[0].AT;

    std::vector<int> readyQueue;

    addToRQ(processes, readyQueue, pRT);

    while (!isCompleated(readyQueue, 0))
    {
        int index = findMinIndex(readyQueue, 0);
        if (readyQueue[index] > 0) {
            readyQueue[index]--;
            if (processes[index].RT == -1)
                processes[index].RT = pRT;
        }
        pRT++;
        if (readyQueue[index] == 0 && processes[index].CT == -1)
            processes[index].CT = pRT;
        addToRQ(processes, readyQueue, pRT);
    }

    for (auto& p : processes) p.exec();

    std::cout << "PID\tAT\tBT\tRT\tCT\tTAT\tWT\n";

    for (const auto& p : processes)
        std::cout << p << "\n";

    std::cout << "\nAvg. TAT = " << getAverageTAT(processes) << "\n";

    std::cout << "Avg. WT = " << getAverageWT(processes) << "\n";

    return 0;
}