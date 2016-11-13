#include "DataUtil.h"

USING_NS_CC;

sqlite3 *pDB = NULL;//���ݿ�ָ�� 
char * errMsg = NULL;//������Ϣ 
std::string sqlstr;//SQLָ�� 
int result;//sqlite3_exec����ֵ 


//�������ݿ�
void DataUtil::initDB(const char *db)
{
	//��һ�����ݿ⣬��������ݿⲻ���ڣ��򴴽�һ�����ݿ��ļ�
	result = sqlite3_open(db, &pDB);
	if (result != SQLITE_OK)
		CCLOG("�����ݿ�ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
}

//tableIsExist�Ļص�����
int isExisted(void * para, int n_column, char ** column_value, char ** column_name)
{
	bool *isExisted_ = (bool*)para;
	*isExisted_ = (**column_value) != '0';
	return 0;
}
//�жϱ���Ƿ����
bool DataUtil::tableIsExist(string name)
{
	if (pDB != NULL)
	{
		//�жϱ��Ƿ����
		bool tableIsExisted;
		sqlstr = "select count(type) from sqlite_master where type='table' and name ='" + name + "'";
		result = sqlite3_exec(pDB, sqlstr.c_str(), isExisted, &tableIsExisted, &errMsg);
		return tableIsExisted;
	}
	return false;
}


//�����ݿ����ж���Ϊname�ı�ʾ����ڣ�����������򴴽����ű�
//@ʾ�����string sqls = "create table user(id integer,username text,password text)";
void DataUtil::createTable(string sql, string name)
{
	if (!tableIsExist(name))
	{
		//����������IDΪ���������Զ����� 
		result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
		if (result != SQLITE_OK)
			CCLog("������ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
	}

}


//ɾ�����
//@ʾ�����sqlstr="drop table name"; 
void DataUtil::deleteTable(string sql, string name)
{
	if (tableIsExist(name))
	{
		result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
		if (result != SQLITE_OK)
			CCLog("������ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
	}
}


//��������
//@ʾ�����sqlstr=" insert into MyTable_1( name ) values ( '������' ) "; 
void DataUtil::insertData(string sql){
	result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		CCLog("�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
}


//ɾ������
//@ʾ�����sqlstr="delete from MyTable_1 where ID = 2"; 
void DataUtil::deleteData(string sql)
{
	result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		CCLog("�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
}


//�޸�����
//@ʾ�����        sqlstr="update MyTable_1 set name='������' where ID = 3"; 
void DataUtil::updateData(string sql)
{
	result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		CCLog("�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
}

//getDataCount�Ļص�����
int loadRecordCount(void * para, int n_column, char ** column_value, char ** column_name)
{
	int *count = (int*)para;
	*count = n_column;
	return 0;
}

//��ȡ��¼������
//@ʾ�����string sqlsssss = "select count(*) from user";
//@ʾ�����  ȡ�ñ���ֶε����string sqlsssss = "select * from user";
int DataUtil::getDataCount(string sql)
{
	int count = 0;
	sqlite3_exec(pDB, sql.c_str(), loadRecordCount, &count, &errMsg);
	return count;
}

char* DataUtil::pScore = NULL;

//getDataInfo�Ļص�����
int loadRecord(void * para, int n_column, char ** column_value, char ** column_name)
{
	CCLog("id=%s,score=%s", column_value[0], column_value[2]);
	int len = strlen(column_value[0]);
	CCLOG("scoreLen=%d", len);
	DataUtil::pScore = new char[len + 1];
	DataUtil::pScore[len] = '\0';
	strcpy(DataUtil::pScore, column_value[0]);
	return 0;
}

//��ȡһ����¼����Ϣ ���е�pSend��һ��ʵ���������Ժ�����Զ���һ���̳���CCObject�������������������ݿ���ȡ����������
void DataUtil::getDataInfo(string sql, cocos2d::CCObject *pSend)
{
	/*sqlite3_exec(pDB, sql.c_str(), loadRecord, NULL, &errMsg);*/
	sqlite3_exec(pDB, sql.c_str(), loadRecord, NULL, &errMsg);
}

//void DataUtil::noCallData(std::string sqlstr, char **dbResult, int* row,int *column)
//{
//	sqlite3_get_table(pDB, sqlstr.c_str(), &dbResult, row, column, &errMsg);
//}

//�ر����ݿ�
void DataUtil::closeDB()
{
	sqlite3_close(pDB);
}