#pragma once
#include<string>
#include<fstream>
#include"User.h"
#include"Yoram.h"

using namespace std;

class GS_Manager
{
private:
	//학과 보관 배열
	string departments[3];
	//쓰기모드파일
	ofstream fout;
	//읽기모드파일
	ifstream fin;
	//요람파일
	ifstream fin_yoram;
	//유저 정보
	User user;
	//요람 정보
	Yoram yoram;
	//사용자 입력값 임시 저장 변수
	vector<string> input_value;
public:
	GS_Manager();
	~GS_Manager();
	//메인 함수
	bool playMain();
	//학번 오류 총괄?
	bool checkId(string school_id);
	//학번 오류 검사 함수
	bool compareSchoolId(string school_id);
	//문자열에 숫자가 아닌 값이 있는지 없는지 확인하는 함수
	bool nonInt(string str);
	//문자열(학번)의 길이를 검증하는 함수
	bool compareLength(string &school_id);
	//문자열의 길이를 검증하는 함수
	bool compareLength(string str, int length);
	//숫자 입력시 선행되는 0제거 함수
	string deleteZero(string str);
	//요람파일 여는 함수. 중복 방지 기능 탑재
	bool openYoramFile();
	//요람파일 읽는 함수
	void readYoramFile();
	//학번 입력 함수
	void inputSchoolId();
	//학과 입력 함수
	void inputDepartment();
	//유저파일 쓰기
	void inputUserFile();
	//유저파일 읽기
	void readUserFile();
	//학점 입력하는 함수
	void inputSubjectScore();
	//단계별 적용 함수
	void applyStep();
	//선택적 적용 함수
	void applySelect();
	//최종 결과 출력 함수
	void printResults();
};

