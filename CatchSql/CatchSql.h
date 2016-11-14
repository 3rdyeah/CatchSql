#ifndef __CATCH_SQL_H__
#define __CATCH_SQL_H__

#define EXT ".sql"

typedef struct _fileinfo
{
	int m_nVersion;
	char* m_szName;
	char* m_szDir;
	
}T_FileInfo;

class CatchSql
{
public:
	CatchSql();
	~CatchSql();
	void setVersionSection(int verBegin, int verEnd);
	bool setFolderDir(char* folderDir);
	bool collectSqlFile();
	bool mergeSqlFile();
private:
	char m_szFolderDir[128];
	int m_nVerBegin;
	int m_nVerEnd;
};

#endif