#include "SQLField.h"
SQLField::SQLField(FieldType type, int bufferOffeset, std::string name, int size) {
	this->type = type;
	this->bufferOffeset = bufferOffeset;
	this->fieldName = name;
	this->size = size;
}
string SQLField::TypeToSql() {

	switch (this->type)
	{
	case	_int_:
	case		_double_:
	case		_long_:
	case _longlong_:
	case _longDouble:
	case _float_:
	{
		return "INTEGER ";
	}
	case
			_string_:
	case	_wstring_:
	{
		return "TEXT ";
	}


	}
	return "";
}