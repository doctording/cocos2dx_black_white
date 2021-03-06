#include "DataUtil.h"

USING_NS_CC;

sqlite3 *pDB = NULL;//数据库指针 
char * errMsg = NULL;//错误信息 
std::string sqlstr;//SQL指令 
int result;//sqlite3_exec返回值 


//创建数据库
void DataUtil::initDB(const char *db)
{
	//打开一个数据库，如果该数据库不存在，则创建一个数据库文件
	result = sqlite3_open(db, &pDB);
	if (result != SQLITE_OK)
		CCLOG("打开数据库失败，错误码:%d ，错误原因:%s\n", result, errMsg);
}

//tableIsExist的回调函数
int isExisted(void * para, int n_column, char ** column_value, char ** column_name)
{
	bool *isExisted_ = (bool*)para;
	*isExisted_ = (**column_value) != '0';
	return 0;
}
//判断表格是否存在
bool DataUtil::tableIsExist(string name)
{
	if (pDB != NULL)
	{
		//判断表是否存在
		bool tableIsExisted;
		sqlstr = "select count(type) from sqlite_master where type='table' and name ='" + name + "'";
		result = sqlite3_exec(pDB, sqlstr.c_str(), isExisted, &tableIsExisted, &errMsg);
		return tableIsExisted;
	}
	return false;
}


//在数据库中判断名为name的表示否存在，如果不存在则创建这张表
//@示例语句string sqls = "create table user(id integer,username text,password text)";
void DataUtil::createTable(string sql, string name)
{
	if (!tableIsExist(name))
	{
		//创建表，设置ID为主键，且自动增加 
		result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
		if (result != SQLITE_OK)
			CCLog("创建表失败，错误码:%d ，错误原因:%s\n", result, errMsg);
	}

}


//删除表格
//@示例语句sqlstr="drop table name"; 
void DataUtil::deleteTable(string sql, string name)
{
	if (tableIsExist(name))
	{
		result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
		if (result != SQLITE_OK)
			CCLog("创建表失败，错误码:%d ，错误原因:%s\n", result, errMsg);
	}
}


//插入数据
//@示例语句sqlstr=" insert into MyTable_1( name ) values ( '擎天柱' ) "; 
void DataUtil::insertData(string sql){
	result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		CCLog("插入记录失败，错误码:%d ，错误原因:%s\n", result, errMsg);
}


//删除数据
//@示例语句sqlstr="delete from MyTable_1 where ID = 2"; 
void DataUtil::deleteData(string sql)
{
	result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		CCLog("插入记录失败，错误码:%d ，错误原因:%s\n", result, errMsg);
}


//修改数据
//@示例语句        sqlstr="update MyTable_1 set name='威震天' where ID = 3"; 
void DataUtil::updateData(string sql)
{
	result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		CCLog("插入记录失败，错误码:%d ，错误原因:%s\n", result, errMsg);
}

//getDataCount的回调函数
int loadRecordCount(void * para, int n_column, char ** column_value, char ** column_name)
{
	int *count = (int*)para;
	*count = n_column;
	return 0;
}

//获取记录的条数
//@示例语句string sqlsssss = "select count(*) from user";
//@示例语句  取得表格字段的语句string sqlsssss = "select * from user";
int DataUtil::getDataCount(string sql)
{
	int count = 0;
	sqlite3_exec(pDB, sql.c_str(), loadRecordCount, &count, &errMsg);
	return count;
}

char* DataUtil::pScore = NULL;

//getDataInfo的回调函数
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

//获取一条记录的信息 其中的pSend是一个实体类我们以后可以自定义一个继承了CCObject的类来代替他保存数据库中取出来的数据
void DataUtil::getDataInfo(string sql, cocos2d::CCObject *pSend)
{
	/*sqlite3_exec(pDB, sql.c_str(), loadRecord, NULL, &errMsg);*/
	sqlite3_exec(pDB, sql.c_str(), loadRecord, NULL, &errMsg);
}

//void DataUtil::noCallData(std::string sqlstr, char **dbResult, int* row,int *column)
//{
//	sqlite3_get_table(pDB, sqlstr.c_str(), &dbResult, row, column, &errMsg);
//}

//关闭数据库
void DataUtil::closeDB()
{
	sqlite3_close(pDB);
}