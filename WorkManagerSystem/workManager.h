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

	void exitSystem();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	Worker** m_EmpArray;

	//添加职工
	void Add_Emp();

	//保存文件
	void save();

	//文件是否存在
	bool m_FileIsEmpty;

	//统计文件中人数
	int get_EmpNum();

	//初始化职工
	void init_Emp();

	//显示职工
	void show_Emp();
};

