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
	//학번 ex) 18, 19, 20
	string student_id;
	//학과 ex) 컴퓨터공학과, 소프트웨어학과, 컴퓨터공학부
	string department;
	//요람 파일의 다음 한 줄
	string next;
	//요람 파일에서 읽은 내용을 저장할 과목
	Subject subject;
public:
	Yoram();
	Yoram(string student_id, string department);
	//요람 파일 한 줄씩 읽는 함수
	vector<Subject> read(string next);
	//읽은 내용을 구분자에 따라 split하는 함수
	vector<string> split(const string& next, char delimiter);
	//과목명 반환
	string getName(string next);
	int getSubjectScore(int a);
	//bool getIsTakeClass();

	~Yoram();
};

