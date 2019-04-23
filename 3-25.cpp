#include<iostream>
#include<queue>
#include<vector>

using namespace std;

class Process {
    public:
    int at, bt, priority;
    Process(int a, int b, int p) {
        at = a;
        bt = b;
        priority = p;
    }
    int doProc() {return --bt;}
    int complete() {return bt;}
};

void priorityWithPreempt(vector<Process> processes) {
    auto cmpa = [](Process left, Process right) { return (left.at) > (right.at);};
    priority_queue<Process, vector<Process>, decltype(cmpa)> qa(cmpa);

    for(Process p : processes) {
        qa.push(p);
    }

    auto cmpp = [](Process left, Process right) { return (left.priority) == (right.priority)? (left.at) > (right.at) : (left.priority) < (right.priority);};
    priority_queue<Process, vector<Process>, decltype(cmpp)> qp(cmpp);
    
    for (int i = 0; !qa.empty() || !qp.empty(); i++) {
        if(!qa.empty()) {
            while (!qa.empty() && qa.top().at <= i) {
                Process p = qa.top();
                qa.pop();
                qp.push(p);
            }
        }
        if(!qp.empty()) {
            Process p = qp.top();
            qp.pop();
            if (p.doProc() == 0) {
                cout<<"Process with at, bt, p "<<p.at<<" "<<p.bt<<" "<<p.priority<<" completed at "<<i+1<<endl;
            } else {
                qp.push(p);
            }
        }
    }
}

void priorityWithOutPreempt(vector<Process> processes) {

    auto cmpa = [](const Process & left, const Process & right) { return (left.at) > (right.at);};
    priority_queue<Process, vector<Process>, decltype(cmpa)> qa(cmpa);

    for(Process p : processes) {
        qa.push(p);
    }

    auto cmpp = [](const Process & left, const Process & right) { return (left.priority) < (right.priority);};
    priority_queue<Process, vector<Process>, decltype(cmpp)> qp(cmpp);
    
    for (int i = 0; !qa.empty() || !qp.empty();) {
        if(!qa.empty()) {
            while (!qa.empty() && qa.top().at <= i) {
                Process p = qa.top();
                qa.pop();
                qp.push(p);
            }
        }
        if(!qp.empty()) {
            Process p = qp.top();
            qp.pop();
            int time = p.complete();
            cout<<"Process with at, bt, p "<<p.at<<" "<<p.bt<<" "<<p.priority<<" completed at "<<i + time<<endl;
            i += time;
        } else {
            i++;
        }
    }
}

int main(void) {
    int n;

    vector<Process> processes;

    cout<<"How many processes?"<<endl;
    cin>>n;
    // processes.reserve(n);
    cout<<"Enter arrival times, burst times and priority"<<endl;
    for (int i = 0; i < n; i++) {
        int a, b, p;
        cin>>a>>b>>p;
        Process proc(a, b, p);
        processes.push_back(proc);
    }

    cout<<"With preemption: "<<endl;
    priorityWithPreempt(processes);

    cout<<"Without preemption: "<<endl;
    priorityWithOutPreempt(processes);

    return 0;
}

