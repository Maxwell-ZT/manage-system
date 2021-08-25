#include "Boss.h"

Boss::Boss(int mid, string mname, int mdepid)
{
	this->m_ID = mid;
	this->m_Name = mname;
	this->m_DepID = mdepid;
}

void Boss::showInfo()
{
	cout << "职工编号:" << this->m_ID
		<< "\t职工姓名:" << this->m_Name
		<< "\t岗位:" << this->getDepName()
		<< "\t岗位职责:管理公司事务！" << endl;
}

string Boss::getDepName()
{
	return string("老板");
}
