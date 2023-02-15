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
	void StringToBuffer(SQLField* ptr,char* buffer,char* value) {
		switch (ptr->type)
		{
		case _int_: {
			int d = stod(value);
			memcpy_s(buffer+ ptr->bufferOffeset, ptr->size, &d, ptr->size);

			break;
		}
		case _double_:
		{
			double d = stod(value);;
			memcpy_s(buffer + ptr->bufferOffeset, ptr->size, &d, ptr->size);

			break;
		}
		case _long_:
		{

			long d = stol(value);
			memcpy_s(buffer + ptr->bufferOffeset, ptr->size, &d, ptr->size);

			break;
		}
		case _string_:
		{
			memcpy_s(buffer + ptr->bufferOffeset, ptr->size, value, ptr->size);
		
			break;
		}

		default:
			break;
		}
	}

public:
	SQLFactory(std::string dbpath);
	~SQLFactory();
	void RegisterClass(SQLObject* sqlClass);
	int CreateTable(SQLObject* sqlClass);
	
	

	template<class t>
	int GetTable( SQLObject* sqlClass ,map<size_t,t>& data) {
	;
	int rows = 0, columns = 0;
	size_t rowIndex = 1;
		char** results;
		string sql = "SELECT * FROM "; //+GetName() + "(column_name datatype, column_name datatype);"
		sql.append(sqlClass->GetName());
		int rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &zErrMsg);
		std::map<std::string, SQLField*>::iterator it;
		std::map<std::string, SQLField*> map= sqlClass->GetFields()->GetFields();
		char* buffer = NULL;
		 buffer = new	char[sqlClass->GetFields()->GetBufferSize()];
		size_t i = columns;
		size_t indexLocation = 0;
		it = map.begin();
		


		while (i<(rows+1)*columns)
		{
			StringToBuffer(it->second, buffer, results[i]);
			
			++i;
			++it;
			++indexLocation;
			if (indexLocation>= columns)
			{
				t object_;
				memcpy_s(&object_, sqlClass->GetFields()->GetBufferSize(), buffer, sqlClass->GetFields()->GetBufferSize());
				delete buffer;
				buffer = NULL;
				buffer = new	char[sqlClass->GetFields()->GetBufferSize()];
				data[rowIndex]=(object_);
				
				++rowIndex;
				indexLocation = 0;
				it = map.begin();


			}

		}

		
		

		return rc;
	}
	int InsertObject(std::string Query);
};

