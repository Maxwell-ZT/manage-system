#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
using namespace std;
class Manager :public Worker
{
public:
	Manager(int mid, string mname, int mdepid);
	virtual void showInfo();
	virtual string getDepName();
};