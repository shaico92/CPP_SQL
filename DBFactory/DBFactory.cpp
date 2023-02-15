// DBFactory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Factory.h"



int main()
{
	SQLFactory sqlfactory("stam");

	
	auto type = new TypeOfGeneric2("typeGeneric2");
	sqlfactory.registerStruct(StructsDefined::cl1, new TypeOfGeneric2("typeGeneric2"));
	
	sqlfactory.registerStructCallback(StructsDefined::cl1, callback1);
	sqlfactory.registerStructCallback(StructsDefined::cl1, callback2);
	type->setValues(13, 15);
	
	sqlfactory.insert(StructsDefined::cl1, type);
	sqlfactory.getAllData(StructsDefined::cl1);


}


