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
	//모든과목이 들어있는 벡터
	vector<vector<Subject>> subjects;

	//기초교양
	vector<Subject> basic_liberal;
	//심화교양
	vector<Subject> improve_liberal;
	//지정교양
	vector<Subject> designation_liberal;
	//전공선택
	Subject select_major;
	//일반선택
	Subject select_liberal;
	//전공필수
	vector<Subject> compulsory_major;
	//패스과목
	vector<Subject> pass_subject;
	//필수과목
	vector<Subject> compulsory_subject;
	//총 이수 학점
	int total_credit;
public:
	Yoram();
	~Yoram();
	//각 과목 리턴 함수
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
	//각 과목 값 추가
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