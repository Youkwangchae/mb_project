#pragma once
#include<string>
#include<fstream>
#include"User.h"
#include"Yoram.h"

using namespace std;

class GS_Manager
{
private:
	//�а� ���� �迭
	string departments[3];
	//����������
	ofstream fout;
	//�б�������
	ifstream fin;
	//�������
	ifstream fin_yoram;
	//���� ����
	User user;
	//��� ����
	Yoram yoram;
	//����� �Է°� �ӽ� ���� ����
	vector<string> input_value;
public:
	GS_Manager();
	~GS_Manager();
	//���� �Լ�
	bool playMain();
	//�й� ���� �Ѱ�?
	bool checkId(string school_id);
	//�й� ���� �˻� �Լ�
	bool compareSchoolId(string school_id);
	//���ڿ��� ���ڰ� �ƴ� ���� �ִ��� ������ Ȯ���ϴ� �Լ�
	bool nonInt(string str);
	//���ڿ�(�й�)�� ���̸� �����ϴ� �Լ�
	bool compareLength(string &school_id);
	//���ڿ��� ���̸� �����ϴ� �Լ�
	bool compareLength(string str, int length);
	//���� �Է½� ����Ǵ� 0���� �Լ�
	string deleteZero(string str);
	//������� ���� �Լ�. �ߺ� ���� ��� ž��
	bool openYoramFile();
	//������� �д� �Լ�
	void readYoramFile();
	//�й� �Է� �Լ�
	void inputSchoolId();
	//�а� �Է� �Լ�
	void inputDepartment();
	//�������� ����
	void inputUserFile();
	//�������� �б�
	void readUserFile();
	//���� �Է��ϴ� �Լ�
	void inputSubjectScore();
	//�ܰ躰 ���� �Լ�
	void applyStep();
	//������ ���� �Լ�
	void applySelect();
	//���� ��� ��� �Լ�
	void printResults();
};

