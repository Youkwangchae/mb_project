#include "Yoram.h"
string Yoram::getName(string next)
{
	return next;
}

int Yoram::getSubjectScore(int a)
{
	return a;
}

Yoram::Yoram()
{
}

Yoram::Yoram(string student_id, string department)
	:student_id(student_id), department(department)
{
	//생성자에서 파일 read함.
	//읽고 구분자 넣고 붙이고, 읽고 구분자 넣고 붙여서 파일 내용을 string변수 하나에 저장.

	string filename = "19소프트웨어학과.txt";
	ifstream in;
	in.open(filename, ios::in);
	string str;

	while (in >> str, !in.eof()) {
		if (str != "@"&& str != "★") { str += "%"; }

		cout << str << endl;
	}

	in.close();
}

vector<Subject> Yoram::read(string next)
{
	vector<Subject> subject;

	vector<string> first_result = split(next,'@');
	vector<string> ::iterator it;
	for (it = first_result.begin(); it < first_result.end(); it++) {
		vector<string> second_result = split(*it, '●');
		vector<string> ::iterator it_2;
		for (it_2 = second_result.begin(); it_2 < second_result.end()-1; it_2++) {
			vector<string> third_result = split(*it_2, ':');
			vector<string> ::iterator it_a;

			Subject a = Subject(*third_result.begin(),stoi((*(third_result.end()-1))), false);
			subject.push_back(a);
		}

	}
	return subject;
}

//Subject 자료를 저장하는 vector를 매 @ 나올때마다 반환

vector<string> Yoram::split(const string& next, char delimiter)
{
	unsigned int start_pos = 0;
	unsigned int search_pos = 0;
	vector<string> result;
	while (start_pos < next.size()) {
		search_pos = next.find_first_of(delimiter, start_pos);

		string temp;

		if (search_pos == string::npos) {
			search_pos = next.size();
			temp = next.substr(start_pos, search_pos - start_pos);
			result.push_back(temp);
			break;
		}
		temp = next.substr(start_pos, search_pos - start_pos);
		result.push_back(temp);
		start_pos = search_pos + 1;
	}
	return result;
}

Yoram::~Yoram()
{
}