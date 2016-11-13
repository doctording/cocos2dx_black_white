#ifndef _Data_Util_
#define _Data_Util_
#include <string>
#include "sqlite3.h"

#include "cocos2d.h"

using namespace std;

class DataUtil
{
public:
	//��������һ��db���ݿ� dbΪ���ݿ������
	static void initDB(const char *db);
	//�����жϱ���Ƿ����
	static bool tableIsExist(string name);
	//��������һ������Ϊname�ı�񣬴���ʱ����ƥ��ʱ���иñ�Ĵ�����������򲻴���
	static void createTable(string sql, string name);
	//����ɾ��һ�ű���Ϊname�ı��ɾ��ʱ����ƥ���Ƿ��иñ�Ĵ��������������ִ��ɾ������
	static void deleteTable(string sql, string name);
	//��������в���һ������
	static void insertData(string sql);
	//���������ɾ��һ������
	static void deleteData(string sql);
	//����������޸�һ������
	static void updateData(string sql);
	//��ȡһ����¼������
	static int getDataCount(string sql);
	//��ȡһ����¼����Ϣ
	static void getDataInfo(string sql, cocos2d::CCObject *pSend);

	
	//static void noCallData(std::string sqlstr, char **dbResult, int* row, int *column);

	//�رմ򿪵����ݿ�
	static void closeDB();

	static char* pScore;
protected:
	//int isExisted( void * para, int n_column, char ** column_value, char ** column_name );
private:
};
#endif //_Data_Util_