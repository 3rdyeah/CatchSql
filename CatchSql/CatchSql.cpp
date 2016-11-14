// CatchSql.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <io.h>
#ifdef __GNUC__
#include <dir.h>
#endif
#include <stdlib.h>
#include <string>
#include <iostream>
#include "CatchSql.h"

#ifdef _MSC_VER
#define _strcpy strcpy_s
#define _strcat strcat_s
#elif defined __GNUC__
#define _strcpy strcpy
#define _strcat strcat
#endif

using namespace std;

CatchSql::CatchSql()
{
}

CatchSql::~CatchSql()
{
}

void CatchSql::setVersionSection(int verBegin, int verEnd)
{
	m_nVerBegin = verBegin;
	m_nVerEnd = verEnd;
}

bool CatchSql::setFolderDir(char* folderDir)
{
	if(folderDir == NULL)
	{
		return false;
	}
#ifdef _MSC_VER
	int err = _strcpy(m_szFolderDir, folderDir);
	if(0 != err)
	{
		return false;
	}
#elif defined __GNUC__
	char* strTmp = _strcpy(m_szFolderDir, folderDir);
	if(!strTmp)
	{
		return false;
	}
#endif
	return true;
}

bool CatchSql::collectSqlFile()
{
	char file[128] = {0};
	char cmd[128] = {0};
	int num = 0;
	_finddata_t filedata;

	if(!m_szFolderDir)
	{
		return false;
	}
	_strcpy(file, m_szFolderDir);
	_strcat(file, "\\*");
	_strcat(file, EXT);

	long hfile = _findfirst(file, &filedata);
	if(-1L == hfile)
	{
		cout<<"--------------------"<<endl<<"没有文件被搜索到(No files found)!"<<endl<<"--------------------"<<endl;
		return false;
	}
	cout<<"--------------------"<<endl<<"搜索到的文件如下(Found files as follows):"<<endl<<"--------------------"<<endl;
	do
	{
		cout<<++num<<">"<<filedata.name<<endl;
		_strcpy(cmd, "svn info ");
		_strcat(cmd, filedata.name);
		system(cmd);
	}while(_findnext(hfile, &filedata) == 0);
	cout<<"--------------------"<<endl;
	return true;
}

bool CatchSql::mergeSqlFile()
{
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int verBegin = 0;
	int verEnd = 0;
	char folderDir[128] = {0};
	CatchSql* csInst = new CatchSql;
	do
	{
		if(!csInst)
		{
			cerr<<"create CatchSql instance failed!"<<endl;
			break;
		}

		cout<<"当前版本号(current version):";
		cin>>verBegin;
		cout<<"更新版本号(update version):";
		cin>>verEnd;
		cout<<"查找目录(search folder):";
		cin>>folderDir;

		csInst->setVersionSection(verBegin, verEnd);
		if(!csInst->setFolderDir(folderDir))
		{
			cerr<<"[Error] set folder dir failed!"<<endl;
			break;
		}

		csInst->collectSqlFile();
		
	}while(0);

	delete csInst;
	csInst = NULL;
	//system("pause");
	return 0;
}

