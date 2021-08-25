#include<iostream>
#include"workerManager.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"
using namespace std;


int main() {
	workerManager wm;
	while (true) {
		wm.showMenu();
	}
	system("pause");
	return 0;
}
