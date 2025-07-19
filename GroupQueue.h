#ifndef GROUPQUEUE_H
#define GROUPQUEUE_H

#include "Group.h"

using namespace std;

class GroupQueue {
	private:
		// Queue to hold groups
		queue<Group> groupQueue;
		
	public:
		GroupQueue() {}
		~GroupQueue() {}

		// Function to get the queue itself
		queue<Group>& getQueue() {return groupQueue;}

		// Cancel a reservation by queue position
		bool cancelReservation(int queuePosition);

		// Function to save the queue to a file
		// The file will be overwritten each time this function is called.
		void saveQueueToFile();

		// Function to load the queue from a file
		void loadQueueFromFile();

		// Append a group to the queue
		void appendToQueue(Group group);
};

#endif
