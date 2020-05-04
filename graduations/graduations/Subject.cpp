#include "Subject.h"
#include<iostream>


Subject::Subject()
{
}

Subject::Subject(string name, int subject_score)
	:name(name), subject_score(subject_score)
{
}

Subject::~Subject()
{
}

void Subject::setName(string name)
{
	this->name = name;
}

void Subject::setSubjectScore(int subject_score)
{
	this->subject_score = subject_score;
}

string Subject::getName()
{
	return this->name;
}

int Subject::getSubjectScore()
{
	return this->subject_score;
}

