/*
 * Child.h
 * Child's class.
*/

#ifndef Child_h
#define Child_h
#include <string>
#include <iostream>
using namespace std;
#include <stdio.h>

class Child {
public:
Child();
Child(Child &c);
Child(string firstName, string lastName, int age);
~Child();
    string getFirstName() const;
    string getLastName() const;
    int getAge() const;
    
    bool operator<(const Child &c) const;
    bool operator>(const Child &c) const;
    bool operator==(const Child &c) const;
    bool operator!=(const Child &c) const;
    Child operator=(const Child &c);
    
    friend ostream& operator<<(ostream &out, const Child &c);
    friend istream& operator>>(istream& in_stream, Child &c);
    
private:
    string first_, last_;
    int age_;
#endif /* Child_h */
};
