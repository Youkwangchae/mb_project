#include "Yoram.h"
#include <iostream>


Yoram::Yoram()
{
	for (int i = 0; i < 8; i++) {
		vector<Subject> vec;
		subjects.push_back(vec);
	}
}

Yoram::~Yoram()
{
}

vector<Subject> Yoram::getSubjects(int index)
{
	return subjects[index];
}

void Yoram::pushSubject(Subject subject, int index)
{
	subjects[index].push_back(subject);
}

int Yoram::getTotalCredit()
{
	return total_credit;
}

void Yoram::setTotalCredit(int credit)
{
	total_credit = credit;
}
