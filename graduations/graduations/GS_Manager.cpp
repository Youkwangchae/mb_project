#include "GS_Manager.h"
#include<iostream>
#include<sstream>


GS_Manager::GS_Manager()
	:user("201910001", "noDepartment")
{
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
	fin.open("./Student_info/" + user.getSchoolId() + ".txt");
	if (!(fin.is_open())) {
		inputDepartment();
		if (!openYoramFile()) {
			return false;
		}
		if (user.getDepartment() == "컴퓨터공학과")
			input_value.push_back("0");
			//fout << "0\n";
		else if (user.getDepartment() == "소프트웨어학과")
			input_value.push_back("1");
			//fout << "1\n";
		else if (user.getDepartment() == "컴퓨터공학부")
			input_value.push_back("2");
			//fout << "2\n";
		inputSubjectScore();

		fout.open("./Student_Info/" + user.getSchoolId() + ".txt");
		fin.open("./Student_info/" + user.getSchoolId() + ".txt");
		if (!(fin.is_open())) {
			cout << "학번파일 저장경로가 없습니다." << endl;
			return false;
		}
		inputUserFile();
		fout.close();
	}

	if (!(fin.is_open())) {
		fin.open("./Student_info/" + user.getSchoolId() + ".txt");
	}

	if (!openYoramFile()) {
		return false;
	}

	printResults();

	return true;
}

bool GS_Manager::checkId(string school_id)
{
	bool result = nonInt(school_id)*compareLength(school_id)*compareSchoolId(school_id);
	return result;
}

bool GS_Manager::compareSchoolId(string school_id)
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
	//warning C4018 방지용 변수
	int size = str.length();
	//한글 깨짐 방지 변수
	int count = 1;
	for (int i = 0; i < size; i++) {
		char check_ch = str.at(i);
		if (!(check_ch >= '0'&&check_ch <= '9')) {
			if ((count == 1) && ((check_ch >= '!'&&check_ch <= '/') || (check_ch >= ':'&&check_ch <= '~')) || check_ch == ' ') {
				if (result != "")
					result += ", ";
				result += check_ch;
			}
			else {
				if (count == 1) {
					if (result != "")
						result += ", ";
					count++;
				}
				else
					count--;
				result += check_ch;
			}
		}
	}
	if (result == "")
		return true;
	else {
		cout << "입력 인자에 숫자가 아닌게 있습니다.( " + result + " )" << endl;
		return false;
	}
}

bool GS_Manager::compareLength(string &school_id)
{
	int size = school_id.length();
	if (size == 9)
		return true;
	else if (size > 9) {
		cout << "입력한 학번이 너무 깁니다." << endl;
		return false;
	}
	else {
		for (int i = 0; i < 9 - size; i++) {
			school_id.append(" ");
		}
		cout << "입력한 학번이 너무 짧습니다." << endl;
		return false;
	}
}

bool GS_Manager::compareLength(string str, int length)
{
	//warning C4018 방지용 변수
	int size = str.length();
	if (size > length) {
		cout << "입력한 값이 너무 깁니다." << endl;
		return false;
	}
	else if (size == 0) {
		cout << "입력한 값이 너무 짧습니다." << endl;
		return false;
	}
	else {
		return true;
	}
}

string GS_Manager::deleteZero(string str)
{
	string result;
	int size = str.length();
	for (int i = 0; i < size; i++) {
		char check_ch = str.at(i);
		if (check_ch != '0' || i == size - 1) {
			result = str.substr(i);
			break;
		}
	}
	return result;
}

bool GS_Manager::openYoramFile()
{
	if (fin_yoram.is_open()) {
		string tmp_department;
		getline(fin, tmp_department);
		return true;
	}
	else if (user.getDepartment()=="noDepartment") {
		string tmp_department;
		getline(fin, tmp_department);
		istringstream read_department(tmp_department);
		int department_num;
		read_department >> department_num;
		user.setDepartment(departments[department_num]);
	}
	string id_year = user.getSchoolId().substr(2, 2);
	if (id_year == "19"&&user.getDepartment() == "컴퓨터공학부") {
		id_year = "20";
	}
	fin_yoram.open("./Booklet/" + id_year + user.getDepartment() + ".txt");
	if (fin_yoram.is_open()) {
		readYoramFile();
		return true;
	}
	else {
		cout << "요람파일이 존재하지 않습니다." << endl;
		return false;
	}
}

