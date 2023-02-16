#pragma once
#include "SQLFieldBuffer.h"

class SQLObject
{
	
	
	std::string TableName;
	virtual void RegisterFields() = 0;
protected:
	void addFieldString(std::string fieldName, int size);
	void addFieldWString(std::string fieldName, std::wstring obj);
	void addFieldInt(std::string fieldName, int obj);
	void addFieldDouble(std::string fieldName, double obj);
	void addFieldFloat(std::string fieldName, float obj);
	void addFieldlong(std::string fieldName, long obj);
	void addFieldlonglong(std::string fieldName, long long obj);
	void addFieldlongDouble(std::string fieldName, long double obj);
	SQLObject(std::string tableName);
	SQLFields* sqlFields;
public:
	 std::string GetName()const { return this->TableName; }
	SQLFields* GetFields() { return this->sqlFields; }
	template<class t>
	string Insert(t obj) {
	return	sqlFields->ToSQLInsert( obj,this->TableName);
	}
	template<class t>
	vector<string> Insert(vector<t> objects) {
		vector<string> vec;
		for (size_t i = 0; i < objects.size(); i++)
		{
			vec.push_back(sqlFields->ToSQLInsert(objects.at(i), this->TableName));
		}
		return vec;
	}
	template<class t>
	string Update(t obj,size_t row) {
		return	sqlFields->UpdateRow(this->TableName,row,obj);
	}
	template<class t>
	vector<string> UpdateRange(vector<pair<size_t,t>> objects) {

		
		vector<string>queries;
		for (size_t i = 0; i < objects.size(); i++)
		{

			const pair<size_t, t> current = objects[i];
		 string query=	sqlFields->UpdateRow(this->TableName, current.first, current.second);
		 queries.push_back(query);
		 
			
		}


		return	queries;
			//
	}


};

