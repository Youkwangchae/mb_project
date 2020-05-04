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
			//fout << "0\n";
		else if (user.getDepartment() == "����Ʈ�����а�")
			input_value.push_back("1");
			//fout << "1\n";
		else if (user.getDepartment() == "��ǻ�Ͱ��к�")
			input_value.push_back("2");
			//fout << "2\n";
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
			name = str_token1.substr(0, delimiter) + " �Ǵ� ";
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
	Subject subject;
	//���ʱ��� ����
	subjects = yoram.getBasicLiberal();
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		while (true) {
			cout << "���ʱ��� " << subjects[i].getName() << " ���� ���� : ";
			getline(cin, subject_score);
			subject_score = deleteZero(subject_score);
			if (nonInt(subject_score)*compareLength(subject_score, 3)) {
				input_value.push_back(subject_score);
				//fout << subject_score + "\n";
				break;
			}
		}
	}
	//��ȭ���� ����
	subjects = yoram.getImproveLiberal();
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		while (true) {
			cout << "��ȭ���� " << subjects[i].getName() << " ���� ���� : ";
			getline(cin, subject_score);
			subject_score = deleteZero(subject_score);
			if (nonInt(subject_score)*compareLength(subject_score, 3)) {
				input_value.push_back(subject_score);
				//fout << subject_score + "\n";
				break;
			}
		}
	}
	//�������� ����
	subjects = yoram.getDesignationLiberal();
	cout << "��������" << endl;
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		while (true) {
			cout << subjects[i].getName() << "��(��) �̼��ϼ̽��ϱ�? (Y/N) : ";
			getline(cin, subject_score);
			if (subject_score == "Y"||subject_score == "N") {
				input_value.push_back(subject_score);
				//fout << subject_score + "\n";
				break;
			}
			else {
				cout << "��ȿ���� ���� �Է��Դϴ�." << endl;
			}
		}
	}
	//��������, �Ϲݼ��� ����
	for (int i = 0; i < 2; i++) {
		if (i == 0)
			subject = yoram.getSelectMajor();
		else
			subject = yoram.getSelectLiberal();
		while (true) {
			cout << subject.getName() << " ���� : ";
			getline(cin, subject_score);
			subject_score = deleteZero(subject_score);
			if (nonInt(subject_score)*compareLength(subject_score, 3)) {
				input_value.push_back(subject_score);
				//fout << subject_score + "\n";
				break;
			}
		}
	}
	//�����ʼ� ����
	subjects = yoram.getCompulsoryMajor();
	if (!subjects.empty()) {
		while (true) {
			cout << "�����ʼ� ���� : ";
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
					cout << subjects[i].getName() << "��(��) �̼��ϼ̽��ϱ�? (Y/N) : ";
					getline(cin, subject_score);
					if (subject_score == "Y" || subject_score == "N") {
						input_value.push_back(subject_score);
						//fout << subject_score + "\n";
						break;
					}
					else {
						cout << "��ȿ���� ���� �Է��Դϴ�." << endl;
					}
				}
			}
		}
	}
	//�н����� ����
	subjects = yoram.getPassSubject();
	cout << "���� �н� ����" << endl;
	size = subjects.size();
	for (int i = 0; i < size; i++) {
		while (true) {
			cout << subjects[i].getName() << "��(��) �н�(������ü)�ϼ̽��ϱ�? (Y/N) : ";
			getline(cin, subject_score);
			if (subject_score == "Y" || subject_score == "N") {
				input_value.push_back(subject_score);
				//fout << subject_score + "\n";
				break;
			}
			else {
				cout << "��ȿ���� ���� �Է��Դϴ�." << endl;
			}
		}
	}
	//�ʼ����� ����
	subjects = yoram.getCompulsorySubject();
	cout << "�ʼ������̼�" << endl;
	if (!subjects.empty()) {
		size = subjects.size();
		for (int i = 0; i < size; i++) {
			while (true) {
				cout << subjects[i].getName() << "��(��) �̼��ϼ̽��ϱ�? (Y/N) : ";
				getline(cin, subject_score);
				if (subject_score == "Y" || subject_score == "N") {
					input_value.push_back(subject_score);
					//fout << subject_score + "\n";
					break;
				}
				else {
					cout << "��ȿ���� ���� �Է��Դϴ�." << endl;
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
	Subject subject;
	//��¿� ����
	int user_credit = 0;
	int yoram_credit = 0;
	//���ʱ��� ���
	subjects = yoram.getBasicLiberal();
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
	subjects = yoram.getImproveLiberal();
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
	designation_result += "\n�������� : " + to_string(user_credit) + "����/" + to_string(yoram_credit) + "����\n";
	user.addTotalCredit(user_credit);
	if (user.getCangraduation()) {
		if (user_credit < yoram_credit) {
			user.setCangraduation(false);
		}
	}

	//�������� ��¹� ����
	subject = yoram.getSelectMajor();
	string major_result;
	getline(fin, input_score);
	yoram_credit = subject.getSubjectScore();
	major_result = "�������ð��� : " + input_score + "����/" + to_string(yoram_credit);
	subject_score = stoi(input_score);
	user.addTotalCredit(subject_score);
	if (user.getCangraduation()) {
		if (subject_score < yoram_credit) {
			user.setCangraduation(false);
		}
	}

	//�Ϲݼ��� ���
	subject = yoram.getSelectLiberal();
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
	subjects = yoram.getCompulsoryMajor();
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
				cout << "-" << subjects[i].getName() << endl;
			}
			yoram_credit += subjects[i].getSubjectScore();
		}
		major_result += ", �����ʼ����� : " + to_string(user_credit) + "����/" + to_string(yoram_credit);
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
	subjects = yoram.getPassSubject();
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
	subjects = yoram.getCompulsorySubject();
	cout << endl << "�ʼ����� ��������" << endl;
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

	//���̼����� ���
	cout << "===============================" << endl;
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
