#pragma once
#include "SQLFieldBuffer.h"
#include <iostream>
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
	std::string GetName() { return this->TableName; }
	SQLFields* GetFields() { return this->sqlFields; }
	template<class t>
	string ToSQLInsert(t obj) {
	return	sqlFields->ToSQLInsert( obj,this->TableName);
	}
	template<class t>
	string ToSQLUpdate(t obj,size_t row) {
		return	sqlFields->UpdateRow(this->TableName,row,obj);
	}
};

