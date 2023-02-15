// TestStructBufferAlloc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <set>
#include <map>
#include "SQLFieldBuffer.h"
#include "SQLDerived.h"
#include "SQLFactory.h"
using namespace std;





int main()
{
  
    SQLFactory factory("thisisfactory");
  
   
    
    
    SQLDerived* t = new    SQLDerived("tableName");
    factory.RegisterClass(t);
    // 
    factory.CreateTable(t);

    StructExample tempo;
    tempo.age = 22.32;
    tempo.id = 2211;
    tempo.year = 1994;
    memcpy_s(tempo.name, 23, "mash", 23);


    

    cout << factory.InsertObject(t->ToSQLInsert(tempo));

    map<size_t,StructExample> data;
    factory.GetTable( t,data);

    map<size_t, StructExample>::iterator  datad= data.end();
    datad--;
    datad->second.age = 123;
    cout<<factory.InsertObject(t->ToSQLUpdate(datad->second, datad->first));


   

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
