#include<iostream>
#include<stdlib.h>
#include"GS_Manager.h"

int main() {
	
	GS_Manager manager;
	if (manager.playMain()) {
		cout << "���α׷� ����" << endl;
	}
	else {
		cout << "������ ���� ���α׷� ����" << endl;
	}
	system("pause");

	return 0;
}