#pragma once
#include "Dependencies.h"
#include "SQLObject.h"
#include "../external/sqlite3.h"
#include "Filter.h"



extern "C++" SQLFACTORY_API class  SQLFactory
{

	
	const char* data;
	std::string dbPath;
	sqlite3* db;
	char* zErrMsg = 0;
	std::map<std::string, SQLObject*> registered;
	void StringToBuffer(SQLField* ptr, char* buffer, char* value);
	int Execute(SQLObject* obj, unordered_map<size_t, char*>& data,size_t& size,const Filter filter);
	int Execute(SQLObject* obj, unordered_map<size_t, char*>& data, size_t& size, const vector<Filter>& filters);
	void open();
	void close();
public:
	SQLFACTORY_API SQLFactory(std::string dbpath);
	SQLFACTORY_API	~SQLFactory();
	SQLFACTORY_API	void RegisterClass(SQLObject* sqlClass);
	SQLFACTORY_API	int CreateTable(SQLObject* sqlClass);
	
	
	template<class t>
		int GetTable(SQLObject* sqlClass, unordered_map<size_t, t>& data,const Filter& filter);
	template<class t>
		int GetTable(SQLObject* sqlClass, unordered_map<size_t, t>& data, const vector<Filter> & filter);


	SQLFACTORY_API		int InsertObject(const std::string& Query);
	SQLFACTORY_API	int InsertObject(const vector<std::string>& Queries);
	SQLFACTORY_API	int DropTable(const SQLObject* obj);
};

//template implementation
template<class t>
 int SQLFactory::GetTable(SQLObject* sqlClass, unordered_map<size_t, t>& data,const Filter& filter) {
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

	return rc;
}
template<class t>
 int SQLFactory::GetTable(SQLObject* sqlClass, unordered_map<size_t, t>& data, const vector<Filter>& filter) {
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

	return rc;
}

