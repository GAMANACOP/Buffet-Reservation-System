#include "GroupQueue.h"
#include "Group.h"

#include <string>
#include <fstream>
#include <iostream>

string DEFAULT_QUEUE_FILENAME = "BRSQueue.txt";

using namespace std;

// Removes the group from the queue by finding the representative's name. 
// It needs to traverse the queue. 
// To do so, create a temporary copy of the queue.
// Unless the group is equal to the representative name, pop from the original queue and push a copy to the temporary.
// Then assign original with temp;
void GroupQueue::cancelReservation(string representativeName) {
    queue<Group> tempQueue; // This will hold the groups we want to keep
    bool found = false;

    // Iterate through the original queue
    while (!groupQueue.empty()) {
        Group currentGroup = groupQueue.front(); // Get the front group
        groupQueue.pop(); // Remove it from the original queue

        // If this is NOT the group to cancel, push it to the temporary queue
        if (currentGroup.getRepresentativeName() != representativeName) {
            tempQueue.push(currentGroup);
        } else {
            // This is the group to cancel
            found = true;
            cout << "Reservation for '" << representativeName << "' cancelled." << endl;
        }
    }

    // After iterating through all elements, assign the temporary queue back
    // to the original groupQueue. This effectively removes the cancelled group(s).
    groupQueue = tempQueue;

    if (!found) {
        cout << "No reservation found for '" << representativeName << "'." << endl;
    }
}

void GroupQueue::appendToQueue(Group group) {
	groupQueue.push(group);
}

// Truncates the file to save the current queue.
void GroupQueue::saveQueueToFile() {
	ofstream queueFile(DEFAULT_QUEUE_FILENAME, ios::trunc);
	
	queue<Group> tempCopy = groupQueue;
	
	while (!tempCopy.empty()) {
		
		Group front = tempCopy.front();
		
		string repName = front.getRepresentativeName();
		int childCount = front.countMember("Child");
		int adultCount = front.countMember("Adult");
		int seniorCount = front.countMember("Senior");
		// File structure:
		// representative_name
		// child_count
		// adult_count
		// senior_count
		queueFile 	<< repName << "\n"
					<< childCount << "\n"
					<< adultCount << "\n"
					<< seniorCount;
					
		tempCopy.pop();
		
		if (!tempCopy.empty()) {
			queueFile << "\n";
		}
	}
	
	queueFile.close();
}


void GroupQueue::loadQueueFromFile() {
	ifstream queueFile(DEFAULT_QUEUE_FILENAME);
	
	if (queueFile.is_open()) {
		Group savedGroup;
		string savedRepName = "";
		
		while (getline(queueFile, savedRepName)) {
			savedGroup.setRepresentativeName(savedRepName);
			
			int childCount, adultCount, seniorCount;
			queueFile >> childCount;
			queueFile >> adultCount;
			queueFile >> seniorCount;
			
			groupQueue.push(savedGroup);
		}
	}
	
	queueFile.close();
}
