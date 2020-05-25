#pragma once
#include <string>

using namespace std;

class Subject
{
private:
	string name;
	int subject_score;
	int semester;

public:
	Subject();
	Subject(string name, int subject_score);
	Subject(string name, int subject_score, int semester);
	~Subject();
	void setName(string name);
	void setSubjectScore(int subject_score);
	void setSemester(int semester);
	string getName();
	int getSubjectScore();
	int getSemester();
};