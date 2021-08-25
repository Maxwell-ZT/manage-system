#pragma once
#include<iostream>
#include<string>
using namespace std;
class Worker
{
public:
	int m_ID;
	string m_Name;
	int m_DepID;

	virtual void showInfo() = 0;
	virtual string getDepName() = 0;
};
