#include <iostream>
#include <fstream>
#include <string>
#include "Header.h"

int main(int argc, char* argv[]) {
	//if (argc != 3) {
	//	cout << "Usage: " << argv[0] << " <INPUT_FILE> <OUTPUT_FILE>" << endl;
	//	return 1;
	//}

	ifstream input_file("input.txt");
	ofstream output_file("output.txt");

	if (!input_file.is_open() || !output_file.is_open()) {
		cout << "Error opening files." << endl;
		return 1;
	}

	int algorithm_type, num_of_process, quantum;
	vector<Process> processes;

	// Read input file
	readFile(input_file, algorithm_type, num_of_process, processes, quantum);

	// Perform scheduling based on algorithm type
	switch (algorithm_type) {
	case 1:
		FCFS(processes, output_file);
		break;
	case 2:
		RR(processes, quantum, output_file);
		break;
	case 3:
		SJF(processes, output_file);
		break;
	case 4:
		SRTN(processes, output_file);
		break;
	default:
		cout << "Invalid algorithm type." << endl;
		break;
	}

	input_file.close();
	output_file.close();
}