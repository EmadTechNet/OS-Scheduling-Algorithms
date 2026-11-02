# CPU Scheduling Algorithms Simulator

A C++ simulation program implementing 4 core CPU scheduling algorithms in Operating Systems, comparing their performance based on Waiting Time and Turnaround Time.

---

### Academic Information

| Field | Details |
| :--- | :--- |
| **Institution** | Ar-Rasheed Smart University |
| **Author** | Emad Ahmad Mohammed Emad |
| **Supervisor** | Eng. Mohammed Al-Siani |
| **Subject** | Operating Systems — CPU Scheduling |

---

## Overview

In modern computing, managing CPU time among concurrent processes is essential. This project simulates and evaluates four classic CPU scheduling algorithms to measure system responsiveness and scheduling efficiency.

---

## Implemented Algorithms

### 1. First-Come, First-Served (FCFS)
* **Mechanism:** Processes are executed in the exact order of their arrival. It is strictly **Non-preemptive**.
* **Advantages:** Simple to implement; no prior knowledge of execution times required; strictly fair by arrival time.
* **Disadvantages:** High average waiting time; vulnerable to the **Convoy Effect**; not suitable for interactive environments.
* **Best Use Case:** Batch systems with similar execution durations.

---

### 2. Shortest Job First (SJF)
* **Mechanism:** Selects the waiting process with the smallest CPU burst time. Operates in **Non-preemptive** mode.
* **Advantages:** Delivers the theoretically minimal average waiting time; high CPU utilization; optimal for short tasks.
* **Disadvantages:** Risk of **Starvation** for long tasks; difficult to predict future execution times accurately.
* **Best Use Case:** Long-term batch environments where task durations are known in advance.

---

### 3. Priority Scheduling
* **Mechanism:** Allocates the CPU to the process with the highest priority (lowest numerical value). Operates in **Non-preemptive** mode.
* **Advantages:** Flexible control over vital tasks; well-suited for real-time environments; efficient critical resource allocation.
* **Disadvantages:** Starvation of lower-priority processes; risk of **Priority Inversion**; requires an **Aging** mechanism to mitigate starvation.
* **Best Use Case:** Real-time operating systems, industrial automation, and mission-critical applications.

---

### 4. Round Robin (RR)
* **Mechanism:** Assigns a fixed time slice (**Quantum**) to each ready process. It is **Preemptive**; uncompleted jobs are returned to the back of the queue.
* **Advantages:** High fairness across all tasks; completely eliminates starvation (**No Starvation**); excellent response time for interactive jobs.
* **Disadvantages:** Higher average waiting time than SJF; excessive **Context Switching Overhead** if the quantum is too small; degrades to FCFS behavior if the quantum is excessively large.
* **Best Use Case:** Time-sharing systems, interactive applications, and personal desktop computing.

---

## Comparison Summary

| Algorithm | Type | Starvation Risk | Response Time | Ideal Application |
| :--- | :---: | :---: | :---: | :--- |
| **FCFS** | Non-preemptive | None | Slow | Simple batch systems |
| **SJF** | Non-preemptive | High for long jobs | Optimal for short jobs | Pre-calculated batch workloads |
| **Priority** | Non-preemptive | High for low priority | Depends on priority | Real-time & critical control |
| **Round Robin** | Preemptive | None (Zero starvation) | Fast & interactive | Time-sharing systems |

---

## Build and Execution

Compile and run the single C++ source file (`project_final1.cpp`):

```bash
# Compilation
g++ project_final1.cpp -o scheduler

# Execution (Linux / macOS)
./scheduler

# Execution (Windows)
scheduler.exe
