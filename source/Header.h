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
		int last_time_push_in_CPU_queue = 0; // first in first out (FIFO)
		int last_time_get_out_CPU = 0; // in case both got pushed into CPU_queue at the same time, the one that got out CPU before first will have higher priority
	} priority; // keep this struct in case there are some additional priority rules in the future
};

struct time_comparator {
	bool operator()(Process* a, Process* b) {
		if (a->CPU_burst_time.front() != b->CPU_burst_time.front())
			return a->CPU_burst_time.front() > b->CPU_burst_time.front(); // FIRST PRIORITY: one has smaller CPU burst time
		if (a->priority.last_time_push_in_CPU_queue != b->priority.last_time_push_in_CPU_queue)
			return a->priority.last_time_push_in_CPU_queue > b->priority.last_time_push_in_CPU_queue; // SECOND PRIORITY: FIFO rule

		return a->priority.last_time_get_out_CPU > b->priority.last_time_get_out_CPU; // FINAL PRIORITY: if both above are tied, the one that got out CPU first will have higher priority
	}
};

struct order_comparator {
	bool operator()(Process* a, Process* b) {
		if (a->priority.last_time_push_in_CPU_queue != b->priority.last_time_push_in_CPU_queue)
			return a->priority.last_time_push_in_CPU_queue > b->priority.last_time_push_in_CPU_queue; // FIRST PRIORITY: FIFO rule (at this part, if there's no conflict exists, this is just like normal queue)
		if (a->priority.last_time_get_out_CPU != b->priority.last_time_get_out_CPU)
			return a->priority.last_time_get_out_CPU > b->priority.last_time_get_out_CPU; // if both got pushed into CPU_queue at the same time, the one that got out CPU first will have higher priority
	}
};

void readFile(istream& is, int& algorithm_type, int& num_of_process, vector<Process>& processes, int& quantum);
void writeFile(ostream& os, vector<Process>& processes, vector<string>& CPU_chart, vector<string>& R_chart);

void FCFS(vector<Process>& processes, ostream& os);
void RR(vector<Process>& processes, const int& quantum, ostream& os);
void SJF(vector<Process>& processes, ostream& os);
void SRTN(vector<Process>& processes, ostream& os);