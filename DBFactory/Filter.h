#pragma once
#include "Dependencies.h"
#include "SQLField.h"
#include "SQLFieldBuffer.h"
enum Expression
{
	_bigger_,
	_smaller,
	_bigEq,
	_smallEq,
	_eq
};

class Filter
{
	friend class SQLFactory;

public:
	Filter( SQLField* ptr,const Expression what, const bool value);
	Filter( SQLField* ptr,const Expression what, const int value);
	Filter( SQLField* ptr,const Expression what, const long value);
	Filter( SQLField* ptr,const Expression what, const double value);
	Filter( SQLField* ptr,const Expression what, const float value);
	Filter( SQLField* ptr,const Expression what, const long long value);
	Filter( SQLField* ptr,const Expression what, const long double value);
	Filter( SQLField* ptr,const Expression what,const char* value);

	~Filter();

private:
	const SQLField* field;
	 Expression what;
	 char* data;
	 string FilterResult()const;
	
};

