#pragma once
#include "Dependencies.h"
#include "FieldTypes.h"



class SQLField
{
	friend class SQLFields;
	friend class SQLFactory;
	friend class Filter;
	FieldType type;
	int bufferOffeset;
	int size;
	bool primary;
	std::string fieldName;
	std::string tableName;
	std::string TypeToSql()const;
	SQLField(FieldType type, int bufferOffeset, std::string name, int size,std::string tableName="");
	
	
};


