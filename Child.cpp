/*
 * Child.cpp
 * Implementation of the child class, overloads: <, >, ==, !=, =, >>, <<.
*/

#include <string>
#include "Child.h"

Child::Child(){
    first_ = "";
    last_ = "";
    age_ = 0;
}

Child::Child(Child &c){
    first_ = c.first_;
    last_ = c.last_;
    age_ = c.age_;
}

Child::Child(string firstName, string lastName, int age){
    first_ = firstName;
    last_ = lastName;
    age_ = age;
}

Child::~Child(){}

string Child::getFirstName() const{
    return first_;
}

string Child::getLastName() const{
    return last_;
}

int Child::getAge() const{
    return age_;
}
    
bool Child::operator<(const Child &c) const{
    if(last_ < c.last_)
        return true;
   else if(first_ < c.first_ && last_ == c.last_)
        return true;
   else if(age_ < c.age_ && last_ == c.last_ && first_ == c.first_)
        return true;
    else
        return false;
}

bool Child::operator>(const Child &c) const{
    if(last_ > c.last_)
        return true;
    else if(first_ > c.first_ && last_ == c.last_)
        return true;
    else if(age_ > c.age_ && last_ == c.last_ && first_ == c.first_)
        return true;
    else
        return false;
}

bool Child::operator==(const Child &c) const{
    return(last_ == c.last_ && first_ == c.first_ && age_ == c.age_);
}

bool Child::operator!=(const Child &c) const{
    return !(*this == c);
}

Child Child::operator=(const Child &c){
    this->first_ = c.first_;
    this->last_ = c.last_;
    this->age_ = c.age_;
    return *this;
}

istream& operator>>(istream& in_stream, Child &c)
{
    in_stream >> c.first_ >> c.last_ >> c.age_;
    return in_stream;
}
    
ostream& operator<<(ostream &out, const Child &c){
    out << c.getFirstName() << c.getLastName() << c.getAge();
    return out;
}
