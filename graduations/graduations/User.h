#pragma once
#include <string>

using namespace std;

class User
{
private:
	//�й��޴� string Ÿ�� ����
	string school_id;
	//�а� �޴� string Ÿ�� ����
	string department;
	//�� �̼� ������ �޴� intŸ�� ����
	unsigned int total_credit;
	//�������ɿ��θ� true false�� �޴� boolŸ�� ����
	bool can_graduation;
public:
	//�й��� �а� �˻������� ���°�� ���� ������ �ϹǷ�, �� �̼� �������� 0��, �������� ���ο��� false�� �־��ִ� �����ڸ� ������ݴϴ�.
	User(string school_id, string department);
	//�й��� �а��� �Է� �޾��� �� �۵��ϴ� ������
	User(string school_id, string department, bool can_graduation);
	//default�Ҹ���.
	~User();
	//�й��� Get �Լ�
	string getSchoolId();
	//�а��� Get�ϴ� �Լ�.
	string getDepartment();
	//�� �̼� ������ Get�ϴ� �Լ�.
	int getTotalCredit();
	//�������ɿ��θ� Get�ϴ� �Լ�.
	bool getCangraduation();
	//�й��� set�ϴ� �Լ�.
	void setSchoolId(string school_id);
	//�а��� set�ϴ� �Լ�
	void setDepartment(string department);
	//�� �̼������� set�ϴ� �Լ�.
	void setTotalCredit(int credit);
	//�������ɿ��θ� set�ϴ� �Լ�.
	void setCangraduation(bool can_graduation);
	//�� �̼������� ���ϴ� �Լ�
	void addTotalCredit(int credit);
};

