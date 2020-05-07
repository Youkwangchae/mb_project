#pragma once
#include <string>

using namespace std;

class Subject
{
private:
	string name;
	int subject_score;

public:
	Subject();
	Subject(string name, int subject_score);
	~Subject();
	void setName(string name);
	void setSubjectScore(int subject_score);
	string getName();
	int getSubjectScore();
};