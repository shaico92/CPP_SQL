#pragma once
#include "Dependencies.h"
#include "SQLObject.h"
#include "../external/sqlite3.h"

class  SQLFactory
{
	
	
	const char* data;
	std::string dbPath;
	sqlite3* db;
	char* zErrMsg = 0;
	std::map<std::string, SQLObject*> registered;
	void StringToBuffer(SQLField* ptr, char* buffer, char* value);
	int Execute(SQLObject* obj
		, int& rows
		, int& columns
		, char**& res
		, char*& buffer
		, std::unordered_map<std::string, SQLField*>::iterator& it
		, std::unordered_map<std::string, SQLField*>& map);
public:
	SQLFactory(std::string dbpath);
	~SQLFactory();
	void RegisterClass(SQLObject* sqlClass);
	int CreateTable(SQLObject* sqlClass);
	
	

	
	template<class t>
	int GetTable(SQLObject* sqlClass, unordered_map<size_t, t>& data);
	int InsertObject(const std::string& Query);
	int InsertObject(const vector<std::string>& Queries);
	int DropTable(const SQLObject* obj);
};

//template implementation

template<class t>
int SQLFactory::GetTable(SQLObject* sqlClass, unordered_map<size_t, t>& data) {
	;
	int rows = 0, columns = 0;
	size_t rowIndex = 1;
	char** results=NULL;
	std::unordered_map<std::string, SQLField*>::iterator it;
	std::unordered_map<std::string, SQLField*> map;
	char* buffer = NULL;
	int rc= Execute(sqlClass, rows, columns, results,buffer,it,map);
	if (rc!=0)
	{
		return rc;
	}





	size_t i = columns;
	size_t indexLocation = 0;
	size_t row = 0;

	while (i < (rows + 1) * (columns))
	{
		if (i % (columns) == 0)
		{


			row = stoi(results[i]);
			it = map.begin();
			++i;
			continue;
		}
		StringToBuffer(it->second, buffer, results[i]);

		++i;
		++it;
		++indexLocation;
		if (indexLocation >= (columns - 1))
		{
			t object_;
			memcpy_s(&object_, sqlClass->GetFields()->GetBufferSize(), buffer, sqlClass->GetFields()->GetBufferSize());
			delete buffer;
			buffer = NULL;
			buffer = new	char[sqlClass->GetFields()->GetBufferSize()];
			data[row] = (object_);


			indexLocation = 0;



		}

	}




	return rc;
}



