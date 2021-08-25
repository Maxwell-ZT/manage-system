#include "Manager.h"

Manager::Manager(int mid, string mname, int mdepid)
{
	this->m_ID = mid;
	this->m_Name = mname;
	this->m_DepID = mdepid;
}

void Manager::showInfo()
{
	cout << "职工编号:" << this->m_ID
		<< "\t职工姓名:" << this->m_Name
		<< "\t岗位:" << this->getDepName()
		<< "\t岗位职责:交代任务给员工！" << endl;
}

string Manager::getDepName()
{
	return string("经理");
}
