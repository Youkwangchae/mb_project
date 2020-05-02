#include<iostream>
#include"GS_Manager.h"

using namespace std;

int main() {
	
	GS_Manager manager;
	if (manager.playMain()) {
		cout << "안전 종료" << endl;
	}
	else {
		cout << "불안전 종료" << endl;
	}

	return 0;
}