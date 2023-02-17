#include "Filter.h"
Filter::Filter(SQLField* ptr, const Expression what, const bool value) {
	field = ptr;
	this->what = what;
	if (sizeof(value)!= field->size)
	{
		data = new char[sizeof(value)];
	}
	else {
		data = new char[field->size];
	}
	
		;
	memcpy_s(data, field->size, &value, field->size);
}
Filter::Filter(SQLField* ptr, const Expression what, const int value) {
	field = ptr;this->what = what;
	
	if (sizeof(value) != field->size)
	{
		data = new char[sizeof(value)];
	}
	else {
		data = new char[field->size];
	}
	memcpy_s(data, field->size, &value, field->size);
}
Filter::Filter(SQLField* ptr, const Expression what, const long value) {
	field = ptr;this->what = what;
	if (sizeof(value) != field->size)
	{
		data = new char[sizeof(value)];
	}
	else {
		data = new char[field->size];
	}
	memcpy_s(data, field->size, &value, field->size);
}
Filter::Filter(SQLField* ptr, const Expression what, const double value) {
	field = ptr;this->what = what;
	if (sizeof(value) != field->size)
	{
		data = new char[sizeof(value)];
	}
	else {
		data = new char[field->size];
	}
	memcpy_s(data, field->size, &value, field->size);
}
Filter::Filter(SQLField* ptr, const Expression what, const float value) {
	field = ptr;this->what = what;
	if (sizeof(value) != field->size)
	{
		data = new char[sizeof(value)];
	}
	else {
		data = new char[field->size];
	}
	memcpy_s(data, field->size, &value, field->size);
}
Filter::Filter(SQLField* ptr, const Expression what, const long long value) {
	field = ptr;this->what = what;
	if (sizeof(value) != field->size)
	{
		data = new char[sizeof(value)];
	}
	else {
		data = new char[field->size];
	}
	memcpy_s(data, field->size, &value, field->size);
}
Filter::Filter(SQLField* ptr, const Expression what, const long double value) {
	field = ptr;this->what = what;
	if (sizeof(value) != field->size)
	{
		data = new char[sizeof(value)];
	}
	else {
		data = new char[field->size];
	}
	memcpy_s(data, field->size, &value, field->size);
}
Filter::Filter(SQLField* ptr, const Expression what, const char* value) {
	field = ptr;this->what = what;
	if (sizeof(value) != field->size)
	{
		data = new char[sizeof(value)];
	}
	else {
		data = new char[field->size];
	}
	memcpy_s(data, field->size, &value, field->size);

}

Filter::~Filter()
{
}
string Filter::FilterResult()const {
	{
		string whereClause = " ";
		whereClause.append(field->fieldName);
		switch (this->what)
		{
		case _bigger_:
			whereClause.append(">");
			break;
		case _smaller:
			whereClause.append("<");
			break;
		case _bigEq:
			whereClause.append(">=");
			break;
		case _smallEq:
			whereClause.append("<=");
			break;
		case _eq:
			whereClause.append("=");
			break;
		default:
			break;
		}
		whereClause.append(SQLFields::BufferValue(field, data));
		delete[field->size] data;
		return whereClause;
	}
}
