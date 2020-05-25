#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>
#include "Subject.h"
using namespace std;
class Yoram
{
private:
	//�������� ����ִ� ����
	vector<vector<Subject>> subjects;

	//���ʱ���
	vector<Subject> basic_liberal;
	//��ȭ����
	vector<Subject> improve_liberal;
	//��������
	vector<Subject> designation_liberal;
	//��������
	Subject select_major;
	//�Ϲݼ���
	Subject select_liberal;
	//�����ʼ�
	vector<Subject> compulsory_major;
	//�н�����
	vector<Subject> pass_subject;
	//�ʼ�����
	vector<Subject> compulsory_subject;
	//�� �̼� ����
	int total_credit;
public:
	Yoram();
	~Yoram();
	//�� ���� ���� �Լ�
	vector<Subject> getSubjects(int index);
	void pushSubject(Subject subject, int index);

	vector<Subject> getBasicLiberal();
	vector<Subject> getImproveLiberal();
	vector<Subject> getDesignationLiberal();
	Subject getSelectMajor();
	Subject getSelectLiberal();
	vector<Subject> getCompulsoryMajor();
	vector<Subject> getPassSubject();
	vector<Subject> getCompulsorySubject();
	//�� ���� �� �߰�
	void pushBasicLiberal(string name, int subject_score);
	void pushImproveLiberal(string name, int subject_score);
	void pushDesignationLiberal(string name, int subject_score);
	void setSelectMajor(string name, int subject_score);
	void setSelectLiberal(string name, int subject_score);
	void pushCompulsoryMajor(string name, int subject_score);
	void pushPassSubject(string name, int subject_score);
	void pushCompulsorySubject(string name, int subject_score);

	int getTotalCredit();
	void setTotalCredit(int credit);
};