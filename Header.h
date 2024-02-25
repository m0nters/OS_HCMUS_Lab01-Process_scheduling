#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

struct Process
{
	int id = 0;
	int arrival_time = 0;
	queue<int> CPU_burst_time;
	queue<int> resource_usage_time;
	int turn_around_time = 0;
	int waiting_time = 0;

	int priority = 0; // for priority_queue problems (SRTN & SJF)
};

struct comparator { // TOOL FOR PRIORITY_QUEUE PROBLEMS
	bool operator()(const Process* a, const Process* b) const {
		// Prioritize based on the cpu_burst_time_left: the smaller, the more prioritized
		if (a->CPU_burst_time.front() != b->CPU_burst_time.front())
			return a->CPU_burst_time.front() > b->CPU_burst_time.front();

		// If above condition is tie, prioritize based on "priority" values: the higher, the more prioritized
		return a->priority < b->priority;
	}
};


void readFile(istream& is, int& algorithm_type, int& num_of_process, vector <Process>& processes, int& quantum);
void writeFile(ostream& os, vector <Process> processes, vector <string> CPU_chart, vector <string> R_chart);

void FCFS(vector<Process> processes, ostream& os);
void RR(vector<Process> processes, const int& quantum, ostream& os);
void SJF(vector<Process> processes, ostream& os);
void SRTN(vector<Process> processes, ostream& os);