#include "Header.h"

void SRTN(vector<Process>& processes, ostream& os) {
	int time = 0;

	// gantt chart for the result
	vector<string> CPU_chart;
	vector<string> R_chart;

	priority_queue<Process*, vector<Process*>, comparator> CPU_queue;
	queue<Process*> R_queue;

	Process* current_CPU_used_process = NULL;
	Process* current_R_used_process = NULL;

	int finished_processes_num = 0; // the number of the processes that have finished
	unordered_map<Process*, int> last_time_put_into_CPU_queue; // for waiting time calculation
	for (int i = 0; i < processes.size(); ++i)
		last_time_put_into_CPU_queue[&processes[i]] = processes[i].arrival_time;

	int process_count = 0; // optimization: avoid abundant check to add into ready queue, reduce O(n)
	while (finished_processes_num != processes.size()) {
		// READY QUEUE CONFLICT RESOLVE
		for (int i = process_count; i < processes.size(); i++) {
			if (processes[i].arrival_time == time) {
				processes[i].priority.cpu = 3; // HIGHEST PRIORITY (3)
				processes[i].priority.time = time;
				CPU_queue.push(&processes[i]);
				++process_count;
			}
		}

		// if there's a (newer) process with smaller or equal cpu burst time than the current processn at the moment
		if (current_CPU_used_process && !CPU_queue.empty() && CPU_queue.top()->CPU_burst_time.front() <= current_CPU_used_process->CPU_burst_time.front()) {

			// IMMEDIATELY terminate the current process by pushing it into queue
			current_CPU_used_process->priority.cpu = 1; // LOWEST PRIORITY (1)
			CPU_queue.push(current_CPU_used_process);
			last_time_put_into_CPU_queue[current_CPU_used_process] = time; // not +1 because in this case we need the first end of the time block
			current_CPU_used_process = NULL;

		}

		// take the next process in ready queue -> CPU 
		if (!current_CPU_used_process && !CPU_queue.empty()) {
			current_CPU_used_process = CPU_queue.top();
			CPU_queue.pop();
			current_CPU_used_process->waiting_time += time - last_time_put_into_CPU_queue[current_CPU_used_process];
		}

		// take the next process in R_queue to work with
		if (!current_R_used_process && !R_queue.empty()) { // if there isn't any process running in the R right now
			current_R_used_process = R_queue.front(); // pick the next one waiting in the queue (if the queue is not empty)
			R_queue.pop();
		}

		// draw the CPU gantt chart
		if (current_CPU_used_process) { // if there's a process running in CPU
			int index = current_CPU_used_process->id - 1;
			CPU_chart.push_back(to_string(current_CPU_used_process->id));

			int current_CPU_burst_time = --current_CPU_used_process->CPU_burst_time.front();
			if (!current_CPU_burst_time) {
				current_CPU_used_process->CPU_burst_time.pop();
				if (!current_CPU_used_process->resource_usage_time.empty()) // check if there's next R, if have, put into R_ready_queue
					R_queue.push(current_CPU_used_process);
				else { // otherwise, the process is done! now we can calculate the turn around time
					++finished_processes_num;
					current_CPU_used_process->turn_around_time = time - current_CPU_used_process->arrival_time + 1;
				}

				current_CPU_used_process = NULL;
			}
		}
		else
			CPU_chart.push_back("_");

		// draw the R gantt chart
		// FCFS ALWAYS!
		if (current_R_used_process) { // if there's a process running in R
			int index = current_R_used_process->id - 1;
			R_chart.push_back(to_string(current_R_used_process->id));
			int current_R_usage_time = --current_R_used_process->resource_usage_time.front();

			if (!current_R_usage_time) {
				current_R_used_process->resource_usage_time.pop();
				last_time_put_into_CPU_queue[current_R_used_process] = time + 1; // for example time is 7 but IN FACT the time the process get out of the R_queue is 8! since we are considering time as BLOCKS!
				if (!current_R_used_process->CPU_burst_time.empty()) { // check if there's next cpu, if have, put into CPU_ready_queue, ALSO CHECK FOR CONFLICT IN THE NEXT SECOND
					current_R_used_process->priority.cpu = 2; // MEDIUM PRIORITY (2)
					CPU_queue.push(current_R_used_process);
				}
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