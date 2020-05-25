#include "Subject.h"
#include<iostream>


Subject::Subject()
{
}

Subject::Subject(string name, int subject_score)
	:Subject(name, subject_score, 0)
{
}

Subject::Subject(string name, int subject_score, int semester)
	: name(name), subject_score(subject_score), semester(semester)
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

void Subject::setSemester(int semester)
{
	this->semester = semester;
}

string Subject::getName()
{
	return this->name;
}

int Subject::getSubjectScore()
{
	return this->subject_score;
}

int Subject::getSemester()
{
	return this->semester;
}

