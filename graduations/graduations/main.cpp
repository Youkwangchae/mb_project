#include<iostream>
#include<stdlib.h>
#include"GS_Manager.h"

int main() {
	
	GS_Manager manager;
	if (manager.playMain()) {
		cout << "프로그램 종료" << endl;
	}
	else {
		cout << "오류로 인한 프로그램 종료" << endl;
	}
	system("pause");

	return 0;
}