void GS_Manager::readYoramFile()
{
	string str_data;
	int count = 0;
	while (fin_yoram) {
		getline(fin_yoram, str_data);
		if (str_data == "@") {
			count++;
			continue;
		}
		if (str_data == "★") {
			break;
		}
		string name;
		int credit;
		string::size_type delimiter = str_data.find_first_of("|");
		if (delimiter == string::npos) {
			delimiter = str_data.find_first_of(":");
			name = str_data.substr(0, delimiter);
			credit = stoi(str_data.substr(delimiter + 1));
		}
		else {
			string str_token1, str_token2;
			str_token1 = str_data.substr(0, delimiter);
			str_token2 = str_data.substr(delimiter + 1);
			delimiter = str_token1.find_first_of(":");
			name = str_token1.substr(0, delimiter) + " 또는 ";
			delimiter = str_token2.find_first_of(":");
			name += str_token2.substr(0, delimiter);
			credit = stoi(str_token2.substr(delimiter + 1));
		}
		
		switch (count)
		{
		case 0:
			yoram.pushBasicLiberal(name, credit);
			break;
		case 1:
			yoram.pushImproveLiberal(name, credit);
			break;
		case 2:
			yoram.pushDesignationLiberal(name, credit);
			break;
		case 3:
			yoram.setSelectMajor(name, credit);
			break;
		case 4:
			yoram.setSelectLiberal(name, credit);
			break;
		case 5:
			yoram.pushCompulsoryMajor(name, credit);
			break;
		case 6:
			yoram.pushPassSubject(name, credit);
			break;
		case 7:
			yoram.pushCompulsorySubject(name, credit);
			break;
		default:
			break;
		}
	}
	getline(fin_yoram, str_data);
	int total_credit = stoi(str_data);
	yoram.setTotalCredit(total_credit);
}

void GS_Manager::inputSchoolId()
{
	string school_id;
	while (true) {
		cout << "학번을 입력해 주세요 : ";
		getline(cin, school_id);
		if (checkId(school_id)) {
			break;
		}
	}
	user.setSchoolId(school_id);
}

void GS_Manager::inputDepartment()
{
	string department;
	while (true) {
		cout << "학과를 입력하세요(컴퓨터공학과/소프트웨어학과/컴퓨터공학부) : ";
		getline(cin, department);
		if (department == "컴퓨터공학과" || department == "소프트웨어학과" || department == "컴퓨터공학부") {
			user.setDepartment(department);
			break;
		}
		else {
			cout << "유효하지 않은 입력입니다." << endl;
		}
	}
	user.setDepartment(department);
}

void GS_Manager::inputUserFile()
{
	int size = input_value.size();
	for (int i = 0; i < size; i++) {
		fout << input_value[i] + "\n";
	}
}

