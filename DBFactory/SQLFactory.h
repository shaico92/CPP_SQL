#pragma once
#include "Dependencies.h"
#include "SQLObject.h"
#include "../external/sqlite3.h"
#include "Filter.h"


enum SQLFactory_status
{
	SUCCESS,
	ERROR
};
extern "C++"  class  SQLFactory
{

	
	const char* data;
	std::string dbPath;
	sqlite3* db;
	char* zErrMsg = 0;
	std::map<std::string, SQLObject*> registered;
	void StringToBuffer(SQLField* ptr, char* buffer, char* value);
	SQLFACTORY_API	 SQLFactory_status Execute(SQLObject* obj, unordered_map<size_t, char*>& data,size_t& size,const Filter filter);
	 SQLFACTORY_API	 SQLFactory_status Execute(SQLObject* obj, unordered_map<size_t, char*>& data, size_t& size, const vector<Filter>& filters);
	 SQLFACTORY_API	 SQLFactory_status Execute(SQLObject* obj, unordered_map<size_t, char*>& data, size_t& size);
	void open();
	void close();
public:
	SQLFACTORY_API SQLFactory(std::string dbpath);
	SQLFACTORY_API	~SQLFactory();
	SQLFACTORY_API	void RegisterClass(SQLObject* sqlClass);
	SQLFACTORY_API	SQLFactory_status CreateTable(SQLObject* sqlClass);
	
	template<class t>
	SQLFactory_status GetTable(SQLObject* sqlClass, unordered_map<size_t, t>& data);
	template<class t>
	SQLFactory_status GetTable(SQLObject* sqlClass, unordered_map<size_t, t>& data,const Filter& filter);
	template<class t>
	SQLFactory_status GetTable(SQLObject* sqlClass, unordered_map<size_t, t>& data, const vector<Filter> & filter);

	SQLFACTORY_API	SQLFactory_status InsertObjectUnsafe(const vector<std::string>& Queries);
	SQLFACTORY_API	SQLFactory_status InsertObject(const std::string& Query);
	SQLFACTORY_API	SQLFactory_status InsertObject(const vector<std::string>& Queries);
	SQLFACTORY_API	SQLFactory_status DropTable(const SQLObject* obj);
};

//template implementation
template<class t>
SQLFactory_status SQLFactory::GetTable(SQLObject* sqlClass, unordered_map<size_t, t>& data,const Filter& filter) {
	;
	
	unordered_map<size_t, char*>mems;
	unordered_map<size_t, char*>::iterator itMems;
	size_t Size = 0;
	int rc = Execute(sqlClass, mems, Size,filter);
	for (itMems = mems.begin(); itMems != mems.end(); itMems++)
	{
		t* obj = (t*)itMems->second;
		data[itMems->first] = *obj;
		
	
		delete[] (itMems->second);
	

		itMems->second = NULL;

	}

	//in case of memory leak use this 
	//close();
	//open();
	mems.clear();

	return (SQLFactory_status)rc;
}
 template<class t>
 SQLFactory_status SQLFactory::GetTable(SQLObject* sqlClass, unordered_map<size_t, t>& data) {
	 ;

	 unordered_map<size_t, char*>mems;
	 unordered_map<size_t, char*>::iterator itMems;
	 size_t Size = 0;
	 int rc = 0; Execute(sqlClass, mems, Size);
	 for (itMems = mems.begin(); itMems != mems.end(); itMems++)
	 {
		 t* obj = (t*)itMems->second;
		 data[itMems->first] = *obj;


		 delete[](itMems->second);


		 itMems->second = NULL;

	 }

	 //in case of memory leak use this 
	 //close();
	 //open();
	 mems.clear();

	 return (SQLFactory_status)rc;
 }
template<class t>
SQLFactory_status SQLFactory::GetTable(SQLObject* sqlClass, unordered_map<size_t, t>& data, const vector<Filter>& filter) {
	;
	
	unordered_map<size_t, char*>mems;
	unordered_map<size_t, char*>::iterator itMems;
	size_t Size = 0;
	int rc = Execute(sqlClass, mems, Size, filter);
	for (itMems = mems.begin(); itMems != mems.end(); itMems++)
	{
		t* obj = (t*)itMems->second;
		data[itMems->first] = *obj;


		delete[](itMems->second);


		itMems->second = NULL;

	}

	//in case of memory leak use this 
	//close();
	//open();
	mems.clear();

	return (SQLFactory_status)rc;
}

