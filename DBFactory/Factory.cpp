#include "Factory.h"

SQLFactory::SQLFactory(string dbpath)
{
	dbPath = dbpath.append(".db");
	int res = sqlite3_open(dbPath.c_str(), &db);
	data = "Callback function called";

}

SQLFactory::~SQLFactory()
{
}
void SQLFactory::updateData( GenericSQLClass* class_)
{
	char* sql= class_->updateData();
	int rc = sqlite3_exec(db, sql, (int(*)(void*, int, char**, char**)) callBacks[class_->type], 0, &zErrMsg);
}


string SQLFactory::GetClassName(GenericSQLClass* class_) {
	return class_->GetName();
}
void SQLFactory::registerStruct(StructsDefined type, GenericSQLClass* class_,string datamembers[],int size) {

	map[type] = class_;
	class_->type = type;
	createTable( type);
	
}

void SQLFactory::createTable(StructsDefined type) {
	char* sql = map[type]->CreateTable();
	int rc = sqlite3_exec(db, sql, (int(*)(void*, int, char**, char**)) callBacks[type], 0, &zErrMsg);

	;
}
void SQLFactory::insert( GenericSQLClass* t) {

	char* sql = map[t->type]->InsertData(t);
	int rc = sqlite3_exec(db, sql, (int(*)(void*, int, char**, char**)) callBacks[t->type], 0, &zErrMsg);

	delete t;
}


