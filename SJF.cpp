#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include "helper.h"

int main()
{
    std::vector<Process> processes{
     //  #  AT, BT, RT, CT, TAT, WT;
        {1,  1,  3, -1, -1,  -1, -1}, // P1
        {2,  2,  4, -1, -1,  -1, -1}, // P2
        {3,  1,  2, -1, -1,  -1, -1}, // P3
        {4,  4,  4, -1, -1,  -1, -1}  // P4
    };

    sortArrivalTime(processes);

    int pRT = processes[0].AT;

    std::vector<int> readyQueue;

    addToRQ(processes, readyQueue, pRT);

    while (!isCompleated(readyQueue, 0))
    {
        int index = findMinIndex(readyQueue, 0);
        if (readyQueue[index] > 0) {
            readyQueue[index] = 0;
            processes[index].RT = pRT;
            pRT += processes[index].BT;
            processes[index].CT = pRT;
        } else pRT++;
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