#include "Employee.h"

Employee::Employee(int mid, string mname, int mdid)
{
	this->m_ID = mid;
	this->m_Name = mname;
	this->m_DepID = mdid;
}

void Employee::showInfo()
{
	cout << "职工编号:" << this->m_ID
		<< "\t职工姓名:" << this->m_Name
		<< "\t岗位:" << this->getDepName()
		<< "\t岗位职责:完成经理交代得任务！" << endl;

}

string Employee::getDepName()
{
	return string("员工");
}
