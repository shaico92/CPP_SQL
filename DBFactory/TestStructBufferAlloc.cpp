// TestStructBufferAlloc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Dependencies.h"
#include "SQLFieldBuffer.h"
#include "SQLDerived.h"

#include "SQLFactory.h"
//using namespace std;
//
//
//
//void InsertData(int howMuch, SQLFactory& factory, SQLObject* t);
//
//int main()
//{
//  
//    SQLFactory factory("thisisfactory");
//  
//   
//    
//    
//    SQLDerived* t = new    SQLDerived("tableName");
//    factory.RegisterClass(t);
//    factory.DropTable(t);
//    // 
//    factory.CreateTable(t);
//    SQLField* field;
//    //t->GetField("year",field);
//
//    SQL_order_map<StructExample> data;
//  //  factory.GetTable(t, data);
//   // SQL_order_map<StructExample>::iterator  data1 = data.begin();
//   // data1->second.id = -666;
//   // cout << factory.InsertObject(t->ToSQLUpdate(data1->second, data1->first));
//   
//    InsertData(20, factory, t);
//
//
//    
//
//    //cout << factory.InsertObject(t->ToSQLInsert(tempo));
//
//    SQL_order_map<StructExample>::iterator  OBJECT;
//
//    Filter filter(field, Expression::_bigEq, 2002);
//    Filter filter2(field, Expression::_smallEq, 2016);
//    vector<Filter> filters;
//    filters.push_back(filter);
//    filters.push_back(filter2);
//    for (size_t i = 0; i < 200; i++)
//    {
//        factory.GetTable(t, data, filters);
//    }
//
//
//    //OBJECT=data.find(7);
//    //OBJECT->second.age = -666;
//    //OBJECT->second.id = -666;
//    vector <pair< size_t,StructExample >>vec;
//    //auto p = make_pair(7, data.find(8)->second);
//    //vec.push_back(p);
//    //p = make_pair(8, data.find(9)->second);
//    //vec.push_back(p);
//    //
//    cout << factory.InsertObject(t->UpdateRange(vec));
//    //cout<<factory.InsertObject(t->Update(OBJECT->second, OBJECT->first));
//
//    //factory.GetTable(t, data);
//   
//
//}
//
//// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
//// Debug program: F5 or Debug > Start Debugging menu
//
//// Tips for Getting Started: 
////   1. Use the Solution Explorer window to add/manage files
////   2. Use the Team Explorer window to connect to source control
////   3. Use the Output window to see build output and other messages
////   4. Use the Error List window to view errors
////   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
////   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
//void InsertData(int howMuch, SQLFactory& factory, SQLObject* t) {
//    StructExample tempo;
//    vector<StructExample> tempos;
//    for (size_t i = 0; i < howMuch; i++)
//    {
//        tempo.age = 22.32 + 0.1321 - i;
//        tempo.id = i;
//        tempo.year = 1994 + i;
//        memcpy_s(tempo.name, 23, "mash", 23);
//        tempos.push_back(tempo);
//        
//    }
//    cout << factory.InsertObject(t->Insert(tempos));
//}