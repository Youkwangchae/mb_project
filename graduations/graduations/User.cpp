#include "User.h"


User::User(string school_id, string department)
	:User(school_id, department, false)
{
}

User::User(string school_id, string department, bool can_graduation)
	: school_id(school_id), department(department), can_graduation(can_graduation), total_credit(0)
{
}

User::~User()
{
}

string User::getSchoolId()
{
	return school_id;
}

string User::getDepartment()
{
	return department;
}

int User::getTotalCredit()
{
	return total_credit;
}

bool User::getCangraduation()
{
	return can_graduation;
}

void User::setSchoolId(string school_id)
{
	this->school_id = school_id;
}

void User::setDepartment(string department)
{
	this->department = department;
}

void User::setTotalCredit(int credit)
{
	this->total_credit = credit;
}

void User::setCangraduation(bool can_graduation)
{
	this->can_graduation = can_graduation;
}

void User::addTotalCredit(int credit)
{
	this->total_credit += credit;
}
