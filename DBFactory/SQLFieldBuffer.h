#pragma once

#include "SQLField.h"




class SQLFields
{

	friend class SQLObject;

public:
	std::map<std::string, SQLField*>& GetFields() { return this->fields; }
	unsigned int GetBufferSize() { return this->bufferSize; }
private:
	unsigned int bufferSize;
	std::map<std::string, SQLField*> fields;
	
	
	void addFieldString(std::string fieldName,int size);
	void addFieldWString(std::string fieldName, std::wstring obj);
	void addFieldInt(std::string fieldName, int obj);
	void addFieldDouble(std::string fieldName, double obj);
	void addFieldFloat(std::string fieldName, float obj);
	void addFieldlong(std::string fieldName, long obj);
	void addFieldlonglong(std::string fieldName, long long obj);
	void addFieldlongDouble(std::string fieldName, long double obj);
	
	template<class t>
	string ToSQLInsert(t obj,string Table) {
		
		std::map<std::string, SQLField*>::iterator it;
		char* buff = new		char[bufferSize];
		memcpy_s(buff, bufferSize, &obj, bufferSize);
		string Query = "INSERT INTO ";
		Query.append(Table);

		Query.append(" (");
		vector< string> values;
		for ( it = fields.begin(); it != fields.end(); it++)
		{
			//iterate each field
			Query.append(it->second->fieldName);
		
			
			values.push_back(BufferValue(it->second, buff + it->second->bufferOffeset));
		
			
			it++;
			if (it == fields.end())
			{
				break;
			}
			else {
				it--;
				Query.append(" , ");
			}
			Query.append(" ");
			//std::cout << it->second->fieldName << ':' << BufferValue(it->second, currentPropery) << std::endl;

			
		
		}
		Query.append(" ) VALUES (");
		for (size_t i = 0; i < values.size(); i++)
		{
			Query.append(values.at(i));
			if (i+1 == values.size())
			{
				break;
			}
			else {
				it--;
				Query.append(" , ");
			}
		}
		Query.append(");");
		return Query;
	}


	template<class t>
	string UpdateRow(string name, size_t row, t obj) {
		string Query = "UPDATE ";
		Query.append(name);
		Query.append(" SET ");
		char* buff = new		char[bufferSize];
		memcpy_s(buff, bufferSize, &obj, bufferSize);
		std::map<std::string, SQLField*> fields = GetFields();
		vector<string> values;
		for (std::map<std::string, SQLField*>::iterator it = fields.begin(); it != fields.end(); it++)
		{
			//iterate each field
			Query.append(it->second->fieldName);

			Query.append("=");
			Query.append(BufferValue(it->second, buff + it->second->bufferOffeset));
			


			it++;
			if (it == fields.end())
			{
				break;
			}
			else {
				it--;
				Query.append(" , ");
			}
			Query.append(" ");
			//std::cout << it->second->fieldName << ':' << BufferValue(it->second, currentPropery) << std::endl;



		}
		delete buff;
		buff = NULL;
		Query.append(" where ROWID=");
		Query.append(to_string(row));
		Query.append(";");
		return Query;
	}
	std::string BufferValue(SQLField* ptr, char* data);
};

