#include "Subject.h"



Subject::Subject()
{
}

Subject::Subject(string name, int subject_score, bool is_take_class)
	:name(name), subject_score(subject_score), is_take_class(is_take_class)
{
}

void Subject::print()
{
	cout << "과목명 : " << name << endl;
	cout << "학점 : " << subject_score << endl;
	cout << "수강여부 : " << is_take_class << endl;
}

void Subject::setName(string name)
{
	this->name = name;
}

void Subject::setSubjectScore(int subject_score)
{
	this->subject_score = subject_score;
}

void Subject::setIsTakeClass(bool is_take_class)
{
	this->is_take_class = is_take_class;
}

string Subject::getName()
{
	return this->name;
}

int Subject::getSubjectScore()
{
	return this->subject_score;
}

bool Subject::getIsTakeClass()
{
	return this->is_take_class;
}

Subject::~Subject()
{
}
