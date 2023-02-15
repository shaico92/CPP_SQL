#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "Primitives.h"
using namespace std;



class Property
{
public:
	Property(Primitives type,string name,size_t size);
	~Property();
	void SetSize(size_t size);
	void SetName(string name);

private:
	string name;
	Primitives type;
	size_t size;
};
class Structs_ {

	map<string, Property> properties;
};


class StructReader
{

private: 
	map<string, Structs_> structs_s;
	void collectPrimitives(map<string, Property>& map, size_t Current, int last, string buffer);

	Primitives StringToPrimitive(string data);
	void ParseProperties(vector<string>elements, map<string, Property>& map);

	void CollectProperties(vector<Property>& elements, vector<string>strings_);

public:
	StructReader(wstring path);


};

