#include "SQLObject.h"


void SQLObject::addFieldString(std::string fieldName, int size) {
	std::string NameForSQL = fieldName;
	for (size_t i = 0; i < fieldName.length(); i++)
	{
		if (fieldName[i]==' ')
		{
			NameForSQL = "";
			NameForSQL.append("[");
			NameForSQL.append(fieldName);
			NameForSQL.append("]");
			break;
		}
	}
	sqlFields->addFieldString(NameForSQL, size);
}
bool SQLObject::GetField(const char* fieldName,SQLField*& ptr) {
	unordered_map<std::string, SQLField*>::iterator it=  this->GetFields()->fields.find(fieldName);

	if (it!= this->GetFields()->fields.end())
	{
		ptr= it->second;
		return true;
	}
	ptr= NULL;
	return false;
}
void SQLObject::addFieldWString(std::string fieldName, std::wstring obj){
	sqlFields->addFieldWString(fieldName, obj);
}
void SQLObject::addFieldInt(std::string fieldName, int obj){
	sqlFields->addFieldInt(fieldName, sizeof(int));
}
void SQLObject::addFieldDouble(std::string fieldName, double obj){
	sqlFields->addFieldDouble(fieldName, sizeof(double));
}
void SQLObject::addFieldFloat(std::string fieldName, float obj){
	sqlFields->addFieldFloat(fieldName, sizeof(float));
}
void SQLObject::addFieldlong(std::string fieldName, long obj){
	sqlFields->addFieldlong(fieldName, sizeof(long));
}
void SQLObject::addFieldlonglong(std::string fieldName, long long obj){

	sqlFields->addFieldlonglong(fieldName, sizeof(long long));
}
void SQLObject::addFieldlongDouble(std::string fieldName, long double obj) {
	sqlFields->addFieldlongDouble(fieldName, sizeof(long double));
}

SQLObject::SQLObject(std::string tableName) {
	this->TableName = tableName;
	if (this->sqlFields == NULL)
	{
		this->sqlFields = new	SQLFields();
	}
}