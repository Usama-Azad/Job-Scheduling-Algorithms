#pragma once

#include <vector>
#include "process.h"

bool isCompleated(const std::vector<int>& BT, const int& x) {
    for (const auto& bt : BT)
        if (bt != x)
            return false;
    return true;
}

int findMin(const std::vector<int>& vec, const int& j) {
    int min = j;
    for (const int& x : vec) {
        if (x > j && min == j)
            min = x;
        else
            if (x < min && x > j)
                min = x;
    }
    return min;
}

void addToRQ(const std::vector<Process>& processes, std::vector<int>& readyQueue, int timer) {
    static int x = -1;
    for (const auto& p : processes)
        if (p.AT > x && p.AT <= timer)
            readyQueue.push_back(p.BT);
    x = timer;
}

void addToRQ_P(const std::vector<PProcess>& processes, std::vector<int>& readyQueue, int timer) {
    static int x = -1;
    for (const auto& p : processes)
        if (p.AT > x && p.AT <= timer)
            readyQueue.push_back(p.PR);
    x = timer;
}

template <typename T>
void sortArrivalTime(std::vector<T>& processes){
    std::sort(
        processes.begin(),
        processes.end(),
        [](const auto& p1, const auto& p2)
        { return p1.AT < p2.AT; }
    );
}

int findMinIndex(const std::vector<int>& readyQueue, const int& x){
    return std::find(readyQueue.begin(), readyQueue.end(), findMin(readyQueue, x)) - readyQueue.begin();
}

template <typename T>
float getAverageTAT(const std::vector<T>& processes){
    return (std::accumulate(processes.begin(), processes.end(), 0.f, [](const auto& p1, const auto& p2) { return p1 + p2.TAT; }) / processes.size());
}

template <typename T>
float getAverageWT(const std::vector<T>& processes) {
    return (std::accumulate(processes.begin(), processes.end(), 0.f, [](const auto& p1, const auto& p2) { return p1 + p2.WT; }) / processes.size());
}