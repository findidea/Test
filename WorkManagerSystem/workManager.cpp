#include "workManager.h"

WorkManager::WorkManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	//1.情况1 文件不存在
	if (!ifs.is_open())
	{
		cout << "文本不存在" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2.文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		cout << "文件为空！" << endl;
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.文件存在，并且记录数据
	int num = this->Get_EmpNum();
	cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker * [m_EmpNum];
	this->Init_Emp();
}

void WorkManager::Show_Menu()
{
	cout << "欢迎使用职工管理系统" << endl;
	cout << "0.退出管理系统" << endl;
	cout << "1.增加职工信息" << endl;
	cout << "2.显示职工信息" << endl;
	cout << "3.删除职工信息" << endl;
	cout << "4.修改职工信息" << endl;
	cout << "5.查找职工信息" << endl;
	cout << "6.按照编号排序" << endl;
	cout << "7.清空所有文档" << endl;
	cout << endl;
}

WorkManager::~WorkManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

void WorkManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//添加职工
void WorkManager::Add_Emp()
{
	cout << "请输入添加职工的数量" << endl;
	int addNum = 0;//保存用户的输入数量
	cin >> addNum;
	if (addNum > 0)
	{
		//添加
		//计算添加新空间的大小
		int newSize = this->m_EmpNum + addNum;//新空间人数 = 原来记录人数 + 新增人数
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来空间的数据拷贝到新的数组中
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部们选择

			cout << "请输入第 " << i + 1 << "个新职工编号：" << endl;
			cin >> id;

			cout << "请输入第 " << i + 1 << "个新职工姓名：" << endl;
			cin >> name;

			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			default:
				break;
			}
			//将创建职工，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;

			//释放原有空间
			delete[] this->m_EmpArray;
			//更改新空间的指向
			this->m_EmpArray = newSpace;
			//更新新的职工人数
			this->m_EmpNum = newSize;

			//更新文件不为空
			this->m_FileIsEmpty = true;

			//保存数据到文件中
			this->Save();

			//提示添加成功
			cout << "成功添加" << addNum << "名新职工!" << endl;
		}

	}
	else
	{
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
}

//保存文件
void WorkManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//用输出的方式打开文件 --相当于就是写文件
	//将每个人的数据写到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//关闭文件
	ofs.close();
}

//统计文件中人数
int WorkManager::Get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件 读
	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//
		num++;
	}

	return num;
}

void WorkManager::Init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();
}

//显示职工
void WorkManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//删除职工
void WorkManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入想要删除的职工编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);
		if (index != -1)
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录的人员个数
			//将数据改动同步更新到文件中
			this->Save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该员工" << endl;
		}
	}
	//按任意键 清屏
	system("pause");
	system("cls");
}

//判断职工是否存在，如果存在返回数组中的位置，不存在返回-1
int WorkManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}

	return index;
}

//修改职工
void WorkManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到编号的职工
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到：" << id << "号职工，请输入新职工编号：" << endl;
			cin >> newId;

			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请输入岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//更新数据到数组中
			this->m_EmpArray[ret] = worker;
			cout << "修改成功!" << endl;
		}
	}
}