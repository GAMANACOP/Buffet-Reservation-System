#ifndef GROUP_H
#define GROUP_H

#include <string>

using namespace std;

class Member {
	private:
		string memberType;
		float discount;
	public:
		void setMemberType(string mt) { memberType = mt; }
		void setDiscount(float d) { discount = d; }
		
		string getMemberType() const {return memberType;}
		float getDiscount() const {return discount;}
};



class Group {
	private:
		struct MemberNode {
			Member data;
			MemberNode *next;
		};
		
		MemberNode *head;
		string representativeName;

		void appendNode(Member);
		void deleteNode(string MemberType);
		
	public:
		
		int totalMembers;
		
		Group() {
			head = NULL;
			totalMembers = 0;
		}
		
		void setRepresentativeName(std::string);
		void AddChild();
		void AddAdult();
		void AddSenior();
		void RemoveMember(std::string);
		void ConfirmReservation();
		int countChild() const;
		int countSenior() const;
		int countAdult() const;
};

#endif
