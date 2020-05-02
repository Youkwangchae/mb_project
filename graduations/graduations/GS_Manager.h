#pragma once
#include<string>
#include<fstream>

using namespace std;

class GS_Manager
{
private:
	//학번 입력 변수
	string school_id;
	//학과 입력 변수
	string department;
	//학과 보관 배열
	string departments[3];
	//쓰기모드파일
	ofstream fout;
	//읽기모드파일
	ifstream fin;
	//요람파일
	ifstream fin_requirement;

public:
	GS_Manager();
	~GS_Manager();
	//메인 함수
	bool playMain();
	//학번 오류 총괄?
	bool checkId();
	//학번 오류 검사 함수
	bool compareSchoolId();
	//문자열에 숫자가 아닌 값이 있는지 없는지 확인하는 함수
	bool nonInt(string str);
	//문자열(학번)의 길이를 검증하는 함수
	bool compareLength(int length);
	//문자열의 길이를 검증하는 함수
	bool compareLength(string str, int length);
	//요람파일 여는 함수. 중복 방지 기능 탑재
	bool openRequirementFile();
	//학번 입력 함수
	void inputSchoolId();
	//학과 입력 함수
	void inputDepartment();
	//학점 입력하는 함수
	void inputSubjectScore();
	//최종 결과 출력 함수
	void compareResults();
};

