#pragma once
#include <string>

using namespace std;

class User
{
private:
	//학번받는 string 타입 변수
	string school_id;
	//학과 받는 string 타입 변수
	string department;
	//총 이수 학점을 받는 int타입 변수
	unsigned int total_credit;
	//졸업가능여부를 true false로 받는 bool타입 변수
	bool can_graduation;
public:
	//학번과 학과 검색했을때 없는경우 새로 만들어야 하므로, 총 이수 학점에는 0을, 졸업가능 여부에는 false를 넣어주는 생성자를 만들어줍니다.
	User(string school_id, string department);
	//학번과 학과를 입력 받았을 때 작동하는 생성자
	User(string school_id, string department, bool can_graduation);
	//default소멸자.
	~User();
	//학번을 Get 함수
	string getSchoolId();
	//학과를 Get하는 함수.
	string getDepartment();
	//총 이수 학점을 Get하는 함수.
	int getTotalCredit();
	//졸업가능여부를 Get하는 함수.
	bool getCangraduation();
	//학번을 set하는 함수.
	void setSchoolId(string school_id);
	//학과를 set하는 함수
	void setDepartment(string department);
	//총 이수학점을 set하는 함수.
	void setTotalCredit(int credit);
	//졸업가능여부를 set하는 함수.
	void setCangraduation(bool can_graduation);
	//총 이수학점에 더하는 함수
	void addTotalCredit(int credit);
};

