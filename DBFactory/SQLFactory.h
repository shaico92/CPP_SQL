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
	int GetTable( SQLObject* sqlClass , unordered_map<size_t,t>& data) {
	;
	int rows = 0, columns = 0;
	size_t rowIndex = 1;
		char** results;
		string sql = "SELECT ROWID,* FROM "; //+GetName() + "(column_name datatype, column_name datatype);"
		sql.append(sqlClass->GetName());
		sql.append(" ORDER BY id DESC ;");
		int rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &zErrMsg);
		if (rows<1)
		{
			return 0;
		}
		std::map<std::string, SQLField*>::iterator it;
		std::map<std::string, SQLField*> map= sqlClass->GetFields()->GetFields();
		char* buffer = NULL;
		 buffer = new	char[sqlClass->GetFields()->GetBufferSize()];
		size_t i = columns;
		size_t indexLocation = 0;
		it = map.begin();
		size_t row = 0;


		while (i<(rows+1)*(columns))
		{
			if (i%(columns)==0)
			{

				
				row=	stoi(results[i]);
				it = map.begin();
				++i;
				continue;
			}
			StringToBuffer(it->second, buffer, results[i]);
			
			++i;
			++it;
			++indexLocation;
			if (indexLocation>= (columns-1))
			{
				t object_;
				memcpy_s(&object_, sqlClass->GetFields()->GetBufferSize(), buffer, sqlClass->GetFields()->GetBufferSize());
				delete buffer;
				buffer = NULL;
				buffer = new	char[sqlClass->GetFields()->GetBufferSize()];
				data[row]=(object_);
				
				
				indexLocation = 0;
				


			}

		}

		
		

		return rc;
	}
	int InsertObject(std::string Query);
};

