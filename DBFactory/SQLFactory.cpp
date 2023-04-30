#include "SQLFactory.h"
using namespace std;
SQLFactory::SQLFactory(std::string dbpath) {
	
	dbPath = dbpath.append(".db");
	int res = sqlite3_open(dbPath.c_str(), &db);
	data = "Callback function called";
}

void SQLFactory::open() {
	if (db==NULL)
	{
		int res = sqlite3_open(dbPath.c_str(), &db);
		data = "Callback function called";
	}

}
void SQLFactory::close() {
	if (db != NULL)
	{
		sqlite3_close(db);
		db = NULL;
	}

}
void SQLFactory::StringToBuffer(SQLField* ptr, char* buffer, char* value) {
	switch (ptr->type)
	{
	case _int_: {
		int d = stoi(value);
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
SQLFactory_status SQLFactory::InsertObjectUnsafe(const vector<std::string>& Queries) {
	open();
	string query = "BEGIN TRANSACTION;";
	for (size_t i = 0; i < Queries.size(); i++)
	{
		query.append(Queries.at(i));

	}
	query.append(" COMMIT;");
	int rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);

	return (SQLFactory_status)rc;
}
SQLFactory_status SQLFactory::InsertObject(const std::string& Query) {
	open();
	
	
	int rc=  sqlite3_exec(db, Query.c_str(), NULL, 0, &zErrMsg);

	return (SQLFactory_status)rc;
}

SQLFactory_status SQLFactory::InsertObject(const vector<std::string>& Queries) {
	open();
	string query = "";
	for (size_t i = 0; i < Queries.size(); i++)
	{
		query.append(Queries.at(i));
	}

	int rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);

	return (SQLFactory_status)rc;
}

SQLFactory_status SQLFactory::CreateTable(SQLObject* ptr) {
	open();
	std::unordered_map<std::string, SQLField*> fields= ptr->GetFields()->GetFields();
	std::unordered_map<std::string, SQLField*>::iterator fieldsIt;
	map<string, SQLObject*>::iterator it;;
	string sqlCreate = "";
	SQLField* primary = NULL;









	 sqlCreate = "CREATE TABLE IF NOT EXISTS "; 
	sqlCreate.append(ptr->GetName());
	sqlCreate.append(" (");
	for (fieldsIt = fields.begin(); fieldsIt != fields.end(); fieldsIt++)
	{
		sqlCreate.append(fieldsIt->first);
		sqlCreate.append(" ");
		sqlCreate.append(fieldsIt->second->TypeToSql());
		if (fieldsIt->second->primary)
		{
			primary = fieldsIt->second;
		}
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
	//inserting foreign keys according to objects
	


	sqlCreate.append(" );");



	



	







	int rc = sqlite3_exec(db, sqlCreate.c_str(), NULL, 0, &zErrMsg);
	map<string, SQLObject*>::iterator itTable;
	sqlCreate.clear();
	for (itTable = ptr->GetObjects().begin(); itTable != ptr->GetObjects().end(); itTable++)
	{
		sqlCreate = "CREATE TABLE IF NOT EXISTS ";
		sqlCreate.append(itTable->second->GetName());
		sqlCreate.append(" (");
		for (fieldsIt = fields.begin(); fieldsIt != fields.end(); fieldsIt++)
		{
			sqlCreate.append(fieldsIt->first);
			sqlCreate.append(" ");
			sqlCreate.append(fieldsIt->second->TypeToSql());
			fieldsIt++;
			if (fieldsIt == fields.end())
			{
				sqlCreate.append(", ");
				sqlCreate.append(ptr->GetName());
				sqlCreate.append(primary->fieldName);
				sqlCreate.append(" INTEGER");
				break;
			}
			else {
				fieldsIt--;
				sqlCreate.append(" , ");
			}

		}
	}
	sqlCreate.append(" );");
	rc = sqlite3_exec(db, sqlCreate.c_str(), NULL, 0, &zErrMsg);
	return (SQLFactory_status)rc;
}


SQLFactory_status SQLFactory::DropTable(const SQLObject* obj) {
	open();
	string sql = "DROP TABLE ";
	sql.append(obj->GetName());

	return (SQLFactory_status)sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
}



SQLFactory_status SQLFactory::Execute(SQLObject* obj, unordered_map<size_t, char*>& data, size_t& size)
{

	int rows = 0, columns = 0;
	size_t rowIndex = 1;
	char** results = NULL;
	std::unordered_map<std::string, SQLField*>::iterator it;
	std::unordered_map<std::string, SQLField*> map;
	char* buffer = NULL;




	string sql = "SELECT ROWID,* FROM "; //+GetName() + "(column_name datatype, column_name datatype);"
	sql.append(obj->GetName());

	int rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &zErrMsg);
	if (rows < 1 || rc != 0)
	{
		return (SQLFactory_status)rc;
	}

	map = obj->GetFields()->GetFields();

	buffer = new	char[obj->GetFields()->GetBufferSize()];
	size = obj->GetFields()->GetBufferSize();



	size_t i = columns;
	size_t indexLocation = 0;
	size_t row = 0;

	while (i < (rows + 1) * (columns))
	{
		if (i % (columns) == 0)
		{


			row = stoi(results[i]);
			it = map.begin();
			++i;
			continue;
		}
		StringToBuffer(it->second, buffer, results[i]);

		++i;
		++it;
		++indexLocation;
		if (indexLocation >= (columns - 1))
		{
			char* mem = NULL;
			mem = new char[obj->GetFields()->GetBufferSize()];
			memcpy_s(mem, obj->GetFields()->GetBufferSize(), buffer, obj->GetFields()->GetBufferSize());
			delete[obj->GetFields()->GetBufferSize()] buffer;
			buffer = NULL;
			buffer = new	char[obj->GetFields()->GetBufferSize()];
			data[row] = (mem);


			indexLocation = 0;



		}

	}


	for (size_t i = 0; i < (rows + 1) * (columns); i++)
	{
		delete  results[i];
		results[i] = NULL;
	}

	delete[obj->GetFields()->GetBufferSize()]  buffer;

	buffer = NULL;
	results = NULL;

	return (SQLFactory_status)rc;
}

SQLFactory_status SQLFactory::Execute(SQLObject* obj, unordered_map<size_t, char*>& data,size_t& size,const Filter filter) {

	int rows = 0, columns = 0;
	size_t rowIndex = 1;
	char** results = NULL;
	std::unordered_map<std::string, SQLField*>::iterator it;
	std::unordered_map<std::string, SQLField*> map;
	char* buffer = NULL;




	string sql = "SELECT ROWID,* FROM "; //+GetName() + "(column_name datatype, column_name datatype);"
	sql.append(obj->GetName());
	sql.append(" WHERE");
	//sql.append(" ORDER BY id ASC, age DESC;");
	sql.append(filter.FilterResult());
	int rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &zErrMsg);
	if (rows < 1 || rc != 0)
	{
		return (SQLFactory_status)rc;
	}

	map = obj->GetFields()->GetFields();

	buffer = new	char[obj->GetFields()->GetBufferSize()];
	size = obj->GetFields()->GetBufferSize();
	


	size_t i = columns;
	size_t indexLocation = 0;
	size_t row = 0;

	while (i < (rows + 1) * (columns))
	{
		if (i % (columns) == 0)
		{


			row = stoi(results[i]);
			it = map.begin();
			++i;
			continue;
		}
		StringToBuffer(it->second, buffer, results[i]);

		++i;
		++it;
		++indexLocation;
		if (indexLocation >= (columns - 1))
		{
			char* mem = NULL;
			 mem = new char[obj->GetFields()->GetBufferSize()];
			memcpy_s(mem, obj->GetFields()->GetBufferSize(), buffer, obj->GetFields()->GetBufferSize());
			delete[obj->GetFields()->GetBufferSize()] buffer;
			buffer = NULL;
			buffer = new	char[obj->GetFields()->GetBufferSize()];
			data[row] = (mem);


			indexLocation = 0;



		}

	}


	for (size_t i = 0; i < (rows + 1) * (columns); i++)
	{
		delete  results[i];
		results[i] = NULL;
	}

	delete[obj->GetFields()->GetBufferSize()]  buffer;

	buffer = NULL;
	results = NULL;

	return (SQLFactory_status)rc;
}

