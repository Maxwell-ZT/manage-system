#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
using namespace std;
class Boss :public Worker
{
public:
	Boss(int mid, string mname, int mdepid);
	virtual void showInfo();
	virtual string getDepName();
};
