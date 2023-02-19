#include "SQLFieldBuffer.h"
void SQLFields::addFieldString(std::string fieldName,int size) {

	if (size>MAX_CHARACTERS)
	{
		size = MAX_CHARACTERS;
	}
	
	fields[fieldName] = new SQLField(FieldType::_string_, bufferSize, fieldName, size);
	bufferSize += size;
}
void SQLFields::addFieldWString(std::string fieldName, int size) {

	if (size > MAX_CHARACTERS)
	{
		size = MAX_CHARACTERS;
	}

	fields[fieldName] = new SQLField(FieldType::_wstring_, bufferSize, fieldName, size);
	bufferSize += size;
}

void SQLFields::addFieldInt(std::string fieldName, int obj) {
	fields[fieldName] = new SQLField(FieldType::_int_, bufferSize, fieldName, sizeof(obj));
	bufferSize += sizeof(obj);
}
void SQLFields::addFieldDouble(std::string fieldName, double obj) {
	fields[fieldName] = new SQLField(FieldType::_double_, bufferSize, fieldName, sizeof(obj));
	bufferSize += sizeof(obj);
}
void SQLFields::addFieldFloat(std::string fieldName, float obj) {
	fields[fieldName] = new SQLField(FieldType::_float_, bufferSize, fieldName, sizeof(obj));
	bufferSize += sizeof(obj);
}
void SQLFields::addFieldlong(std::string fieldName, long obj) {
	fields[fieldName] = new SQLField(FieldType::_long_, bufferSize, fieldName, sizeof(obj));
	bufferSize += sizeof(obj);
}
void SQLFields::addFieldlonglong(std::string fieldName, long long obj) {
	fields[fieldName] = new SQLField(FieldType::_longlong_, bufferSize, fieldName, sizeof(obj));
	bufferSize += sizeof(obj);
}
void SQLFields::addFieldlongDouble(std::string fieldName, long double obj) {
	fields[fieldName] = new SQLField(FieldType::_longDouble, bufferSize, fieldName, sizeof(obj));
	bufferSize += sizeof(obj);
}
std::string SQLFields::BufferValue(const SQLField* ptr, char* data) {
	switch (ptr->type)
	{
	case _int_:
	{
		int d = 0;
		memcpy_s(&d, ptr->size, data, ptr->size);

		return std::to_string(d);
	}
	case _double_:
	{
		double doiu = 0;
		memcpy_s(&doiu, ptr->size, data, ptr->size);

		return std::to_string(doiu);
	}
	case _long_:
	{

		long d = 0;
		memcpy_s(&d, ptr->size, data, ptr->size);

		return std::to_string(d);
	}

	case _wstring_:
	{
		

	
	}

	case _string_:
	{
		char mem[MAX_CHARACTERS];
		mem[0] = '\"';

		//iterate each letter

		memcpy_s(&mem[1], ptr->size, data, ptr->size);
		size_t i = 0;
		while (mem[i]!='\0')
		{
			++i;
		}
		mem[i] = '\"';
		
		for (size_t J = i; J < MAX_CHARACTERS; J++)
		{
			if (J>i)
			{
				mem[J] = '\0';
			}

			
		}
		
		return mem;
	}

	default:
		return "";
	}

}