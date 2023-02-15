#include "StructReader.h"
StructReader::StructReader(wstring path) {
	ifstream MyReadFile(path);
	string myText;
	std::ostringstream buffer;

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(MyReadFile, myText)) {
		// Output the text from the file
		buffer << myText;
	}
	cout<<buffer.str();
	vector<string> structs_;
	string currentBuffer = buffer.str();
	string tempStruct_;
	bool record = false;
	map<string, Property>fields;
	for (size_t i = 0; i < currentBuffer.size(); i++)
	{

		if (record)
		{
			if (currentBuffer[i]=='{')
			{
				++i;
				collectPrimitives(fields, i, currentBuffer.size(), currentBuffer);
			}
			tempStruct_ += currentBuffer[i];
		}

		if (currentBuffer[i]=='s'&&
			currentBuffer[i+1] == 't' &&
			currentBuffer[i+2] == 'r' &&
			currentBuffer[i+3] == 'u' &&
			currentBuffer[i+4] == 'c' &&
			currentBuffer[i+5] == 't')
		{
			record = true;
			i += 6;
		}
	}


	
}
void StructReader::CollectProperties(vector<Property>& elements, vector<string>strings_) {

	string tempo = "";
	vector<string> finalResults;
	for (size_t i = 0; i < strings_.size(); i++)
	{
		const string temp = strings_.at(i);
		for (size_t j = 0; j < temp.length(); j++)
		{
			if (temp[j]=='\t'|| temp[j] == '\b'
				|| temp[j] == '\n' || temp[j] == ','
				|| temp[j] == ' ')
			{
				
				continue;
			}
			tempo += temp[j];

		}
		if (tempo.length()>0)
		{
			finalResults.push_back(tempo);
		}
		
		tempo = "";
	}

	//figure out what is the type
	bool Is_Int= strcmp(finalResults.at(0).c_str(), _INT_.c_str()) == 0;
	bool Is_CHAR = strcmp(finalResults.at(0).c_str(), _CHAR_.c_str()) == 0;
	bool Is_Double = strcmp(finalResults.at(0).c_str(), _DOUBLE_.c_str()) == 0;
	Primitives tempPrimitive=Primitives::_undefined_;
	if (Is_CHAR)
	{
		tempPrimitive = Primitives::_char_;
	}
	if (Is_Int)
	{
		tempPrimitive = Primitives::_int_;
	}
	if (Is_Double)
	{
		tempPrimitive = Primitives::_double_;
	}
	bool recordSize = false;
	string Size_ = "";
	size_t size = 0;
	int nameStop = 0;
	for (size_t i = 1; i < finalResults.size(); i++)
	{
		const string result = finalResults.at(i);
		Property p(tempPrimitive, result, size);
		for (size_t j = 0; j < result.length(); j++)
		{
			if (recordSize)
			{
				Size_ += result[j];
			}

			if (result[j]=='[')
			{
				recordSize = true;
				nameStop = j;
			}
			if (result[j] == ']')
			{
				recordSize = false;
				size = stoi(Size_);
				Size_ = "";
				p.SetSize(size);
				string newName = "";
				for (size_t k = 0; k < nameStop; k++)
				{
					newName += result[k];
				}
				
				p.SetName(newName);
			}
		}

		elements.push_back(p);
	}




}
void StructReader::ParseProperties(vector<string>elements, map<string, Property>&map) {
	//iterate each string and get the number of properties and the type;

	Primitives temp = Primitives::_undefined_;
	vector<string> splittedRow;
	vector<Property> properties;
	string val="";
	for (size_t i = 0; i < elements.size(); i++)
	{
		const string CurrentValue = elements.at(i);

		for (size_t j = 0; j < CurrentValue.length(); j++)
		{
			if (CurrentValue[j] == ';')
			{
				splittedRow.push_back(val);
				CollectProperties(properties, splittedRow);
				splittedRow.clear();
				val = "";
				break;
			}
			if (CurrentValue[j]==' ')
			{
				splittedRow.push_back(val);
				val = "";
			}


			val += CurrentValue[j];
		}

		
	}


}
void StructReader::collectPrimitives(map<string, Property>& map,size_t Current,int last,string buffer) {

	string CurrentValue = "";
	vector<string> properties;
	for (size_t i = Current; i < last; i++)
	{
		CurrentValue += buffer[i];

		//more than one property with same type
		
		if (buffer[i] == ';')
		{
			//need to parse to values
			properties.push_back(CurrentValue);
			CurrentValue = "";
		}

	}
	ParseProperties(properties, map);
}

Primitives StructReader::StringToPrimitive(string data) {
	return Primitives::_charPtr_;
}
Property::Property(Primitives type, string name,size_t size)
{
	this->size = size;

	this->name = name;
	if (size>0)
	{
		this->type = (Primitives)(type + 12);
	}
	else {
		this->type = type;
	}
	

}

Property::~Property()
{
}
void Property::SetSize(size_t size) {
	this->size = size;
	if (size > 0)
	{
		this->type = (Primitives)(type + 12);
	}
	else {
		this->type = type;
	}
}
void Property::SetName(string name) {
	this->name = name;
	
}