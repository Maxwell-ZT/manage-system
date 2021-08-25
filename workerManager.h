#pragma once
#include<iostream>
#include"Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"
#include<fstream>
#define filename "worker.txt"
using namespace std;
class workerManager
{
public:
	int m_Empnum;
	Worker** m_EmpArray;
	bool m_fileisEmpty;
	workerManager();
	void showMenu();
	void exitSystem();
	void Add_emp();
	void save();
	int getNum();
	void init_Emp();
	void show_Emp();
	int exist_Emp(int mid);
	void delete_Emp(int mid);
	void change_Emp();
	void search_Emp(int id);
	void sort_Emp();
	void delete_file();
	~workerManager();
};
