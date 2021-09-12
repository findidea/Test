#include <iostream>
#include "workManager.h"
using namespace std;

//#include "worker.h"
//#include "employee.h"
//#include "manager.h"
//#include "boss.h"

int main(void)
{
	//Worker* worker = NULL;
	//worker = new Employee(1, "张三", 1);
	//worker->showInfo();
	//delete worker;

	//worker = new Manager(2, "李四", 2);
	//worker->showInfo();
	//delete worker;

	//worker = new Boss(3, "王五", 3);
	//worker->showInfo();
	//delete worker;

	WorkManager wm;
	int choice = 9;
	while (true)
	{
		wm.Show_Menu();
		cout << "请输入你的选择:" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://退出系统
			wm.ExitSystem();
			break;
		case 1://增加职工
			wm.Add_Emp();
			break;
		case 2://显示职工
			wm.Show_Emp();
			break;
		case 3://删除职工
			break;
		case 4://修改职工
			break;
		case 5://查找职工
			break;
		case 6://排序职工
			break;
		case 7://清空文档
			break;
		default:
			system("cls");//清屏
			break;
		}
	}

	system("pause");
	
	return 0;
}