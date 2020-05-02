#include <iostream>
#include <string>
#include <fstream>
#include "Yoram.h"
using namespace std;

ostream& operator<< (ostream& out, Subject &sub) {
	out << sub.getName() << endl << sub.getSubjectScore() << endl << sub.getIsTakeClass() << endl;
	return out;
}

int main()
{
	Yoram yoram;
	string filename = "19소프트웨어학과.txt";
	ifstream in;
	in.open(filename, ios::in);
	string str;
	string total = "";
	while (in >> str, !in.eof()) {
		if (str != "@"&& str != "★") { str += "●"; }
		total += str;
	}
	
	vector<Subject>sub =  yoram.read(total);
	vector<Subject>::iterator it;
	for (it = sub.begin(); it < sub.end(); it++) {
		cout << *it;
	}
	in.close();
}