// Tester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SQLFactory.h"
#include "SQLDerived.h"


void castToUnicode(char ptr[], wstring data,char unicodePrefix);
void castUnicodeToWide(char ptr[]);


int main()
{

    SQLFactory factory_("mashu");

    SQLDerived* someTable = new   SQLDerived("a table");
    factory_.RegisterClass(someTable);
    factory_.CreateTable(someTable);
    StructExample st;

    st.age = 223;
    st.year = 1945;
    st.id = 2;
    st.name[0] = 's';
    st.name[1] = '2';
    st.name[2] = '\0';
    castToUnicode(st.name, L"שי היה פה", -41);
    int dataInt = -1;
    


    SQL_order_map<StructExample> data;
    ;
    //
    
    factory_.InsertObject(someTable->Insert(st));

    factory_.GetTable(someTable,data);
    st.year = 1921;
    wchar_t df= L'א';
    df = L'ת';

    int f = 0x5d0;
    f = 0x5ea;
   

 
    std::cout << "Hello World!\n";
}

void castToUnicode(char ptr[], wstring data, char unicodePrefix) {
    vector<int> letters;

    for (size_t i = 0; i < data.size()&& letters .size()<MAX_CHARACTERS; i++)
    {
        int expression = -1 * (1600 - ((int)data.at(i)));
        if (expression<-112)
        {
            letters.push_back((int)data.at(i));
          
        }
        else {
            letters.push_back((int)unicodePrefix);
            letters.push_back(expression);
        }
       
    }
    letters.push_back(0);
  

    char* dynamic = new char[letters.size()];
    for (size_t i = 0; i < letters.size(); i++)
    {
        dynamic[i] = (char)letters.at(i);
    }

    memcpy_s(ptr, MAX_CHARACTERS, dynamic, MAX_CHARACTERS);
    if (ptr[MAX_CHARACTERS - 1] < 0 && ptr[MAX_CHARACTERS - 1] == (int)unicodePrefix)
    {
        ptr[MAX_CHARACTERS - 1] = 0;
    }
    delete[] dynamic;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
