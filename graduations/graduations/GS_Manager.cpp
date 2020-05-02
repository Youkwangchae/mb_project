#include "GS_Manager.h"
#include<iostream>
#include<sstream>


GS_Manager::GS_Manager()
{
	department = "";
	departments[0] = "��ǻ�Ͱ��а�";
	departments[1] = "����Ʈ�����а�";
	departments[2] = "��ǻ�Ͱ��к�";
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
		cout << "�����Ϸ�" << endl;
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
		cout << "���α׷� ��� ����� �߸��ƽ��ϴ�. �кλ��� ������ 1~6���� �Դϴ�." << endl;
		is_error = false;
	}
	if (!(year == "2018" || year == "2019" || year == "2020")) {
		cout << "���г⵵�� �߸��ƽ��ϴ�." << endl;
		is_error = false;
	}
	if (order_num == "0000") {
		cout << "�ùٸ��� ���� �й��Դϴ�. ���� 4�ڸ��� 0001���� ��ȿ�մϴ�." << endl;
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
		cout << "�Է� ���ڿ� ���ڰ� �ƴѰ� �ֽ��ϴ�.( " + result + " )" << endl;
		return false;
	}
}

bool GS_Manager::compareLength(int length)
{
	if (school_id.length() == length)
		return true;
	else if (school_id.length() > length) {
		cout << "�Է��� �й��� �ʹ� ��ϴ�." << endl;
		return false;
	}
	else {
		cout << "�Է��� �й��� �ʹ� ª���ϴ�." << endl;
		return false;
	}
}

bool GS_Manager::compareLength(string str, int length)
{
	if (str.length() > length) {
		cout << "�Է��� ���� �ʹ� ��ϴ�." << endl;
		return false;
	}
	else {
		return true;
	}
}

bool GS_Manager::openRequirementFile()
{
	if (fin_requirement.is_open()) {
		//��ġ �����ڸ� ���� �� ������ �̵�
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
		cout << "��������� �������� �ʽ��ϴ�." << endl;
		return false;
	}
}

void GS_Manager::inputSchoolId()
{
	while (true) {
		cout << "�й��� �Է��� �ּ��� : ";
		cin >> school_id;
		if (checkId()) {
			break;
		}
	}
}

void GS_Manager::inputDepartment()
{
	while (true) {
		cout << "�а��� �Է��ϼ���(��ǻ�Ͱ��а�/����Ʈ�����а�/��ǻ�Ͱ��к�) : ";
		cin >> department;
		if (department == "��ǻ�Ͱ��а�") {
			fout << "0";
			break;
		}
		else if (department == "����Ʈ�����а�") {
			fout << "1";
			break;
		}
		else if (department == "��ǻ�Ͱ��к�") {
			fout << "2";
			break;
		}
		else {
			cout << "��ȣ���� ���� �Է��Դϴ�." << endl;
		}
	}
}

void GS_Manager::inputSubjectScore()
{
	//���⿡ ���� �Է�
}

void GS_Manager::compareResults()
{
	//���⿡ ���� �Է�
}
