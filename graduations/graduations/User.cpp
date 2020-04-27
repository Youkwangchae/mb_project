#include "User.h"


User::User(string classof, string department)
	:User(classof, department, 0, false)
{
}

User::User(string classof, string department, int credit, bool can_graduation)
	: classof(classof), department(department), credit(credit), can_graduation(can_graduation)
{
}

User::~User()
{
}
