#include <bits/stdc++.h>
using namespace std;

struct Process {
    string pid;
    int at, bt;
    int ct, tat, wt;
    bool completed = false;
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

    int currentTime = 0;
    int completedCount = 0;
    int totalTAT = 0, totalWT = 0;

    vector<string> gantt;  // Store order of execution

    // Non-preemptive SJF
    while (completedCount < n) {

        int idx = -1;
        int minBT = INT_MAX;

        // Find available shortest job
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= currentTime) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

        // CPU Idle → No process has arrived yet
        if (idx == -1) {
            currentTime++;
            continue;
        }

        // Execute selected process
        currentTime += p[idx].bt;
        p[idx].ct = currentTime;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        p[idx].completed = true;
        gantt.push_back(p[idx].pid);

        totalTAT += p[idx].tat;
        totalWT += p[idx].wt;
        completedCount++;
    }

    // Output table
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "--------------------------------------------------\n";

    for (auto &x : p) {
        cout << x.pid << "\t" << x.at << "\t" << x.bt << "\t"
             << x.ct << "\t" << x.tat << "\t" << x.wt << "\n";
    }

    cout << "--------------------------------------------------\n";
    cout << "Average TAT = " << (float)totalTAT / n << "\n";
    cout << "Average WT  = " << (float)totalWT / n << "\n";

    // Gantt Chart
    cout << "\nGantt Chart:\n";
    for (auto &g : gantt) {
        cout << "| " << g << " ";
    }
    cout << "|\n";

    return 0;
}
