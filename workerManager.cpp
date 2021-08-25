#include "workerManager.h"

workerManager::workerManager()
{
	ifstream ifs(filename, ios::in);
	if (!ifs.is_open()) {
		this->m_Empnum = 0;
		this->m_EmpArray = NULL;
		this->m_fileisEmpty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->m_Empnum = 0;
		this->m_EmpArray = NULL;
		this->m_fileisEmpty = true;
		ifs.close();
		return;
	}
	this->m_fileisEmpty = false;
	this->m_Empnum = this->getNum();
	this->m_EmpArray = new Worker * [this->m_Empnum];
	this->init_Emp();
}

void workerManager::showMenu()
{
	cout << "******************************" << endl;
	cout << "*****欢迎使用职工管理系统*****" << endl;
	cout << "*****0、退出管理程序*****" << endl;
	cout << "*****1、增加职工信息****" << endl;
	cout << "*****2、显示职工信息****" << endl;
	cout << "*****3、删除职工信息****" << endl;
	cout << "*****4、修改职工信息****" << endl;
	cout << "*****5、查找职工信息****" << endl;
	cout << "*****6、按照编号排序****" << endl;
	cout << "*****7、清空所有文档****" << endl;
	cout << "******************************" << endl;
	cout << "请输入您的选择:" << endl;
	int choice;
	cin >> choice;
	switch (choice) {
	case 0://退出系统
		exitSystem();
		break;
	case 1://增加职工信息
		Add_emp();
		break;
	case 2://显示职工信息
		this->show_Emp();
		break;
	case 3://删除职工信息
		cout << "请输入想要删除的职工编号：" << endl;
		int mid;
		cin >> mid;
		this->delete_Emp(mid);
		break;
	case 4://修改职工信息
		this->change_Emp();
		break;
	case 5://查找职工信息
		int id;
		cout << "请输入查找的职工编号：" << endl;
		cin >> id;
		this->search_Emp(id);
		break;
	case 6://按照编号排序
		this->sort_Emp();
		break;
	case 7://清空所有文档
		this->delete_file();
		break;
	default:
		cout << "输入有误，请重新输入" << endl;
		system("pause");
		system("cls");
		break;

	}
}

void workerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void workerManager::Add_emp()
{
	cout << "添加职工的数量：" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		int newsize = addNum + this->m_Empnum;
		Worker** newspace = new Worker * [newsize];
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_Empnum; i++) {
				newspace[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++) {
			int mid;
			string mname = "";
			int mdepid;
			while (true) {
				cout << "请输入第" << i + 1 << "个新职工的编号：" << endl;
				cin >> mid;
				if (this->exist_Emp(mid) != -1) {
					cout << "编号已经存在,请输入一个不存在的编号" << endl;
					continue;
				}
				else break;
			}
			cout << "请输入第" << i + 1 << "个新职工的姓名：" << endl;
			cin >> mname;
			cout << "请输入第" << i + 1 << "个新职工的岗位编号：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> mdepid;
			Worker* worker = NULL;
			switch (mdepid) {
			case 1:
				worker = new Employee(mid, mname, mdepid);
				break;
			case 2:
				worker = new Manager(mid, mname, mdepid);
				break;
			case 3:
				worker = new Boss(mid, mname, mdepid);
				break;
			default:
				break;
			}
			newspace[this->m_Empnum + i] = worker;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = newspace;
		this->m_Empnum = newsize;
		cout << "成功添加了" << addNum << "名职工！" << endl;
		this->m_fileisEmpty = false;
		this->save();
		system("pause");
		system("cls");
	}
	else {
		cout << "输入有误，重新输入" << endl;
	}
}

void workerManager::save()
{
	ofstream ofs(filename, ios::out);
	for (int i = 0; i < this->m_Empnum; i++) {
		ofs << this->m_EmpArray[i]->m_ID << '\t'
			<< this->m_EmpArray[i]->m_Name << '\t'
			<< this->m_EmpArray[i]->m_DepID << endl;
	}
	ofs.close();
}

int workerManager::getNum()
{
	ifstream ifs(filename, ios::in);
	int num = 0;
	int mid, mdepid;
	string mname;
	while (getline(ifs, mname)) {
		num++;
	}
	ifs.close();
	return num;
}

