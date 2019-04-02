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

void TaskScheduler::RoundRobin(){
	// int time = 0;
	int quant = this->quantum;

	for (int time = 0; time < 20; ++time){ // CONTA O TEMPO
		for (int i = 0; i < int(this->tasksWaiting.size()); ++i){
			Task *current = this->tasksWaiting[i];
			if(current->inQueue){
				if(current->duration-quant > 0){
					current->end = time;
					current->duration = duration-quant;
				} else if(current->duration-quant == 0){
					current->end = time;
					current->duration = duration-quant;
				}
			}
			
		}
	}
}
