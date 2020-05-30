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
	//�������� ����ִ� ����
	vector<vector<Subject>> subjects;
	//�� �̼� ����
	int total_credit;
public:
	Yoram();
	~Yoram();
	
	vector<Subject> getSubjects(int index);
	void pushSubject(Subject subject, int index);

	int getTotalCredit();
	void setTotalCredit(int credit);
};