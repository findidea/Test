#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
#define FILENAME "empFile.txt"

class WorkManager
{
public:
	WorkManager();

	void Show_Menu();

	~WorkManager();

	void ExitSystem();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	Worker** m_EmpArray;

	//添加职工
	void Add_Emp();

	//保存文件
	void Save();

	//文件是否存在
	bool m_FileIsEmpty;

	//统计文件中人数
	int Get_EmpNum();

	//初始化职工
	void Init_Emp();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp();

	//判断职工是否存在，如果存在返回数组中的位置，不存在返回-1
	int IsExist(int id);

	//修改职工
	void Mod_Emp();
};

