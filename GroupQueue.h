#ifndef GROUPQUEUE_H
#define GROUPQUEUE_H

#include "Group.h"

using namespace std;

class GroupQueue {
	private:
		queue<Group> groupQueue;
		
	public:
		queue<Group>& getQueue() {return groupQueue;}
		bool cancelReservation(string representativeName);
		void saveQueueToFile();
		void loadQueueFromFile();
		void appendToQueue(Group group);
};

#endif