SQLFactory_status SQLFactory::Execute(SQLObject* obj, unordered_map<size_t, char*>& data, size_t& size, const vector<Filter>& filters) {

	int rows = 0, columns = 0;
	size_t rowIndex = 1;
	char** results = NULL;
	std::unordered_map<std::string, SQLField*>::iterator it;
	std::unordered_map<std::string, SQLField*> map;
	char* buffer = NULL;




	string sql = "SELECT ROWID,* FROM "; //+GetName() + "(column_name datatype, column_name datatype);"
	sql.append(obj->GetName());
	//sql.append(" ORDER BY id ASC, age DESC;");
	sql.append(" WHERE");

	for (size_t i = 0; i < filters.size(); i++)
	{
		sql.append(filters.at(i).FilterResult());

		;
		if (i+1< filters.size())
		{
			sql.append(" AND ");
		}
	}
	int rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &zErrMsg);
	if (rows < 1 || rc != 0)
	{
		return (SQLFactory_status)rc;
	}

	map = obj->GetFields()->GetFields();

	buffer = new	char[obj->GetFields()->GetBufferSize()];
	size = obj->GetFields()->GetBufferSize();



	size_t i = columns;
	size_t indexLocation = 0;
	size_t row = 0;

	while (i < (rows + 1) * (columns))
	{
		if (i % (columns) == 0)
		{


			row = stoi(results[i]);
			it = map.begin();
			++i;
			continue;
		}
		StringToBuffer(it->second, buffer, results[i]);

		++i;
		++it;
		++indexLocation;
		if (indexLocation >= (columns - 1))
		{
			char* mem = NULL;
			mem = new char[obj->GetFields()->GetBufferSize()];
			memcpy_s(mem, obj->GetFields()->GetBufferSize(), buffer, obj->GetFields()->GetBufferSize());
			delete[obj->GetFields()->GetBufferSize()] buffer;
			buffer = NULL;
			buffer = new	char[obj->GetFields()->GetBufferSize()];
			data[row] = (mem);


			indexLocation = 0;



		}

	}


	for (size_t i = 0; i < (rows + 1) * (columns); i++)
	{
		delete  results[i];
		results[i] = NULL;
	}

	delete[obj->GetFields()->GetBufferSize()]  buffer;

	buffer = NULL;
	results = NULL;

	return (SQLFactory_status)rc;
}

