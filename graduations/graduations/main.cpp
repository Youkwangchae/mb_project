#include<iostream>
#include"GS_Manager.h"

using namespace std;

int main() {
	
	GS_Manager manager;
	if (manager.playMain()) {
		cout << "���� ����" << endl;
	}
	else {
		cout << "�Ҿ��� ����" << endl;
	}

	return 0;
}