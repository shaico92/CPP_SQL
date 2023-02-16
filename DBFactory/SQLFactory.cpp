#include "SQLFactory.h"
using namespace std;
SQLFactory::SQLFactory(std::string dbpath) {
	
	dbPath = dbpath.append(".db");
	int res = sqlite3_open(dbPath.c_str(), &db);
	data = "Callback function called";
}


void SQLFactory::StringToBuffer(SQLField* ptr, char* buffer, char* value) {
	switch (ptr->type)
	{
	case _int_: {
		int d = stod(value);
		memcpy_s(buffer + ptr->bufferOffeset, ptr->size, &d, ptr->size);

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

SQLFactory::~SQLFactory() {
	
}
void SQLFactory::RegisterClass(SQLObject* ptr) {

	registered[ptr->GetName()] = ptr;

}
int SQLFactory::InsertObject(const std::string& Query) {
	int rc=  sqlite3_exec(db, Query.c_str(), NULL, 0, &zErrMsg);

	return rc;
}
int SQLFactory::InsertObject(const vector<std::string>& Queries) {
	string query = "";
	for (size_t i = 0; i < Queries.size(); i++)
	{
		query.append(Queries.at(i));
	}
	int rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);

	return rc;
}

int SQLFactory::CreateTable(SQLObject* ptr) {

	std::unordered_map<std::string, SQLField*> fields= ptr->GetFields()->GetFields();
	std::unordered_map<std::string, SQLField*>::iterator fieldsIt;
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


int SQLFactory::DropTable(const SQLObject* obj) {
	string sql = "DROP TABLE ";
	sql.append(obj->GetName());

	return sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
}
int SQLFactory::Execute(SQLObject* obj
	, int& rows
	, int& columns
	, char**& res
	, char*& buffer
	, std::unordered_map<std::string, SQLField*>::iterator& it
	, std::unordered_map<std::string, SQLField*>& map) {
	
	size_t rowIndex = 1;
	
	string sql = "SELECT ROWID,* FROM "; //+GetName() + "(column_name datatype, column_name datatype);"
	sql.append(obj->GetName());
	//sql.append(" ORDER BY id ASC, age DESC;");
	int rc = sqlite3_get_table(db, sql.c_str(), &res, &rows, &columns, &zErrMsg);
	if (rows < 1 || rc != 0)
	{
		return 0;
	}
	
	 map = obj->GetFields()->GetFields();

	buffer = new	char[obj->GetFields()->GetBufferSize()];
	
	
	it = map.begin();
	



	return rc;
}