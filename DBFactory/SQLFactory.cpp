#include "SQLFactory.h"
using namespace std;
SQLFactory::SQLFactory(std::string dbpath) {
	
	dbPath = dbpath.append(".db");
	int res = sqlite3_open(dbPath.c_str(), &db);
	data = "Callback function called";
}
	

SQLFactory::~SQLFactory() {
	
}
void SQLFactory::RegisterClass(SQLObject* ptr) {

	registered[ptr->GetName()] = ptr;

}
int SQLFactory::InsertObject(std::string Query) {
	int rc=  sqlite3_exec(db, Query.c_str(), NULL, 0, &zErrMsg);

	return rc;
}

int SQLFactory::CreateTable(SQLObject* ptr) {

	std::map<std::string, SQLField*> fields= ptr->GetFields()->GetFields();
	std::map<std::string, SQLField*>::iterator fieldsIt;
	string sqlCreate = "CREATE TABLE IF NOT EXISTS "; //+GetName() + "(column_name datatype, column_name datatype);"
	sqlCreate.append(ptr->GetName());
	sqlCreate.append(" (");
	for (fieldsIt = fields.begin(); fieldsIt != fields.end(); fieldsIt++)
	{
		sqlCreate.append(fieldsIt->first);
		sqlCreate.append(" ");
		sqlCreate.append(fieldsIt->second->TypeToSql());
		fieldsIt++;
		if (fieldsIt == fields.end())
		{
			break;
		}
		else {
			fieldsIt--;
			sqlCreate.append(" , ");
		}
		
	}
	sqlCreate.append(" );");

	void* Stam;
	int rc = sqlite3_exec(db, sqlCreate.c_str(), NULL, 0, &zErrMsg);
	return rc;
}
