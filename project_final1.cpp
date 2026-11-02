#include <iostream>
using namespace std;

struct Process {
    char pid;
    int arrival;
    int burst;
    int remaining;
    int priority;
    int waiting;
    int turnaround;
    Process* next;
};

struct Stack {
    char data[50];
    int top;
};

void initStack(Stack &s) { s.top = -1; }
void push(Stack &s, char x) { s.data[++s.top] = x; }
void printStack(Stack s) {
    cout << "\nExecution Order (Processes in Stack): ";
    while (s.top != -1) { cout << s.data[s.top--] << " "; }
    cout << endl;
}

void addProcess(Process* &head, Process p) {
    Process* newNode = new Process(p);
    newNode->next = NULL;
    if (!head) { head = newNode; return; }
    Process* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
}

int countProcesses(Process* head) {
    int count = 0;
    while (head) { count++; head = head->next; }
    return count;
}

void FCFS(Process* head) {
    int time = 0;
    float totalWT = 0, totalTAT = 0;
    Stack s; initStack(s);

    cout << "\n--- First Come First Serve (FCFS) Scheduling ---\n";

    Process* p = head;
    while (p) {
        if (time < p->arrival) time = p->arrival;
        p->waiting = time - p->arrival;
        time += p->burst;
        p->turnaround = time - p->arrival;

        totalWT += p->waiting;
        totalTAT += p->turnaround;
        push(s, p->pid);

        cout << "Process " << p->pid
             << " | Waiting Time = "<<"<" << p->waiting<<">"
             << " | Turnaround Time = " <<"<" << p->turnaround<<">" << endl;

        p = p->next;
    }

    cout << "Average Waiting Time = " <<"<" << totalWT / countProcesses(head) <<">"<< endl;
    cout << "Average Turnaround Time = " << "<" <<totalTAT / countProcesses(head) <<">"<< endl;
    printStack(s);
}

//SJF (Non-preemptive) 
void SJF(Process* head) {
    int time = 0, completed = 0;
    int n = countProcesses(head);
    float totalWT = 0, totalTAT = 0;
    bool done[50] = {false};
    Process* arr[50];
    Stack s; initStack(s);

    Process* temp = head;
    for (int i = 0; temp; i++, temp = temp->next) arr[i] = temp;

    cout << "\n--- Shortest Job First (SJF) Scheduling ---\n";

    while (completed < n) {
        int idx = -1, minBurst = 9999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && arr[i]->arrival <= time && arr[i]->burst < minBurst) {
                minBurst = arr[i]->burst;
                idx = i;
            }
        }

        if (idx == -1) { time++; continue; }

        arr[idx]->waiting = time - arr[idx]->arrival;
        time += arr[idx]->burst;
        arr[idx]->turnaround = time - arr[idx]->arrival;

        totalWT += arr[idx]->waiting;
        totalTAT += arr[idx]->turnaround;
        push(s, arr[idx]->pid);

        cout << "Process " << arr[idx]->pid
             << " | Waiting Time = " <<"<" << arr[idx]->waiting<<">"
             << " | Turnaround Time = " << "<" <<arr[idx]->turnaround <<">"<< endl;

        done[idx] = true;
        completed++;
    }

    cout << "Average Waiting Time = " << "<" <<totalWT / n <<">"<< endl;
    cout << "Average Turnaround Time = " <<"<" << totalTAT / n <<">"<< endl;
    printStack(s);
}

//Priority Scheduling (Non-preemptive) =
void PriorityScheduling(Process* head) {
    int time = 0, completed = 0;
    int n = countProcesses(head);
    float totalWT = 0, totalTAT = 0;
    bool done[50] = {false};
    Process* arr[50];
    Stack s; initStack(s);

    Process* temp = head;
    for (int i = 0; temp; i++, temp = temp->next) arr[i] = temp;

    cout << "\n--- Priority Scheduling ---\n";

    while (completed < n) {
        int idx = -1, best = 9999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && arr[i]->arrival <= time && arr[i]->priority < best) {
                best = arr[i]->priority;
                idx = i;
            }
        }
if (idx == -1) { time++; continue; }

        arr[idx]->waiting = time - arr[idx]->arrival;
        time += arr[idx]->burst;
        arr[idx]->turnaround = time - arr[idx]->arrival;

        totalWT += arr[idx]->waiting;
        totalTAT += arr[idx]->turnaround;
        push(s, arr[idx]->pid);

        cout << "Process " << arr[idx]->pid
             << " | Waiting Time = " << arr[idx]->waiting
             << " | Turnaround Time = " << arr[idx]->turnaround << endl;

        done[idx] = true;
        completed++;
    }

    cout << "Average Waiting Time = " << totalWT / n << endl;
    cout << "Average Turnaround Time = " << totalTAT / n << endl;
    printStack(s);
}

// Round Robin (Preemptive)
void RoundRobin(Process* head, int quantum) {
    int n = countProcesses(head);
    Process* arr[50];
    Process* temp = head;
    for (int i = 0; temp; i++, temp = temp->next) arr[i] = temp;

    for (int i = 0; i < n; i++) arr[i]->remaining = arr[i]->burst;

    int time = 0, completed = 0;
    bool inQueue[50] = {false};
    int queue[50], front = 0, rear = 0; // simple array queue
    Stack s; initStack(s);

    // Push processes which arrived at time 0
    for (int i = 0; i < n; i++) if (arr[i]->arrival <= time) { queue[rear++] = i; inQueue[i] = true; }

    cout << "\n--- Round Robin (Preemptive) Scheduling ---\n";

    while (completed < n) {
        if (front == rear) { time++; // idle CPU
            for (int i = 0; i < n; i++)
                if (!inQueue[i] && arr[i]->arrival <= time) { queue[rear++] = i; inQueue[i] = true; }
            continue;
        }

        int idx = queue[front++];
        Process* p = arr[idx];
        int runTime = (p->remaining > quantum) ? quantum : p->remaining;
        p->remaining -= runTime;
        time += runTime;
        push(s, p->pid);

        for (int i = 0; i < n; i++)
            if (!inQueue[i] && arr[i]->arrival <= time) { queue[rear++] = i; inQueue[i] = true; }

        if (p->remaining == 0) {
            p->turnaround = time - p->arrival;
            p->waiting = p->turnaround - p->burst;
            completed++;
        } else { queue[rear++] = idx; } // re-add to queue
    }

    // Print results
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        cout << "Process " << arr[i]->pid
             << " | Waiting Time = " << arr[i]->waiting
             << " | Turnaround Time = " << arr[i]->turnaround << endl;
        totalWT += arr[i]->waiting;
        totalTAT += arr[i]->turnaround;
    }
    cout << "Average Waiting Time = " << totalWT / n << endl;
    cout << "Average Turnaround Time = " << totalTAT / n << endl;
    printStack(s);
}

int main() {
    int n, quantum;
    Process* head = NULL;

    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Process p;
        cout << "\nProcess " << i + 1 << endl;
        cout << "ID (single letter): "; cin >> p.pid;
        cout << "Arrival Time: "; cin >> p.arrival;
        cout << "Burst Time: "; cin >> p.burst;
        cout << "Priority: "; cin >> p.priority;
        p.remaining = p.burst;
        p.waiting = p.turnaround = 0;
        p.next = NULL;
        addProcess(head, p);
    }

    cout << "\nEnter Time Quantum for Round Robin: ";
    cin >> quantum;

    FCFS(head);
    SJF(head);
    PriorityScheduling(head);
    RoundRobin(head, quantum);

    return 0;
}
