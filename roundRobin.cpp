#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include "helper.h"

int main()
{
    std::vector<Process> processes{
     //  #  AT, BT, RT, CT, TAT, WT;
        {1, 0, 23, -1, -1, -1, -1}, // P1
        {2, 1, 51, -1, -1, -1, -1}, // P2
        {3, 2, 35, -1, -1, -1, -1}, // P3
        {4, 3, 62, -1, -1, -1, -1}, // P4
        {5, 4, 41, -1, -1, -1, -1}  // P5
    };

    constexpr int Q = 20;

    sortArrivalTime(processes);

    int pRT = processes[0].AT;

    std::vector<int> readyQueue;

    for (const auto& p : processes)
        readyQueue.push_back(p.BT);

    while (!isCompleated(readyQueue, 0)) {
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].RT == -1)
                processes[i].RT = pRT;
            if (readyQueue[i] > 0) {
                if (readyQueue[i] == Q) {
                    readyQueue[i] -= Q;
                    processes[i].CT = pRT + Q;
                    pRT += Q;
                }
                else if (readyQueue[i] > Q) {
                    readyQueue[i] -= Q;
                    pRT += Q;
                }
                else {
                    pRT += readyQueue[i];
                    processes[i].CT = pRT;
                    readyQueue[i] = 0;
                }
            }
        }
    }

    for (auto& p : processes) p.exec();

    std::cout << "PID\tAT\tBT\tRT\tCT\tTAT\tWT\n";

    for (const auto& p : processes)
        std::cout << p << "\n";

    std::cout << "\nAvg. TAT = " << getAverageTAT(processes) << "\n";

    std::cout << "Avg. WT = " << getAverageWT(processes) << "\n";

    return 0;
}