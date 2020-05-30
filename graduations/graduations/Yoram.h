#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>
#include "Subject.h"
using namespace std;
class Yoram
{
private:
	//모든과목이 들어있는 벡터
	vector<vector<Subject>> subjects;
	//총 이수 학점
	int total_credit;
public:
	Yoram();
	~Yoram();
	
	vector<Subject> getSubjects(int index);
	void pushSubject(Subject subject, int index);

	int getTotalCredit();
	void setTotalCredit(int credit);
};