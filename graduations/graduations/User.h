/*
	4/27일 작성자: 201911144 강건우
	유저 정보를 관리하는 클래스 변수
	관리하는 정보로는 총 4가지가 있다.
	1. 사용자의 학번
	2. 사용자의 학과
	3. 총 이수학점
	4. 졸업가능여부
	*/
#pragma once
#include <iostream>
#include <string>
using namespace std;
class User
{
private:
	//학번받는 string 타입 변수
	string classof;
	//학과 받는 string 타입 변수
	string department;
	//총 이수 학점을 받는 int타입 변수
	unsigned int credit;
	//졸업가능여부를 true false로 받는 bool타입 변수
	bool can_graduation;
public:
	//학번과 학과 검색했을때 없는경우 새로 만들어야 하므로, 총 이수 학점에는 0을, 졸업가능 여부에는 false를 넣어주는 생성자를 만들어줍니다.
	User(string classof, string department);
	//학번과 학과를 입력 받았을 때 작동하는 생성자
	User(string classof, string department, int credit, bool can_graduation);
	//default소멸자.
	~User();
	//학번을 Get 함수
	string getClassof() { return classof; }
	//학과를 Get하는 함수.
	string getDepartment() { return department; }
	//총 이수 학점을 Get하는 함수.
	int getCredit() { return credit; }
	//졸업가능여부를 Get하는 함수.
	bool getCangraduation() { return can_graduation; }
	//학번을 set하는 함수.
	void setClassof(string classof) { this->classof = classof; }
	//학과를 set하는 함수
	void setDepartment(string department) { this->department = department; }
	//총 이수학점을 set하는 함수.
	void setCredit(int credit) { this->credit = credit; }
	//졸업가능여부를 set하는 함수.
	void setCangraduation(bool can_graduation) { this->can_graduation = can_graduation; }
};

