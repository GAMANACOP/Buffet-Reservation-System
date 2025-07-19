#include <string>
#include <list>
#include <queue>

#ifndef GROUP_H
#define GROUP_H

using namespace std;

class Member {
	// Member class represents a member of the group
	// It contains the member type (Child, Adult, Senior) and their discount rate
	private:
		string memberType;
		float discount;
	public:
		Member() : memberType(""), discount(0.0f) {}

		// Setters for memberType and discount
		void setMemberType(string mt) { memberType = mt; }
		void setDiscount(float d) { discount = d; }
		
		// Getters for memberType and discount
		string getMemberType() const {return memberType;}
		float getDiscount() const {return discount;}
};

class Group {
	private:
		list<Member> members;

		// Counters for different member types
		int childCount;
		int adultCount;
		int seniorCount;

		// Name of the group representative
		string representativeName;
		
	public:
		
		Group();
		~Group();
				
		void setRepresentativeName(string);
		string getRepresentativeName() const {return representativeName;}
		
		// Functions for adding member
		void addChildMember();
		void addAdultMember();
		void addSeniorMember();
		
		// Function for removing member
		void removeMember(std::string);
		
		// Function to confirm reservation
		void confirmReservation(queue<Group> &);
		
		// Functions for computing payments
		float computeTotalPayment() const;
		float computeMemberTotalFee(string memberType) const;
		
		// Functions for counting members
		int countMember(string) const;
		int countTotalMembers() const {return adultCount + childCount + seniorCount;}
};

#endif
