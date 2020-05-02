#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>
#include "Subject.h"
#include <string.h>
using namespace std;
class Yoram
{
private:
	//�й� ex) 18, 19, 20
	string student_id;
	//�а� ex) ��ǻ�Ͱ��а�, ����Ʈ�����а�, ��ǻ�Ͱ��к�
	string department;
	//��� ������ ���� �� ��
	string next;
	//��� ���Ͽ��� ���� ������ ������ ����
	Subject subject;
public:
	Yoram();
	Yoram(string student_id, string department);
	//��� ���� �� �پ� �д� �Լ�
	vector<Subject> read(string next);
	//���� ������ �����ڿ� ���� split�ϴ� �Լ�
	vector<string> split(const string& next, char delimiter);
	//����� ��ȯ
	string getName(string next);
	int getSubjectScore(int a);
	//bool getIsTakeClass();

	~Yoram();
};

