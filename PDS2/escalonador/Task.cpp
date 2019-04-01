#include "Task.hpp"

Task::Task(int _id, int _arr, int _dur){
	id = _id;
	arrival = _arr;
	duration = _dur;
}

TaskScheduler::TaskScheduler(int _quant, std::vector<Task*> taskVector){
	quantum = _quant;
	tasksWaiting = taskVector;
}

void TaskScheduler::displayResult(std::vector<Task*> taskVector){
	for (int i = 0; i < int(taskVector.size()); ++i){
		std::cout << "Task " << taskVector[i]->id;
		std::cout << ", Duration: [" << taskVector[i]->arrival << ", ";
		std::cout << "<<final>>" << "]\n";
	}
}

// void TaskScheduler::RoundRobin(){
// 	int time = 0;
// 	for (int i = 0; i < 20; ++i){
		
// 	}
// }