void workerManager::init_Emp()
{
	ifstream ifs(filename, ios::in);
	int mid, mdepid;
	string mname;
	Worker* worker = NULL;
	int index = 0;
	while (ifs >> mid >> mname >> mdepid) {
		switch (mdepid) {
		case 1:
			worker = new Employee(mid, mname, mdepid);
			break;
		case 2:
			worker = new Manager(mid, mname, mdepid);
			break;
		case 3:
			worker = new Boss(mid, mname, mdepid);
			break;
		}
		this->m_EmpArray[index++] = worker;
	}
	ifs.close();
}

void workerManager::show_Emp()
{
	if (this->m_fileisEmpty || this->m_Empnum == 0) {
		cout << "职工人数为0" << endl;
	}
	else {
		for (int i = 0; i < this->m_Empnum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

int workerManager::exist_Emp(int mid)
{
	for (int i = 0; i < this->m_Empnum; i++) {
		if (this->m_EmpArray[i]->m_ID == mid)
			return i;
	}
	return -1;
}

void workerManager::delete_Emp(int mid)
{
	if (this->exist_Emp(mid) == -1) {
		cout << "职工不存在，无法删除" << endl;
	}
	else {
		int index = this->exist_Emp(mid);
		delete this->m_EmpArray[index];
		for (int i = index; i < (this->m_Empnum) - 1; i++) {
			this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		(this->m_Empnum)--;
		this->m_EmpArray[this->m_Empnum] = NULL;
		this->save();
		cout << "删除成功！" << endl;
	}
	system("pause");
	system("cls");
}

void workerManager::change_Emp()
{
	cout << "请输入要修改的职工编号：" << endl;
	int id;
	cin >> id;
	int index = this->exist_Emp(id);
	if (index == -1) {
		cout << "职工不存在" << endl;
	}
	else {
		cout << "请输入要修改的职工姓名：" << endl;
		string name;
		cin >> name;
		cout << "请输入要修改的职工岗位：" << endl;
		cout << "1、普通职工" << endl;
		cout << "2、经理" << endl;
		cout << "3、老板" << endl;
		int depid;
		cin >> depid;
		Worker* worker = NULL;
		switch (depid) {
		case 1:
			worker = new Employee(id, name, depid);
			break;
		case 2:
			worker = new Manager(id, name, depid);
			break;
		case 3:
			worker = new Boss(id, name, depid);
			break;
		}
		delete this->m_EmpArray[index];
		this->m_EmpArray[index] = worker;
		this->save();
		cout << "修改成功！" << endl;
		system("pause");
		system("cls");
	}
}

void workerManager::search_Emp(int id)
{
	int index = this->exist_Emp(id);
	if (index == -1)cout << "职工不存在" << endl;
	else this->m_EmpArray[index]->showInfo();
	system("pause");
	system("cls");
}

void workerManager::sort_Emp()
{
	if (this->m_fileisEmpty) {
		cout << "没有职工" << endl;
		return;
	}
	cout << "选择升序或降序：" << endl;
	cout << "升序：1" << endl;
	cout << "降序：2" << endl;
	int sel;
	cin >> sel;
	if (sel == 1) {
		Worker** worker = this->m_EmpArray;
		bool flag = true;
		for (int i = this->m_Empnum - 1; i >= 0; i--) {
			for (int j = 0; j < i; j++) {
				if (worker[j]->m_ID > worker[j + 1]->m_ID) {
					swap(worker[j], worker[j + 1]);
					flag = false;
				}
			}
			if (flag)break;
		}
	}
	else {
		Worker** worker = this->m_EmpArray;
		bool flag = true;
		for (int i = this->m_Empnum - 1; i >= 0; i--) {
			for (int j = 0; j < i; j++) {
				if (worker[j]->m_ID < worker[j + 1]->m_ID) {
					swap(worker[j], worker[j + 1]);
					flag = false;
				}
			}
			if (flag)break;
		}
	}
	this->save();
	cout << "排序成功" << endl;
	system("pause");
	system("cls");
}

void workerManager::delete_file()
{
	if (this->m_fileisEmpty) {
		cout << "文件不存在" << endl;
		cout << "清空失败" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "确认清空所有文档吗？" << endl;
	cout << "是：1" << endl;
	cout << "否：2" << endl;
	int sel;
	cin >> sel;
	if (sel == 2) {
		cout << "取消清空" << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		for (int i = 0; i < this->m_Empnum; i++) {
			if (this->m_EmpArray[i] == NULL)continue;
			else delete this->m_EmpArray[i];
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
		this->m_Empnum = 0;
		this->m_fileisEmpty = true;
		this->save();
		cout << "成功清空所有文档" << endl;
		system("pause");
		system("cls");
	}
}


workerManager::~workerManager()
{
	if (this->m_EmpArray != NULL) {
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
