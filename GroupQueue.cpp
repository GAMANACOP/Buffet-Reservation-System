#include <string>
#include <fstream>
#include <iostream>

#include "GroupQueue.h"
#include "Group.h"
#include "Utils.h"
#include "DefaultValues.h"

using namespace std;

// Cancels a reservation for a group based on the representative's name.
// This function iterates through the queue and removes the group with the matching representative name.
// It returns true if a group was found and cancelled, false otherwise.
bool GroupQueue::cancelReservation(string representativeName) {
    queue<Group> tempQueue; // This will hold the groups we want to keep
    bool found = false;

    // Iterate through the original queue
    while (!groupQueue.empty()) {
        Group currentGroup = groupQueue.front(); // Get the front group
        groupQueue.pop(); // Remove it from the original queue

        // If this is NOT the group to cancel, push it to the temporary queue
        if (toLowercase(currentGroup.getRepresentativeName()) != toLowercase(representativeName)) {
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
    
	// Save the updated queue to the file
    saveQueueToFile();
    
    return found;
}

// Appends a new group to the queue.
// This function is used to add a new group to the end of the queue.
void GroupQueue::appendToQueue(Group group) {
	groupQueue.push(group);
}

// Saves the current state of the queue to a file.
// The file will be overwritten each time this function is called.
// File structure:
// - representative_name
// - child_count
// - adult_count
// - senior_count
void GroupQueue::saveQueueToFile() {
	ofstream queueFile(DEFAULT_QUEUE_FILENAME, ios::trunc);
	
	queue<Group> tempCopy = groupQueue;
	
	// Check if the file is open before proceeding
	if (!queueFile.is_open()) {
		cerr << "Error: Could not open queue file for writing." << endl;
		return;
	}
	// Iterate through the queue and write each group's details to the file.
	// This will write the representative's name and the counts of each member type.
	while (!tempCopy.empty()) {
		
		Group front = tempCopy.front();
		
		string repName = front.getRepresentativeName();
		int childCount = front.countMember("Child");
		int adultCount = front.countMember("Adult");
		int seniorCount = front.countMember("Senior");
		
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

// Loads the queue from a file.
// This function reads the queue from a file and populates the groupQueue.
// The file structure is the same as used in saveQueueToFile.
void GroupQueue::loadQueueFromFile() {
	ifstream queueFile(DEFAULT_QUEUE_FILENAME);
	
	if (!queueFile.is_open()) {
		cerr << "Error: Could not open queue file." << endl;
		return;
	}

	// Checks if the file is open before proceeding
	if (queueFile.is_open()) {
		Group savedGroup;
		string savedRepName = "";
		
		// Read the file line by line
		while (getline(queueFile, savedRepName)) {
			savedGroup.setRepresentativeName(savedRepName);
			
			int childCount, adultCount, seniorCount;
			// Read the counts from the file
			queueFile >> childCount;
			queueFile >> adultCount;
			queueFile >> seniorCount;
			

			// Adds the members to the group based on the counts read from the file
			for (int i = 0; i < childCount; i++) {
				savedGroup.addChildMember();
			}
			for (int i = 0; i < adultCount; i++) {
				savedGroup.addAdultMember();
			}
			for (int i = 0; i < seniorCount; i++) {
				savedGroup.addSeniorMember();
			}
			
			groupQueue.push(savedGroup);
		}
	}
	
	// Close the file after reading
	queueFile.close();
}
