#include "GS_Manager.h"
#include<iostream>
#include<sstream>


GS_Manager::GS_Manager()
	:user("201910001", "noDepartment")
{
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
	fin.open("./Student_info/" + user.getSchoolId() + ".txt");
	if (!(fin.is_open())) {
		inputDepartment();
		if (!openYoramFile()) {
			return false;
		}
		if (user.getDepartment() == "��ǻ�Ͱ��а�")
			input_value.push_back("0");
		else if (user.getDepartment() == "����Ʈ�����а�")
			input_value.push_back("1");
		else if (user.getDepartment() == "��ǻ�Ͱ��к�")
			input_value.push_back("2");
		inputSubjectScore();

		fout.open("./Student_Info/" + user.getSchoolId() + ".txt");
		fin.open("./Student_info/" + user.getSchoolId() + ".txt");
		if (!(fin.is_open())) {
			cout << "�й����� �����ΰ� �����ϴ�." << endl;
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
	//warning C4018 ������ ����
	int size = str.length();
	//�ѱ� ���� ���� ����
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
		cout << "�Է� ���ڿ� ���ڰ� �ƴѰ� �ֽ��ϴ�.( " + result + " )" << endl;
		return false;
	}
}

bool GS_Manager::compareLength(string &school_id)
{
	int size = school_id.length();
	if (size == 9)
		return true;
	else if (size > 9) {
		cout << "�Է��� �й��� �ʹ� ��ϴ�." << endl;
		return false;
	}
	else {
		for (int i = 0; i < 9 - size; i++) {
			school_id.append(" ");
		}
		cout << "�Է��� �й��� �ʹ� ª���ϴ�." << endl;
		return false;
	}
}

bool GS_Manager::compareLength(string str, int length)
{
	//warning C4018 ������ ����
	int size = str.length();
	if (size > length) {
		cout << "�Է��� ���� �ʹ� ��ϴ�." << endl;
		return false;
	}
	else if (size == 0) {
		cout << "�Է��� ���� �ʹ� ª���ϴ�." << endl;
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
	if (id_year == "19"&&user.getDepartment() == "��ǻ�Ͱ��к�") {
		id_year = "20";
	}
	fin_yoram.open("./Booklet/" + id_year + user.getDepartment() + ".txt");
	if (fin_yoram.is_open()) {
		readYoramFile();
		return true;
	}
	else {
		cout << "��������� �������� �ʽ��ϴ�." << endl;
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
		if (str_data == "��") {
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
			name = str_token1.substr(0, credit_delimiter) + " �Ǵ� ";
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
		cout << "�й��� �Է��� �ּ��� : ";
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
		cout << "�а��� �Է��ϼ���(��ǻ�Ͱ��а�/����Ʈ�����а�/��ǻ�Ͱ��к�) : ";
		getline(cin, department);
		if (department == "��ǻ�Ͱ��а�" || department == "����Ʈ�����а�" || department == "��ǻ�Ͱ��к�") {
			user.setDepartment(department);
			break;
		}
		else {
			cout << "��ȿ���� ���� �Է��Դϴ�." << endl;
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
	//warning C4018 ������ ����
	int size;
	//����� �Է°� ����
	string subject_score;
	//���� ���� ����
	vector<Subject> subjects;

	int count = 1;
	int major_score = -1;
	bool skip = false;

	for (int i = 0; i < 8; i++) {
		subjects = yoram.getSubjects(i);
		if (!subjects.empty()) {
			size = subjects.size();
			//�ݺ���µǸ� �ȵǴ� ��츸 ������
			if (i == 2)
				cout << "��������" << endl;
			else if (i == 6)
				cout << "���� �н� ����" << endl;
			else if (i == 7)
				cout << "�ʼ������̼�" << endl;
			for (int j = 0; j < size; j++) {
				if (i == 0 || i == 1) {
					while (true) {
						if (i == 0)
							cout << "����";
						else
							cout << "��ȭ";
						cout << "���� " << subjects[j].getName() << " ���� ���� : ";
						getline(cin, subject_score);
						if (subject_score == "b" || subject_score == "B") {
							if (j == 0) {
								if (i == 0) {
									cout << "���� ������ �������� �ʽ��ϴ�." << endl;
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
						cout << subjects[j].getName() << "��(��) �̼��ϼ̽��ϱ�? (Y/N) : ";
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
							cout << "��ȿ���� ���� �Է��Դϴ�." << endl;
						}
					}
				}
				else if (i == 3 || i == 4) {
					while (true) {
						cout << subjects[j].getName() << " ���� : ";
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
							cout << "�����ʼ� ���� : ";
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
							cout << subjects[j].getName() << "��(��) �̼��ϼ̽��ϱ�? (Y/N) : ";
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
								cout << "��ȿ���� ���� �Է��Դϴ�." << endl;
							}
						}
					}
				}
				else if (i == 6) {
					while (true) {
						cout << subjects[j].getName() << "��(��) �н�(������ü)�ϼ̽��ϱ�? (Y/N) : ";
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
							cout << "��ȿ���� ���� �Է��Դϴ�." << endl;
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
	//warning C4018 ������ ����
	int size;
	cout << endl << "===============================" << endl;
	cout << "�й� : " << user.getSchoolId() << endl;
	cout << "�Ҽ� : " << user.getDepartment() << endl;
	cout << "===============================" << endl;
	//����� �� ����
	string input_score;
	int subject_score;
	//���� ���� ����
	vector<Subject> subjects;
	//��¿� ����
	int user_credit = 0;
	int yoram_credit = 0;
	//���ʱ��� ���
	subjects = yoram.getSubjects(0);
	cout << "���ʱ���" << endl;
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		getline(fin, input_score);
		cout << subjects[i].getName() << " : " << input_score << "����/" << subjects[i].getSubjectScore() << "����" << endl;
		subject_score = stoi(input_score);
		user_credit += subject_score;
		yoram_credit += subjects[i].getSubjectScore();
	}
	cout << endl << "�� ���ʱ������� : " << user_credit << "����/" << yoram_credit << "����" << endl << endl;
	user.addTotalCredit(user_credit);
	if (user.getCangraduation()) {
		if (user_credit < yoram_credit) {
			user.setCangraduation(false);
		}
	}

	//��ȭ���� ���
	subjects = yoram.getSubjects(1);
	cout << "��ȭ����" << endl;
	user_credit = 0;
	yoram_credit = 0;
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		getline(fin, input_score);
		cout << subjects[i].getName() << " : " << input_score << "����/" << subjects[i].getSubjectScore() << "����" << endl;
		subject_score = stoi(input_score);
		user_credit += subject_score;
		yoram_credit += subjects[i].getSubjectScore();
	}
	cout << endl << "�� ��ȭ�������� : " << user_credit << "����/" << yoram_credit << "����" << endl << endl;
	user.addTotalCredit(user_credit);
	if (user.getCangraduation()) {
		if (user_credit < yoram_credit) {
			user.setCangraduation(false);
		}
	}

	//�������� ��¹� ����
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
				designation_result += to_string(subjects[i].getSemester()) + "�б� ��������\n";
			}
			else if (subjects[i].getSemester() == 3) {
				designation_result += "1�б� 2�б� ��� ����\n";
			}
		}
		yoram_credit += subjects[i].getSubjectScore();
	}
	designation_result += "\n�������� : " + to_string(user_credit) + "����/" + to_string(yoram_credit) + "����\n";
	user.addTotalCredit(user_credit);
	if (user.getCangraduation()) {
		if (user_credit < yoram_credit) {
			user.setCangraduation(false);
		}
	}

	//�������� ��¹� ����
	subjects = yoram.getSubjects(3);
	string major_result;
	getline(fin, input_score);
	yoram_credit = subjects[0].getSubjectScore();
	major_result = "�������ð��� : " + input_score + "����/" + to_string(yoram_credit) + "����";
	subject_score = stoi(input_score);
	user.addTotalCredit(subject_score);
	if (user.getCangraduation()) {
		if (subject_score < yoram_credit) {
			user.setCangraduation(false);
		}
	}

	//�Ϲݼ��� ���
	subjects = yoram.getSubjects(4);
	getline(fin, input_score);
	cout << "�� �ϼ����� : " << input_score << "����" << endl;
	subject_score = stoi(input_score);
	user.addTotalCredit(subject_score);
	cout << "===============================" << endl;

	//�������� ���
	cout << "��������" << endl;
	cout << "���̼� ���� : " << endl;
	cout << designation_result << endl;
	
	//�����ʼ� ���
	subjects = yoram.getSubjects(5);
	if (!subjects.empty()) {
		user_credit = 0;
		yoram_credit = 0;
		cout << "�����ʼ�" << endl;
		cout << "���̼� ���� : " << endl;
		size = subjects.size();
		for (int i = 0; i < size; i++) {
			getline(fin, input_score);
			if (input_score == "Y") {
				user_credit += subjects[i].getSubjectScore();
			}
			else {
				cout << "-" << subjects[i].getName() << " / ";
				if (subjects[i].getSemester() == 1 || subjects[i].getSemester() == 2) {
					cout << to_string(subjects[i].getSemester()) + "�б� ��������" << endl;
				}
				else if (subjects[i].getSemester() == 3) {
					cout << "1�б� 2�б� ��� ����" << endl;
				}
			}
			yoram_credit += subjects[i].getSubjectScore();
		}
		major_result += ", �����ʼ����� : " + to_string(user_credit) + "����/" + to_string(yoram_credit) + "����";
		user.addTotalCredit(user_credit);
		if (user.getCangraduation()) {
			if (user_credit < yoram_credit) {
				user.setCangraduation(false);
			}
		}
	}
	cout << endl << major_result << endl << endl;
	cout << "===============================" << endl;

	//�н����� ���
	subjects = yoram.getSubjects(6);
	cout << "���� �н�����" << endl;
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

	//�ʼ����� ���
	subjects = yoram.getSubjects(7);
	if (!subjects.empty()) {
		cout << endl << "�ʼ����� ��������";
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
					cout << " / " << to_string(subjects[i].getSemester()) + "�б� ��������" << endl;
				}
				else if (subjects[i].getSemester() == 3) {
					cout << " / 1�б� 2�б� ��� ����" << endl;
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

	//���̼����� ���
	cout << "\n===============================" << endl;
	cout << "�� �̼����� : " << user.getTotalCredit() << "����/" << yoram.getTotalCredit() << "����" << endl;
	cout << "===============================" << endl;
	
	if (user.getCangraduation()) {
		if (user.getTotalCredit()<yoram.getTotalCredit()) {
			user.setCangraduation(false);
		}
	}
	//�������ɿ��� ���
	cout << "���� ���� ���� : ";
	if (user.getCangraduation()) {
		cout << "���� ����!" << endl;
	}
	else {
		cout << "���� �Ұ���!" << endl;
	}

}
