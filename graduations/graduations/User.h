/*
	4/27�� �ۼ���: 201911144 ���ǿ�
	���� ������ �����ϴ� Ŭ���� ����
	�����ϴ� �����δ� �� 4������ �ִ�.
	1. ������� �й�
	2. ������� �а�
	3. �� �̼�����
	4. �������ɿ���
	*/
#pragma once
#include <iostream>
#include <string>
using namespace std;
class User
{
private:
	//�й��޴� string Ÿ�� ����
	string classof;
	//�а� �޴� string Ÿ�� ����
	string department;
	//�� �̼� ������ �޴� intŸ�� ����
	unsigned int credit;
	//�������ɿ��θ� true false�� �޴� boolŸ�� ����
	bool can_graduation;
public:
	//�й��� �а� �˻������� ���°�� ���� ������ �ϹǷ�, �� �̼� �������� 0��, �������� ���ο��� false�� �־��ִ� �����ڸ� ������ݴϴ�.
	User(string classof, string department);
	//�й��� �а��� �Է� �޾��� �� �۵��ϴ� ������
	User(string classof, string department, int credit, bool can_graduation);
	//default�Ҹ���.
	~User();
	//�й��� Get �Լ�
	string getClassof() { return classof; }
	//�а��� Get�ϴ� �Լ�.
	string getDepartment() { return department; }
	//�� �̼� ������ Get�ϴ� �Լ�.
	int getCredit() { return credit; }
	//�������ɿ��θ� Get�ϴ� �Լ�.
	bool getCangraduation() { return can_graduation; }
	//�й��� set�ϴ� �Լ�.
	void setClassof(string classof) { this->classof = classof; }
	//�а��� set�ϴ� �Լ�
	void setDepartment(string department) { this->department = department; }
	//�� �̼������� set�ϴ� �Լ�.
	void setCredit(int credit) { this->credit = credit; }
	//�������ɿ��θ� set�ϴ� �Լ�.
	void setCangraduation(bool can_graduation) { this->can_graduation = can_graduation; }
};

