#pragma once
#include<string>
#include<fstream>

using namespace std;

class GS_Manager
{
private:
	//�й� �Է� ����
	string school_id;
	//�а� �Է� ����
	string department;
	//�а� ���� �迭
	string departments[3];
	//����������
	ofstream fout;
	//�б�������
	ifstream fin;
	//�������
	ifstream fin_requirement;

public:
	GS_Manager();
	~GS_Manager();
	//���� �Լ�
	bool playMain();
	//�й� ���� �Ѱ�?
	bool checkId();
	//�й� ���� �˻� �Լ�
	bool compareSchoolId();
	//���ڿ��� ���ڰ� �ƴ� ���� �ִ��� ������ Ȯ���ϴ� �Լ�
	bool nonInt(string str);
	//���ڿ�(�й�)�� ���̸� �����ϴ� �Լ�
	bool compareLength(int length);
	//���ڿ��� ���̸� �����ϴ� �Լ�
	bool compareLength(string str, int length);
	//������� ���� �Լ�. �ߺ� ���� ��� ž��
	bool openRequirementFile();
	//�й� �Է� �Լ�
	void inputSchoolId();
	//�а� �Է� �Լ�
	void inputDepartment();
	//���� �Է��ϴ� �Լ�
	void inputSubjectScore();
	//���� ��� ��� �Լ�
	void compareResults();
};

