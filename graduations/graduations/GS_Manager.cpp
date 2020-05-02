#include "GS_Manager.h"
#include<iostream>
#include<sstream>


GS_Manager::GS_Manager()
{
	department = "";
	departments[0] = "컴퓨터공학과";
	departments[1] = "소프트웨어학과";
	departments[2] = "컴퓨터공학부";
}

GS_Manager::~GS_Manager()
{
}

bool GS_Manager::playMain()
{
	inputSchoolId();
	
	fin.open("./student_info/" + school_id + ".txt");
	if (!(fin.is_open())) {
		fout.open("./Student_Info/" + school_id + ".txt");
		cout << "생성완료" << endl;
		inputDepartment();
		if (!openRequirementFile()) {
			return false;
		}
		inputSubjectScore();
	}
	
	if (!openRequirementFile()) {
		return false;
	}

	compareResults();

	return true;
}

bool GS_Manager::checkId()
{
	bool result = nonInt(school_id)*compareLength(9)*compareSchoolId();
	return result;
}

bool GS_Manager::compareSchoolId()
{
	string year = school_id.substr(0, 4);
	char college_num = school_id.at(4);
	string order_num = school_id.substr(5, 4);
	bool is_error = true;
	if (!(college_num >= '1'&&college_num <= '6')) {
		cout << "프로그램 사용 대상이 잘못됐습니다. 학부생의 구분은 1~6까지 입니다." << endl;
		is_error = false;
	}
	if (!(year == "2018" || year == "2019" || year == "2020")) {
		cout << "입학년도가 잘못됐습니다." << endl;
		is_error = false;
	}
	if (order_num == "0000") {
		cout << "올바르지 않은 학번입니다. 뒤쪽 4자리는 0001부터 유효합니다." << endl;
		is_error = false;
	}
	return is_error;
}

bool GS_Manager::nonInt(string str)
{
	string result = "";
	for (int i = 0; i < str.length(); i++) {
		char check_ch = str.at(i);
		if (!(check_ch >= '0'&&check_ch <= '9')) {
			if (result != "")
				result += ", ";
			result += check_ch;
		}
	}
	if (result == "")
		return true;
	else {
		cout << "입력 인자에 숫자가 아닌게 있습니다.( " + result + " )" << endl;
		return false;
	}
}

bool GS_Manager::compareLength(int length)
{
	if (school_id.length() == length)
		return true;
	else if (school_id.length() > length) {
		cout << "입력한 학번이 너무 깁니다." << endl;
		return false;
	}
	else {
		cout << "입력한 학번이 너무 짧습니다." << endl;
		return false;
	}
}

bool GS_Manager::compareLength(string str, int length)
{
	if (str.length() > length) {
		cout << "입력한 값이 너무 깁니다." << endl;
		return false;
	}
	else {
		return true;
	}
}

bool GS_Manager::openRequirementFile()
{
	if (fin_requirement.is_open()) {
		//위치 지정자를 파일 맨 앞으로 이동
		fin_requirement.seekg(0, ios::beg);
		return true;
	}
	else if (department=="") {
		string tmp_department;
		getline(fin, tmp_department);
		istringstream read_department(tmp_department);
		int department_num;
		read_department >> department_num;
		department = departments[department_num];
	}
	string id_year = school_id.substr(2, 2);
	fin_requirement.open("./Booklet/" + id_year + department + ".txt");
	if (fin_requirement.is_open()) {
		cout << "confirm" << endl;
		return true;
	}
	else {
		cout << "요람파일이 존재하지 않습니다." << endl;
		return false;
	}
}

void GS_Manager::inputSchoolId()
{
	while (true) {
		cout << "학번을 입력해 주세요 : ";
		cin >> school_id;
		if (checkId()) {
			break;
		}
	}
}

void GS_Manager::inputDepartment()
{
	while (true) {
		cout << "학과를 입력하세요(컴퓨터공학과/소프트웨어학과/컴퓨터공학부) : ";
		cin >> department;
		if (department == "컴퓨터공학과") {
			fout << "0";
			break;
		}
		else if (department == "소프트웨어학과") {
			fout << "1";
			break;
		}
		else if (department == "컴퓨터공학부") {
			fout << "2";
			break;
		}
		else {
			cout << "유호하지 않은 입력입니다." << endl;
		}
	}
}

void GS_Manager::inputSubjectScore()
{
	//여기에 내용 입력
}

void GS_Manager::compareResults()
{
	//여기에 내용 입력
}