void GS_Manager::inputSubjectScore()
{
	//warning C4018 방지용 변수
	int size;
	//사용자 입력값 변수
	string subject_score;
	//과목 저장 변수
	vector<Subject> subjects;
	Subject subject;
	//기초교양 질문
	subjects = yoram.getBasicLiberal();
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		while (true) {
			cout << "기초교양 " << subjects[i].getName() << " 영역 학점 : ";
			getline(cin, subject_score);
			subject_score = deleteZero(subject_score);
			if (nonInt(subject_score)*compareLength(subject_score, 3)) {
				input_value.push_back(subject_score);
				//fout << subject_score + "\n";
				break;
			}
		}
	}
	//심화교양 질문
	subjects = yoram.getImproveLiberal();
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		while (true) {
			cout << "심화교양 " << subjects[i].getName() << " 영역 학점 : ";
			getline(cin, subject_score);
			subject_score = deleteZero(subject_score);
			if (nonInt(subject_score)*compareLength(subject_score, 3)) {
				input_value.push_back(subject_score);
				//fout << subject_score + "\n";
				break;
			}
		}
	}
	//지정교양 질문
	subjects = yoram.getDesignationLiberal();
	cout << "지정교양" << endl;
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		while (true) {
			cout << subjects[i].getName() << "을(를) 이수하셨습니까? (Y/N) : ";
			getline(cin, subject_score);
			if (subject_score == "Y"||subject_score == "N") {
				input_value.push_back(subject_score);
				//fout << subject_score + "\n";
				break;
			}
			else {
				cout << "유효하지 않은 입력입니다." << endl;
			}
		}
	}
	//전공선택, 일반선택 질문
	for (int i = 0; i < 2; i++) {
		if (i == 0)
			subject = yoram.getSelectMajor();
		else
			subject = yoram.getSelectLiberal();
		while (true) {
			cout << subject.getName() << " 학점 : ";
			getline(cin, subject_score);
			subject_score = deleteZero(subject_score);
			if (nonInt(subject_score)*compareLength(subject_score, 3)) {
				input_value.push_back(subject_score);
				//fout << subject_score + "\n";
				break;
			}
		}
	}
	//전공필수 질문
	subjects = yoram.getCompulsoryMajor();
	if (!subjects.empty()) {
		while (true) {
			cout << "전공필수 학점 : ";
			getline(cin, subject_score);
			subject_score = deleteZero(subject_score);
			size = subjects.size();
			if (nonInt(subject_score)*compareLength(subject_score, 3)) {
				break;
			}
		}
		for (int i = 0; i < size; i++) {
			if (subject_score == "0")
				fout << "N\n";
			else {
				while (true) {
					cout << subjects[i].getName() << "을(를) 이수하셨습니까? (Y/N) : ";
					getline(cin, subject_score);
					if (subject_score == "Y" || subject_score == "N") {
						input_value.push_back(subject_score);
						//fout << subject_score + "\n";
						break;
					}
					else {
						cout << "유효하지 않은 입력입니다." << endl;
					}
				}
			}
		}
	}
	//패스과목 질문
	subjects = yoram.getPassSubject();
	cout << "과목 패스 여부" << endl;
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		while (true) {
			cout << subjects[i].getName() << "을(를) 패스(수강대체)하셨습니까? (Y/N) : ";
			getline(cin, subject_score);
			if (subject_score == "Y" || subject_score == "N") {
				input_value.push_back(subject_score);
				//fout << subject_score + "\n";
				break;
			}
			else {
				cout << "유효하지 않은 입력입니다." << endl;
			}
		}
	}
	//필수과목 질문
	subjects = yoram.getCompulsorySubject();
	cout << "필수과목이수" << endl;
	if (!subjects.empty()) {
		size = subjects.size();
		for (int i = 0; i < size; i++) {
			while (true) {
				cout << subjects[i].getName() << "을(를) 이수하셨습니까? (Y/N) : ";
				getline(cin, subject_score);
				if (subject_score == "Y" || subject_score == "N") {
					input_value.push_back(subject_score);
					//fout << subject_score + "\n";
					break;
				}
				else {
					cout << "유효하지 않은 입력입니다." << endl;
				}
			}
		}
	}
}

