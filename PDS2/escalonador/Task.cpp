#include "Task.hpp"
#include <list>
#define DEBUG 0

using namespace std;

bool compareByArrivalTime(Task *a, Task *b){
    if(a->arrival == b->arrival) return a->id < b->id; 
    return a->arrival < b->arrival;
}

bool compareById(Task *a, Task *b){
    return a->id < b->id; 
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
	totalTasks = 0;
}

void TaskScheduler::displayResult(vector<Task*> taskVector){
	sort(taskVector.begin(), taskVector.end(), compareById);
	for (int i = 0; i < int(taskVector.size()); ++i){
		cout << "Task " << taskVector[i]->id;
		cout << ", Duration: [" << taskVector[i]->arrival << ", ";
		cout << taskVector[i]->end << "]\n";
	}
}

void TaskScheduler::checkIncomingTasks(int time){
	int bola = 0;
	for (unsigned int i = 0; i < this->tasksWaiting.size(); i++){
		if (this->tasksWaiting[i]->arrival <= time && this->tasksWaiting[i]->inQueue == false){
			this->totalTasks++;
			this->schedulerQueue.push_back(this->tasksWaiting[i]);
			this->tasksWaiting[i]->inQueue = true;
			bola++;
		}
	}

	if (time == 0 && bola == 0){
		this->totalTasks++;
		this->schedulerQueue.push_back(this->tasksWaiting[0]);
		this->tasksWaiting[0]->inQueue = true;
		bola++;
	}
}

void TaskScheduler::RoundRobin(){
	sort(tasksWaiting.begin(), tasksWaiting.end(), compareByArrivalTime);
	
	int quant = this->quantum;
	int time = 0;
	
	this->checkIncomingTasks(time);
	
	list <Task*> :: iterator it = schedulerQueue.begin();
	while(it != schedulerQueue.end()){
		if(totalTasks == 0) break;
		if(DEBUG) this->showlist(schedulerQueue);
		
		if(DEBUG) cout << "atual: " << (*it)->id << "(" << (*it)->duration << "), ";
		if(DEBUG) cout << "tempo: " << time << endl;

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
			
			} else {
				(*it)->end = time;
				this->totalTasks--;
				it = schedulerQueue.begin();
			}
		}
		
		else {
			int var = (*it)->duration;
			for (int i = 0; i < var; i++){
				(*it)->duration--;
				time++;
				this->checkIncomingTasks(time);
			}
			(*it)->end = time;
			schedulerQueue.pop_front();
			it = schedulerQueue.begin();
			this->totalTasks--;
		}

		if(it == schedulerQueue.end()){
			if(schedulerQueue.begin() == schedulerQueue.end()) break;
			else it = schedulerQueue.begin();
		}
	}
}

void TaskScheduler::showlist(list <Task*> g) { 
    list <Task*> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it) 
        cout << " " << (*it)->id << "(" << (*it)->duration << ")"; 
    cout << '\n'; 
} 