#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
class Employee :public Worker
{
public:
	Employee(int mid, string mname, int mdid);
	virtual void showInfo();
	virtual string getDepName();
};