void GS_Manager::printResults()
{
	//warning C4018 방지용 변수
	int size;
	cout << endl << "===============================" << endl;
	cout << "학번 : " << user.getSchoolId() << endl;
	cout << "소속 : " << user.getDepartment() << endl;
	cout << "===============================" << endl;
	//사용자 값 변수
	string input_score;
	int subject_score;
	//과목 저장 변수
	vector<Subject> subjects;
	Subject subject;
	//출력용 변수
	int user_credit = 0;
	int yoram_credit = 0;
	//기초교양 출력
	subjects = yoram.getBasicLiberal();
	cout << "기초교양" << endl;
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		getline(fin, input_score);
		cout << subjects[i].getName() << " : " << input_score << "학점/" << subjects[i].getSubjectScore() << "학점" << endl;
		subject_score = stoi(input_score);
		user_credit += subject_score;
		yoram_credit += subjects[i].getSubjectScore();
	}
	cout << endl << "총 기초교양학점 : " << user_credit << "학점/" << yoram_credit << "학점" << endl << endl;
	user.addTotalCredit(user_credit);
	if (user.getCangraduation()) {
		if (user_credit < yoram_credit) {
			user.setCangraduation(false);
		}
	}

	//심화교양 출력
	subjects = yoram.getImproveLiberal();
	cout << "심화교양" << endl;
	user_credit = 0;
	yoram_credit = 0;
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		getline(fin, input_score);
		cout << subjects[i].getName() << " : " << input_score << "학점/" << subjects[i].getSubjectScore() << "학점" << endl;
		subject_score = stoi(input_score);
		user_credit += subject_score;
		yoram_credit += subjects[i].getSubjectScore();
	}
	cout << endl << "총 심화교양학점 : " << user_credit << "학점/" << yoram_credit << "학점" << endl << endl;
	user.addTotalCredit(user_credit);
	if (user.getCangraduation()) {
		if (user_credit < yoram_credit) {
			user.setCangraduation(false);
		}
	}

	//지정교양 출력문 저장
	string designation_result = "";
	subjects = yoram.getDesignationLiberal();
	user_credit = 0;
	yoram_credit = 0;
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		getline(fin, input_score);
		if (input_score == "Y") {
			user_credit += subjects[i].getSubjectScore();
		}
		else {
			designation_result += "-" + subjects[i].getName() + "\n";
		}
		yoram_credit += subjects[i].getSubjectScore();
	}
	designation_result += "\n지정교양 : " + to_string(user_credit) + "학점/" + to_string(yoram_credit) + "학점\n";
	user.addTotalCredit(user_credit);
	if (user.getCangraduation()) {
		if (user_credit < yoram_credit) {
			user.setCangraduation(false);
		}
	}

	//전공선택 출력문 저장
	subject = yoram.getSelectMajor();
	string major_result;
	getline(fin, input_score);
	yoram_credit = subject.getSubjectScore();
	major_result = "전공선택과목 : " + input_score + "학점/" + to_string(yoram_credit);
	subject_score = stoi(input_score);
	user.addTotalCredit(subject_score);
	if (user.getCangraduation()) {
		if (subject_score < yoram_credit) {
			user.setCangraduation(false);
		}
	}

	//일반선택 출력
	subject = yoram.getSelectLiberal();
	getline(fin, input_score);
	cout << "총 일선학점 : " << input_score << "학점" << endl;
	subject_score = stoi(input_score);
	user.addTotalCredit(subject_score);
	cout << "===============================" << endl;

	//지정교양 출력
	cout << "지정교양" << endl;
	cout << "미이수 과목 : " << endl;
	cout << designation_result << endl;
	
	//전공필수 출력
	subjects = yoram.getCompulsoryMajor();
	if (!subjects.empty()) {
		user_credit = 0;
		yoram_credit = 0;
		cout << "전공필수" << endl;
		cout << "미이수 과목 : " << endl;
		size = subjects.size();
		for (int i = 0; i < size; i++) {
			getline(fin, input_score);
			if (input_score == "Y") {
				user_credit += subjects[i].getSubjectScore();
			}
			else {
				cout << "-" << subjects[i].getName() << endl;
			}
			yoram_credit += subjects[i].getSubjectScore();
		}
		major_result += ", 전공필수과목 : " + to_string(user_credit) + "학점/" + to_string(yoram_credit);
		user.addTotalCredit(user_credit);
		if (user.getCangraduation()) {
			if (user_credit < yoram_credit) {
				user.setCangraduation(false);
			}
		}
	}
	cout << endl << major_result << endl << endl;
	cout << "===============================" << endl;

	//패스과목 출력
	subjects = yoram.getPassSubject();
	cout << "과목 패스여부" << endl;
	user_credit = 0;
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		getline(fin, input_score);
		if (input_score == "Y") {
			user_credit += subjects[i].getSubjectScore();
		}
		cout << subjects[i].getName() << " : " << input_score << endl;
	}
	user.addTotalCredit(user_credit);

	//필수과목 출력
	subjects = yoram.getCompulsorySubject();
	cout << endl << "필수과목 수강여부" << endl;
	if (!subjects.empty()) {
		user_credit = 0;
		size = subjects.size();
		for (int i = 0; i < size; i++) {
			getline(fin, input_score);
			if (input_score == "Y") {
				user_credit += subjects[i].getSubjectScore();
			}
			cout << subjects[i].getName() << " : " << input_score << endl;
			if (user.getCangraduation()) {
				if (input_score=="N") {
					user.setCangraduation(false);
				}
			}
		}
		user.addTotalCredit(user_credit);
	}

	//총이수학점 출력
	cout << "===============================" << endl;
	cout << "총 이수학점 : " << user.getTotalCredit() << "학점/" << yoram.getTotalCredit() << "학점" << endl;
	cout << "===============================" << endl;
	
	if (user.getCangraduation()) {
		if (user.getTotalCredit()<yoram.getTotalCredit()) {
			user.setCangraduation(false);
		}
	}
	//졸업가능여부 출력
	cout << "졸업 가능 여부 : ";
	if (user.getCangraduation()) {
		cout << "졸업 가능!" << endl;
	}
	else {
		cout << "졸업 불가능!" << endl;
	}

}
