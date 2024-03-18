#include "Header.h"

void RR(vector<Process>& processes, const int& quantum, ostream& os) {
	int time = 0;

	// gantt chart for the result
	vector<string> CPU_chart;
	vector<string> R_chart;

	Comparator orderComparator(ORDER_COMPARISON);
	priority_queue<Process*, vector<Process*>, Comparator> CPU_queue(orderComparator);
	queue<Process*> R_queue;

	Process* current_CPU_used_process = NULL;
	Process* current_R_used_process = NULL;

	int finished_processes_num = 0; // the number of the processes that have finished

	int processes_added_to_CPU_queue_count = 0; // optimization: avoid abundant check to add into ready queue, reduce O(n)
	int time_slice;
	while (finished_processes_num != processes.size()) {
		for (int i = processes_added_to_CPU_queue_count; i < processes.size(); i++) {
			if (processes[i].arrival_time == time) {
				processes[i].priority_attributes.last_time_push_in_CPU_queue = time;
				CPU_queue.push(&processes[i]);
				++processes_added_to_CPU_queue_count;
			}
			else
				break;
		}

		// take the next process in ready queue -> CPU
		if (!current_CPU_used_process && !CPU_queue.empty()) { // if there isn't any process running in the CPU right now
			time_slice = quantum;
			current_CPU_used_process = CPU_queue.top(); // pick the next one waiting in the queue (if the queue is not empty)
			CPU_queue.pop();
			current_CPU_used_process->waiting_time += time - current_CPU_used_process->priority_attributes.last_time_push_in_CPU_queue;
		}

		// take the next process in R_queue to work with
		if (!current_R_used_process && !R_queue.empty()) { // if there isn't any process running in the R right now
			current_R_used_process = R_queue.front(); // pick the next one waiting in the queue (if the queue is not empty)
			R_queue.pop();
		}

		// draw the CPU gantt chart
		if (current_CPU_used_process) { // if there's a process running in CPU
			CPU_chart.push_back(to_string(current_CPU_used_process->id));
			if (!--current_CPU_used_process->CPU_burst_time.front()) { // put into resource_queue
				current_CPU_used_process->CPU_burst_time.pop();
				current_CPU_used_process->priority_attributes.last_time_get_out_CPU = time + 1;
				if (!current_CPU_used_process->resource_usage_time.empty()) // check if there's next R, if have, put into R_ready_queue
					R_queue.push(current_CPU_used_process);
				else { // otherwise, the process is done! now we can calculate the turn around time
					++finished_processes_num;
					current_CPU_used_process->turn_around_time = time - current_CPU_used_process->arrival_time + 1;
				}
				current_CPU_used_process = NULL;
			}
			else if (!--time_slice) { // put into CPU_queue
				current_CPU_used_process->priority_attributes.last_time_get_out_CPU = current_CPU_used_process->priority_attributes.last_time_push_in_CPU_queue = time + 1; // when out of time slice, it first pop out the CPU, then push back into the CPU_queue at the same time!
				CPU_queue.push(current_CPU_used_process);
				current_CPU_used_process = NULL;
			}
		}
		else
			CPU_chart.push_back("_");

		// draw the R gantt chart
		// FCFS ALWAYS!
		if (current_R_used_process) { // if there's a process running in R
			R_chart.push_back(to_string(current_R_used_process->id));
			if (!--current_R_used_process->resource_usage_time.front()) {
				current_R_used_process->resource_usage_time.pop();
				current_R_used_process->priority_attributes.last_time_push_in_CPU_queue = time + 1; // for example time is 7 but IN FACT the time the process get out of the R_queue is 8! since we are considering time as BLOCKS!
				if (!current_R_used_process->CPU_burst_time.empty()) // check if there's next cpu, if have, put into CPU_ready_queue, ALSO CHECK FOR CONFLICT IN THE NEXT SECOND
					CPU_queue.push(current_R_used_process);
				else { // otherwise, the process is done! now we can calculate the turn around time
					++finished_processes_num;
					current_R_used_process->turn_around_time = time - current_R_used_process->arrival_time + 1;
				}
				current_R_used_process = NULL;
			}
		}
		else
			R_chart.push_back("_");
		// ==========================================================
		++time;
	}
	writeFile(os, processes, CPU_chart, R_chart);
}