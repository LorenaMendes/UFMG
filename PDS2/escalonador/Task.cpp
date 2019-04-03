#include "Task.hpp"
#include <list>

using namespace std;

bool compareByArrivalTime(Task *a, Task *b){
    if(a->arrival == b->arrival) return a->id < b->id; 
    return a->arrival < b->arrival;
}

Task::Task(int _id, int _arr, int _dur){
	id = _id;
	arrival = _arr;
	duration = _dur;
	inQueue = false;
	end = 0;
}

TaskScheduler::TaskScheduler(int _quant, vector<Task*> taskVector){
	quantum = _quant;
	tasksWaiting = taskVector;
	this->totalTasks = int(tasksWaiting.size());
	// ORDENANDO POR ARRIVAL TIME E ID
	sort(taskVector.begin(), taskVector.end(), compareByArrivalTime);
}

void TaskScheduler::displayResult(vector<Task*> taskVector){
	for (int i = 0; i < int(taskVector.size()); ++i){
		cout << "Task " << taskVector[i]->id;
		cout << ", Duration: [" << taskVector[i]->arrival << ", ";
		cout << taskVector[i]->end << "]\n";
	}
}

void TaskScheduler::checkIncomingTasks(int time){
	// OLHO SE TEM TAREFAS PARA ANTES DE TIME
	// cout << "time: " << time << "\n";
	for (unsigned int i = 0; i < this->tasksWaiting.size(); i++){
		// cout << "arrival: " << this->tasksWaiting[i]->arrival << "\n";
		if (this->tasksWaiting[i]->arrival <= time && this->tasksWaiting[i]->inQueue == false){
			// SE TEM, EU COLOCO NA LISTA
			// cout << "sim, esse tem arrival menor que " << time << ": " << this->tasksWaiting[i]->id << endl;
			this->schedulerQueue.push_back(this->tasksWaiting[i]);
			this->tasksWaiting[i]->inQueue = true;
		}
	}
}

void TaskScheduler::RoundRobin(){
	int quant = this->quantum;
	int time = 0;
	
	this->checkIncomingTasks(time);
	list <Task*> :: iterator it = schedulerQueue.begin();

	while(it != schedulerQueue.end()){
	
		if(totalTasks == 0) break;
	
		this->showlist(schedulerQueue);
		
		if((*it)->duration >= quant){
		
			for (int i = 0; i < quant; i++){
				(*it)->duration--;
				time++;
				this->checkIncomingTasks(time);
			}
			schedulerQueue.pop_front();
			if((*it)->duration > 0){
				schedulerQueue.push_back(*it);
				it = schedulerQueue.begin();
			} else{
				(*it)->end = time;
				this->totalTasks--;
			}

		}
		
		else {
			for (int i = 0; i < (*it)->duration; i++){
				(*it)->duration--;
				time++;
				this->checkIncomingTasks(time);
			}
			schedulerQueue.pop_front();
			(*it)->end = time;
			this->totalTasks--;
		}
		// cout << "nova duração: " << (*it)->duration << endl;
		
		it++;

		if(it == schedulerQueue.end()){
			if(schedulerQueue.begin() == schedulerQueue.end()){
				cout << "lista vazia!\n";
				break;
			}
			else{
				// cout << "recomeçando!\n";
				it = schedulerQueue.begin();
			}
		}

	}
	cout << "acabou! Tempo total: " << time << endl;
}

//function for printing the elements in a list 
void TaskScheduler::showlist(list <Task*> g) { 
    list <Task*> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it) 
        cout << " " << (*it)->id << "(" << (*it)->duration << ")"; 
    cout << '\n'; 
} 