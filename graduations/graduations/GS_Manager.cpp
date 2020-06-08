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
		else if (user.getDepartment() == "소프트웨어학과")
			input_value.push_back("1");
		else if (user.getDepartment() == "컴퓨터공학부")
			input_value.push_back("2");
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
		int credit, semester;
		string::size_type semester_delimiter = str_data.find_first_of("-");
		string::size_type credit_delimiter = str_data.find_first_of("|");
		if (semester_delimiter != string::npos) {
			semester = stoi(str_data.substr(semester_delimiter + 1));
			str_data = str_data.substr(0, semester_delimiter);
		}
		if (credit_delimiter == string::npos) {
			credit_delimiter = str_data.find_first_of(":");
			name = str_data.substr(0, credit_delimiter);
			credit = stoi(str_data.substr(credit_delimiter + 1));
		}
		else {
			string str_token1, str_token2;
			str_token1 = str_data.substr(0, credit_delimiter);
			str_token2 = str_data.substr(credit_delimiter + 1);
			credit_delimiter = str_token1.find_first_of(":");
			name = str_token1.substr(0, credit_delimiter) + " 또는 ";
			credit_delimiter = str_token2.find_first_of(":");
			name += str_token2.substr(0, credit_delimiter);
			credit = stoi(str_token2.substr(credit_delimiter + 1));
		}
		if (semester_delimiter == string::npos) {
			yoram.pushSubject(Subject(name, credit), count);
		}
		else {
			yoram.pushSubject(Subject(name, credit, semester), count);
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

	int count = 1;
	int major_score = -1;
	bool skip = false;

	for (int i = 0; i < 8; i++) {
		subjects = yoram.getSubjects(i);
		if (!subjects.empty()) {
			size = subjects.size();
			//반복출력되면 안되는 경우만 빼놓음
			if (i == 2)
				cout << "지정교양" << endl;
			else if (i == 6)
				cout << "과목 패스 여부" << endl;
			else if (i == 7)
				cout << "필수과목이수" << endl;
			for (int j = 0; j < size; j++) {
				if (i == 0 || i == 1) {
					while (true) {
						if (i == 0)
							cout << "기초";
						else
							cout << "심화";
						cout << "교양 " << subjects[j].getName() << " 영역 학점 : ";
						getline(cin, subject_score);
						if (subject_score == "b" || subject_score == "B") {
							if (j == 0) {
								if (i == 0) {
									cout << "이전 질문이 존재하지 않습니다." << endl;
									j = -1;
									break;
								}
								i--;
								subjects = yoram.getSubjects(i);
								size = subjects.size();
								j = size;
							}
							j -= 2;
							count--;
							break;
						}
						subject_score = deleteZero(subject_score);
						if (nonInt(subject_score)*compareLength(subject_score, 3)) {
							break;
						}
					}
				}
				else if (i == 2 || i == 7) {
					while (true) {
						cout << subjects[j].getName() << "을(를) 이수하셨습니까? (Y/N) : ";
						getline(cin, subject_score);
						if (subject_score == "b" || subject_score == "B") {
							if (j == 0) {
								i--;
								subjects = yoram.getSubjects(i);
								size = subjects.size();
								j = size;
							}
							j -= 2;
							count--;
							break;
						}
						if (subject_score == "Y" || subject_score == "N") {
							break;
						}
						else {
							cout << "유효하지 않은 입력입니다." << endl;
						}
					}
				}
				else if (i == 3 || i == 4) {
					while (true) {
						cout << subjects[j].getName() << " 학점 : ";
						getline(cin, subject_score);
						if (subject_score == "b" || subject_score == "B") {
							if (j == 0) {
								i--;
								subjects = yoram.getSubjects(i);
								size = subjects.size();
								j = size;
							}
							j -= 2;
							count--;
							break;
						}
						subject_score = deleteZero(subject_score);
						if (nonInt(subject_score)*compareLength(subject_score, 3)) {
							break;
						}
					}
				}
				else if (i == 5) {
					if (j == 0 && !skip) {
						while (true) {
							cout << "전공필수 학점 : ";
							getline(cin, subject_score);
							if (subject_score == "b" || subject_score == "B") {
								i--;
								subjects = yoram.getSubjects(i);
								size = 1;
								j = -1;
								count--;
								break;
							}
							subject_score = deleteZero(subject_score);
							if (nonInt(subject_score)*compareLength(subject_score, 3)) {
								major_score = stoi(subject_score);
								break;
							}
						}
					}
					if (major_score == 0) {
						if (count >= input_value.size()) {
							input_value.push_back("N");
						}
						else {
							input_value.insert(input_value.begin() + count, "N");
							input_value.erase(input_value.begin() + count + 1);
						}
						count++;
						continue;
					}
					if (subject_score != "b" && subject_score != "B") {
						while (true) {
							cout << subjects[j].getName() << "을(를) 이수하셨습니까? (Y/N) : ";
							getline(cin, subject_score);
							if (subject_score == "b" || subject_score == "B") {
								if (j == 0) {
									j = -1;
									skip = false;
									break;
								}
								j -= 2;
								count--;
								skip = true;
								break;
							}
							if (subject_score == "Y" || subject_score == "N") {
								break;
							}
							else {
								cout << "유효하지 않은 입력입니다." << endl;
							}
						}
					}
				}
				else if (i == 6) {
					while (true) {
						cout << subjects[j].getName() << "을(를) 패스(수강대체)하셨습니까? (Y/N) : ";
						getline(cin, subject_score);
						if (subject_score == "b" || subject_score == "B") {
							if (j == 0) {
								i--;
								subjects = yoram.getSubjects(i);
								if (subjects.empty()) {
									i--;
									subjects = yoram.getSubjects(i);
								}
								size = subjects.size();
								if(major_score==0){
									j = -1;
									count -= subjects.size();
									skip = false;
									break;
								}
								j = size;
							}
							j -= 2;
							count--;
							break;
						}
						if (subject_score == "Y" || subject_score == "N") {
							break;
						}
						else {
							cout << "유효하지 않은 입력입니다." << endl;
						}
					}
				}
				if (subject_score != "b" && subject_score != "B") {
					if (count >= input_value.size()) {
						input_value.push_back(subject_score);
					}
					else {
						input_value.insert(input_value.begin() + count, subject_score);
						input_value.erase(input_value.begin() + count + 1);
					}
					count++;
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
	//출력용 변수
	int user_credit = 0;
	int yoram_credit = 0;
	//기초교양 출력
	subjects = yoram.getSubjects(0);
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
	subjects = yoram.getSubjects(1);
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
	subjects = yoram.getSubjects(2);
	user_credit = 0;
	yoram_credit = 0;
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		getline(fin, input_score);
		if (input_score == "Y") {
			user_credit += subjects[i].getSubjectScore();
		}
		else {
			designation_result += "-" + subjects[i].getName() + " / ";
			if (subjects[i].getSemester() == 1 || subjects[i].getSemester() == 2) {
				designation_result += to_string(subjects[i].getSemester()) + "학기 개설과목\n";
			}
			else if (subjects[i].getSemester() == 3) {
				designation_result += "1학기 2학기 모두 개설\n";
			}
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
	subjects = yoram.getSubjects(3);
	string major_result;
	getline(fin, input_score);
	yoram_credit = subjects[0].getSubjectScore();
	major_result = "전공선택과목 : " + input_score + "학점/" + to_string(yoram_credit) + "학점";
	subject_score = stoi(input_score);
	user.addTotalCredit(subject_score);
	if (user.getCangraduation()) {
		if (subject_score < yoram_credit) {
			user.setCangraduation(false);
		}
	}

	//일반선택 출력
	subjects = yoram.getSubjects(4);
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
	subjects = yoram.getSubjects(5);
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
				cout << "-" << subjects[i].getName() << " / ";
				if (subjects[i].getSemester() == 1 || subjects[i].getSemester() == 2) {
					cout << to_string(subjects[i].getSemester()) + "학기 개설과목" << endl;
				}
				else if (subjects[i].getSemester() == 3) {
					cout << "1학기 2학기 모두 개설" << endl;
				}
			}
			yoram_credit += subjects[i].getSubjectScore();
		}
		major_result += ", 전공필수과목 : " + to_string(user_credit) + "학점/" + to_string(yoram_credit) + "학점";
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
	subjects = yoram.getSubjects(6);
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
	subjects = yoram.getSubjects(7);
	if (!subjects.empty()) {
		cout << endl << "필수과목 수강여부";
		user_credit = 0;
		size = subjects.size();
		for (int i = 0; i < size; i++) {
			getline(fin, input_score);
			cout << endl << subjects[i].getName() << " : " << input_score;
			if (input_score == "Y") {
				user_credit += subjects[i].getSubjectScore();
			}
			else {
				if (subjects[i].getSemester() == 1 || subjects[i].getSemester() == 2) {
					cout << " / " << to_string(subjects[i].getSemester()) + "학기 개설과목" << endl;
				}
				else if (subjects[i].getSemester() == 3) {
					cout << " / 1학기 2학기 모두 개설" << endl;
				}
			}
			if (user.getCangraduation()) {
				if (input_score=="N") {
					user.setCangraduation(false);
				}
			}
		}
		user.addTotalCredit(user_credit);
	}

	//총이수학점 출력
	cout << "\n===============================" << endl;
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
