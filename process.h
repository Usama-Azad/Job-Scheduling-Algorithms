#pragma once

#include <iostream>

struct Process {
    int PID, AT, BT, RT, CT, TAT, WT;

    void exec() {
        TAT = CT - AT;
        WT = TAT - BT;
    }

    friend std::ostream& operator<<(std::ostream& out, const Process& p) {
        out << p.PID << '\t' << p.AT << '\t' << p.BT << '\t' << p.RT << '\t' << p.CT << '\t' << p.TAT << '\t' << p.WT;
        return out;
    }
};

struct PProcess {
    int PID, AT, BT, PR, RT, CT, TAT, WT;

    void exec() {
        TAT = CT - AT;
        WT = TAT - BT;
    }

    friend std::ostream& operator<<(std::ostream& out, const PProcess& p) {
        out << p.PID << '\t' << p.AT << '\t' << p.BT << '\t' << p.PR << '\t' << p.RT << '\t' << p.CT << '\t' << p.TAT << '\t' << p.WT;
        return out;
    }
};