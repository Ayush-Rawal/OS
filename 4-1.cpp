#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Process {
    public:
    int at, bt, tempBT, ct;
    Process(int a, int b) {
        at = a;
        bt = b;
        tempBT = b;
        ct = 0;
    }
    int doProc(int i = 1) {tempBT = tempBT - i; return tempBT;}
    int complete(int i = 0) {tempBT = 0; ct = i; return tempBT;}
    int remTime() {return tempBT;}
    int getBT() {return  bt;}
    int getAT() {return at;}
    int getCT() {return ct;}
};

void printGanttChart(vector<Process> &processes) {
    cout<<"|    AT   |   BT  |   CT  |   TAT  |   WT "<<endl;
    cout<<"------------------------------------------"<<endl;
    for(auto process: processes) {
        cout<<process.getAT()<<" "<<process.getBT()<<" "<<process.getCT()<<" "<<
        process.getCT() - process.getAT()<<" "<<process.getCT() - process.getAT() - process.getBT()<<endl;
    }
}

void roundRobin(vector<Process> &processes, const unsigned int tq) {
    vector<Process> done;
    for (int i = 0; done.size() != processes.size(); i++) {
        for(auto process : processes) {
            if(process.remTime() <= tq) {
                process.complete(i);
                done.push_back(process);
            } else {
                process.doProc(tq);
            }
        }
    }
    printGanttChart(done);
}

int main() {
    int n;

    vector<Process> processes;

    cout<<"How many processes?"<<endl;
    cin>>n;
    processes.reserve(n);
    cout<<"Enter arrival times and burst times"<<endl;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin>>a>>b;
        Process proc(a, b);
        processes.push_back(proc);
    }

    return 0;
}