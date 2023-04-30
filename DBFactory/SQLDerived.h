#pragma once
#include "SQLObject.h"
#include "StructExample.h"
class SQLDerived :
    public SQLObject
{
    
    void RegisterFields() {
        StructExample* ptr = new     StructExample();
        
        this->addFieldInt("id", ptr->id);
      
        this->addFieldInt("year", ptr->year);

        this->addFieldDouble("age", ptr->age);

        this->addFieldString("the name", 23);

     

    }
public:
    SQLDerived(std::string  name) :SQLObject(name) {
 
        RegisterFields();
    }
};

class SQLDerived2 :
    public SQLObject
{

    void RegisterFields() {
        StructExample2* ptr = new     StructExample2();

        this->addFieldInt("id", ptr->id);
       
        this->addFieldInt("year", ptr->year);
       
    }
public:
    SQLDerived2(std::string  name) :SQLObject(name) {
     
        RegisterFields();
    }
};

