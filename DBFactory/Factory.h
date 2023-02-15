#pragma once
#include <iostream>
#include <string> 
#include <map>
#include "../external/sqlite3.h"
using namespace std;
enum StructsDefined
{
	cl1,
	cl2,
	cl3,
	cl4

};
class GenericSQLClass {
public:
	virtual  char* CreateTable() = 0;
	
	virtual char* InsertData(GenericSQLClass* t) = 0;
	virtual char* GetAllData() = 0;
	
	//virtual void Insert(GenericSQLClass* ptr) = 0;
//	virtual void GetAll() = 0;
	string GetName() { return  tableName; }

protected:
	GenericSQLClass(string tableName) { this->tableName = tableName; }
	string tableName;
};


class TypeOfGeneric2 : public GenericSQLClass {
	int id;
	int age;

	
	 char* 	 CreateTable() {
		string sqlCreate = "CREATE TABLE IF NOT EXISTS "; //+GetName() + "(column_name datatype, column_name datatype);"
		sqlCreate.append(GetName());
		sqlCreate.append(" (");
		sqlCreate.append("id INT  NOT NULL");
		sqlCreate.append(" , ");
		sqlCreate.append("age INT");
		sqlCreate.append(" );");
		

		
		char* sql= new char[sqlCreate.size()];
		char* start = sql;
		memcpy_s(sql, sqlCreate.size(), sqlCreate.c_str(), sqlCreate.size());
		sql += sqlCreate.size();
		*sql = 0;
		return start;
	
	}
	
	 char* InsertData(GenericSQLClass* t) {
		 string sqlCreate = "INSERT INTO "; //+GetName() + "(column_name datatype, column_name datatype);"
		 sqlCreate.append(GetName());
		 sqlCreate.append(" (");
		 sqlCreate.append("id ");
		 sqlCreate.append(" , ");
		 sqlCreate.append("age ");
		 sqlCreate.append(" )");
		 sqlCreate.append(" VALUES");
		 sqlCreate.append(" (");
		 
		 TypeOfGeneric2* t1 = (TypeOfGeneric2*)t;
		 sqlCreate.append(to_string(long long(t1->id)));
		 sqlCreate.append(" , ");
		 sqlCreate.append(to_string(long long(t1->age)));
		 sqlCreate.append(" );");
		 char* sql = new char[sqlCreate.size()];
		 char* start = sql;
		 memcpy_s(sql, sqlCreate.size(), sqlCreate.c_str(), sqlCreate.size());
		 sql += sqlCreate.size();
		 *sql = 0;
		 return start;
	}
	
	 char* GetAllData() {
		 string sqlCreate = "SELECT * FROM "; //+GetName() + "(column_name datatype, column_name datatype);"
		 sqlCreate.append(GetName());
		 char* sql = new char[sqlCreate.size()];
		 char* start = sql;
		 memcpy_s(sql, sqlCreate.size(), sqlCreate.c_str(), sqlCreate.size());
		 sql += sqlCreate.size();
		 *sql = 0;
		 return start;
	 }

public:
	
	void setValues(int id, int age) {
		this->id = id;
		this->age = age;
	}
	

	TypeOfGeneric2(string name) :GenericSQLClass(name) {
		
	}

};
class SQLFactory
{
public:
	SQLFactory(string dbpath);
	~SQLFactory();
	void registerStruct(StructsDefined type, GenericSQLClass* class_);

	string GetClassName(StructsDefined type);
	void insert(StructsDefined type, GenericSQLClass* t);
	string getAllData(StructsDefined type);
	void* GetCallBack(StructsDefined type);
	void registerStructCallback(StructsDefined type, void* f);
private:
	string dbPath;
	 const char* data;
	 void* _data;
	void createTable(StructsDefined type);
	sqlite3* db;
	char* zErrMsg = 0;
	map< StructsDefined, void*> callBacks;
	map<StructsDefined, GenericSQLClass*> map;

};

SQLFactory::SQLFactory(string dbpath)
{
	dbPath = dbpath.append(".db");
	int res= sqlite3_open(dbPath.c_str(),&db);
	 data = "Callback function called";
	
}
void *SQLFactory::GetCallBack(StructsDefined type)
{
	return (int(*)(void*, int, char**, char**))callBacks[type];

}
string SQLFactory::getAllData(StructsDefined type)
{
	char* sql = map[type]->GetAllData();
	char* fa = new char();
	char* fa2 = new char();
	auto df = (int(*)(void*, int, char**, char**)) callBacks[type];
	int rc = sqlite3_exec(db, sql, df,0, &zErrMsg);
	auto f = (char*)_data;
	cout << f;
	return "";
}
SQLFactory::~SQLFactory()
{
}
string SQLFactory::GetClassName(StructsDefined type) {
	return map[type]->GetName();
}
void SQLFactory::registerStruct(StructsDefined type, GenericSQLClass* class_) {

	map[type] = class_;

	createTable(type);
}
void SQLFactory::registerStructCallback(StructsDefined type,void* f) {

	callBacks[type] = f;

	
}
void SQLFactory::createTable(StructsDefined type) {
	char* sql=map[type]->CreateTable();
	int rc = sqlite3_exec(db, sql, (int(*)(void*, int, char**, char**)) callBacks[type], 0, &zErrMsg);
	
	;
}
void SQLFactory::insert(StructsDefined type, GenericSQLClass* t) {

	char* sql=	map[type]->InsertData(t);
	int rc = sqlite3_exec(db, sql, (int(*)(void*, int, char**, char**)) callBacks[type], 0, &zErrMsg);

	delete t;
}

static int callback1(void* data, int argc, char** argv, char** azColName) {
	int i;
	cout << "type1";
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}
static int callback2(void* data, int argc, char** argv, char** azColName) {
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

