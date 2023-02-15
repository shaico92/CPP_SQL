#pragma once
#include "Dependencies.h"
#include "FieldTypes.h"



class SQLField
{
	friend class SQLFields;
	friend class SQLFactory;
	FieldType type;
	int bufferOffeset;
	int size;
	std::string fieldName;
	std::string TypeToSql();
	SQLField(FieldType type, int bufferOffeset, std::string name, int size);
	
	
};


