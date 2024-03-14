#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_map>
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

	struct {
		int time_get_in_CPU_queue; 	// this is only needed for new processes added into the ready queue (which both have highest priority by default -- last_out_CPU_time = 0)
	} priority; // we create struct in case there are some additional priority rules in the future
};

extern unordered_map<Process*, int> last_out_CPU_time; // priority param for every algorithm (VERY IMPORTANT)

struct time_comparator {
	bool operator()(Process* a, Process* b) {
		if (a->CPU_burst_time.front() != b->CPU_burst_time.front())
			return a->CPU_burst_time.front() > b->CPU_burst_time.front();
		if (last_out_CPU_time[a] != last_out_CPU_time[b])
			return last_out_CPU_time[a] > last_out_CPU_time[b];

		return a->priority.time_get_in_CPU_queue < b->priority.time_get_in_CPU_queue; // LIFO rule, like stack
	}
};

struct order_comparator {
	bool operator()(Process* a, Process* b) {
		if (last_out_CPU_time[a] != last_out_CPU_time[b])
			return last_out_CPU_time[a] > last_out_CPU_time[b];

		return a->priority.time_get_in_CPU_queue > b->priority.time_get_in_CPU_queue; // FIFO rule, basically this part is like normal queue
	}
};

void readFile(istream& is, int& algorithm_type, int& num_of_process, vector<Process>& processes, int& quantum);
void writeFile(ostream& os, vector<Process>& processes, vector<string>& CPU_chart, vector<string>& R_chart);

void FCFS(vector<Process>& processes, ostream& os);
void RR(vector<Process>& processes, const int& quantum, ostream& os);
void SJF(vector<Process>& processes, ostream& os);
void SRTN(vector<Process>& processes, ostream& os);