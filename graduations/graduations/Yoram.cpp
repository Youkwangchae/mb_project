#include "Yoram.h"
#include <iostream>


Yoram::Yoram()
{
}

Yoram::~Yoram()
{
}

vector<Subject> Yoram::getBasicLiberal()
{
	return basic_liberal;
}

vector<Subject> Yoram::getImproveLiberal()
{
	return improve_liberal;
}

vector<Subject> Yoram::getDesignationLiberal()
{
	return designation_liberal;
}

Subject Yoram::getSelectMajor()
{
	return select_major;
}

Subject Yoram::getSelectLiberal()
{
	return select_liberal;
}

vector<Subject> Yoram::getCompulsoryMajor()
{
	return compulsory_major;
}

vector<Subject> Yoram::getPassSubject()
{
	return pass_subject;
}

vector<Subject> Yoram::getCompulsorySubject()
{
	return compulsory_subject;
}

void Yoram::pushBasicLiberal(string name, int subject_score)
{
	basic_liberal.push_back(Subject(name, subject_score));
}

void Yoram::pushImproveLiberal(string name, int subject_score)
{
	improve_liberal.push_back(Subject(name, subject_score));
}

void Yoram::pushDesignationLiberal(string name, int subject_score)
{
	designation_liberal.push_back(Subject(name, subject_score));
}

void Yoram::setSelectMajor(string name, int subject_score)
{
	select_major.setName(name);
	select_major.setSubjectScore(subject_score);
}

void Yoram::setSelectLiberal(string name, int subject_score)
{
	select_liberal.setName(name);
	select_liberal.setSubjectScore(subject_score);
}

void Yoram::pushCompulsoryMajor(string name, int subject_score)
{
	compulsory_major.push_back(Subject(name, subject_score));
}

void Yoram::pushPassSubject(string name, int subject_score)
{
	pass_subject.push_back(Subject(name, subject_score));
}

void Yoram::pushCompulsorySubject(string name, int subject_score)
{
	compulsory_subject.push_back(Subject(name, subject_score));
}

int Yoram::getTotalCredit()
{
	return total_credit;
}

void Yoram::setTotalCredit(int credit)
{
	total_credit = credit;
}
