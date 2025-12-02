#include <bits/stdc++.h>
using namespace std;

struct Process {
    string pid;
    int at, bt;
    int ct, tat, wt;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // Input
    for (int i = 0; i < n; i++) {
        cout << "Enter Process ID, Arrival Time, Burst Time: ";
        cin >> p[i].pid >> p[i].at >> p[i].bt;
    }

    // Sort by Arrival Time
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    int currentTime = 0;
    int totalTAT = 0, totalWT = 0;

    // FCFS Logic
    for (int i = 0; i < n; i++) {
        // Handle CPU idle time
        if (currentTime < p[i].at)
            currentTime = p[i].at;

        p[i].ct = currentTime + p[i].bt;     // Completion Time
        currentTime = p[i].ct;

        p[i].tat = p[i].ct - p[i].at;        // Turnaround Time
        p[i].wt  = p[i].tat - p[i].bt;       // Waiting Time

        totalTAT += p[i].tat;
        totalWT  += p[i].wt;
    }

    // Output
    cout << "\n============================================\n";
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "============================================\n";

    for (auto &x : p) {
        cout << x.pid << "\t"
             << x.at << "\t"
             << x.bt << "\t"
             << x.ct << "\t"
             << x.tat << "\t"
             << x.wt << "\n";
    }

    cout << "============================================\n";
    cout << "Total TAT = " << totalTAT << "\n";
    cout << "Total WT  = " << totalWT  << "\n";
    cout << "Average TAT = " << (float)totalTAT / n << "\n";
    cout << "Average WT  = " << (float)totalWT  / n << "\n";

    return 0;
}
