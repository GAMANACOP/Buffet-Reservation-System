#include "Group.h"
#include "DefaultValues.h"

#include <iostream>
#include <string>
#include <list>
#include <deque>
#include <fstream>

using namespace std;

// Default constructor for Group class.
// It initializes the counters for different member types to zero.
Group::Group() : childCount(0), adultCount(0), seniorCount(0) {}

// Destructor for Group class.
// It clears the members list to free up resources.
Group::~Group() {
	members.clear();
}

// Removes a member of the specified type from the group.
// It searches through the members list and removes the first member that matches the specified type.
void Group::removeMember(string MemberType) {
	list<Member>::iterator it;
	for (it = members.begin(); it != members.end(); ++it) {
		if (it->getMemberType() == MemberType) {
			members.erase(it);
			if (MemberType == "Child") {
				childCount--;
			} else if (MemberType == "Adult") {
				adultCount--;
			} else if (MemberType == "Senior") {
				seniorCount--;
			}
			return;
		}
	}
	cout << "No member of type " << MemberType << " found." << endl;
}

// Confirms the reservation of the group by pushing it to the provided queue.
void Group::confirmReservation(queue<Group> &groupQueue) {
	groupQueue.push(*this);
}

// Adds a child member to the group.
void Group::addChildMember() {
	Member newMember;
	newMember.setMemberType("Child");
	newMember.setDiscount(DEFAULT_CHILD_DISCOUNT);
	members.push_back(newMember);
	childCount++;
}

// Adds an adult member to the group.
void Group::addAdultMember() {
	Member newMember;
	newMember.setMemberType("Adult");
	newMember.setDiscount(DEFAULT_ADULT_DISCOUNT);
	members.push_back(newMember);
	adultCount++;
}

// Adds a senior member to the group.
void Group::addSeniorMember() {
	Member newMember;
	newMember.setMemberType("Senior");
	newMember.setDiscount(DEFAULT_SENIOR_DISCOUNT);
	members.push_back(newMember);
	seniorCount++;
}

// Sets the representative name for the group.
void Group::setRepresentativeName(string repName) {
	representativeName = repName;
}

// Returns the count of members of the specified type.
int Group::countMember(string memberType) const {
	if (memberType == "Child") {
		return childCount;
	} else if (memberType == "Adult") {
		return adultCount;
	} else if (memberType == "Senior") {
		return seniorCount;
	}
}

// Computes the total fee for members of the specified type.
float Group::computeMemberTotalFee(string memberType) const {
	float payment = 0.0;
	list<Member>::const_iterator it;

	// Iterate through the members list and calculate the total fee for the specified member type
	for (it = members.begin(); it != members.end(); ++it) {
		if (it->getMemberType() == memberType) {
			payment += DEFAULT_FEE - (DEFAULT_FEE * it->getDiscount());
		}
	}
	return payment;
}

// Computes the total payment for the group by summing up the fees for all member types.
float Group::computeTotalPayment() const {
	return (computeMemberTotalFee("Child") + computeMemberTotalFee("Adult") + computeMemberTotalFee("Senior"));
}
