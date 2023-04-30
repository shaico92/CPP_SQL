// Tester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SQLFactory.h"
#include "SQLDerived.h"
#include "Language.h"





int main(int argc, char** argv)
{

    





    SQLFactory_status status;

    SQLFactory factory_("mashu");

    SQLDerived* someTable = new   SQLDerived("a table");


    SQLDerived2* someTable2 = new   SQLDerived2("a table2");
    factory_.RegisterClass(someTable2);

    status = factory_.CreateTable(someTable2);
    status = factory_.CreateTable(someTable);














    factory_.DropTable(someTable);
    factory_.RegisterClass(someTable);
    status = factory_.CreateTable(someTable);
    int iterations = 10;
    if (argc>1)
    {
        iterations = stoi(argv[1]);
        cout << "Number of iterations is "<< iterations << endl;

       
    }

  
    StructExample st;
    st.age = 2;
    st.year = 1945;
    st.id = 2;
    SQL_order_map<StructExample> data;
    vector<StructExample> data2;
    for (size_t i = 0; i < iterations; i++)
    {
        
        st.age *= (double)i;
        st.year *= (int)i;
        st.id *= (int)i;
        wstring word = L"שלום ";
        
        word.append(to_wstring(i));
        Language::castToUnicode(st.name, word, 23);
        data2.push_back(st);
    }
    //5493
    status = factory_.GetTable(someTable, data);
    SQL_order_map<StructExample>::iterator dataIT;
    Language::castToUnicode(data[5493].name, L"שלאלתאםפ", 23);
    //someTable->Update(data.find(5493));
   
    //status = factory_.InsertObject(someTable->Update(data.find(5493)));
  
    cout << "before " << endl;
    status = factory_.InsertObjectUnsafe(someTable->Insert(data2));
    cout << "Done: " << status << endl;
    status = factory_.GetTable(someTable, data);
    vector<pair<size_t, StructExample>>range;
    range.push_back(make_pair(5493, data[5493]));
    range.push_back(make_pair(1, data[1]));
    range.push_back(make_pair(2, data[2]));
    range.push_back(make_pair(3, data[3]));
    range.push_back(make_pair(12, data[67]));

    status = factory_.InsertObject(someTable->Update(range));

    return 0;
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
