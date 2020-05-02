#pragma once
#include <string>
#include <iostream>
using namespace std;

class Subject
{
private:
	string name;
	int subject_score;
	bool is_take_class;

public:
	Subject();
	Subject(string name, int subject_score, bool is_take_class);
	void print();
	void setName(string name);
	void setSubjectScore(int subject_score);
	void setIsTakeClass(bool is_take_class);
	string getName();
	int getSubjectScore();
	bool getIsTakeClass();
	~Subject();
};