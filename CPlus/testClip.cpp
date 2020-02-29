
#include <iostream>
#include <string>
using namespace std;
 
class Pet{
    string pname;
public:
    Pet(const string& name) : pname(name) {}
    virtual string name() const {return pname;}
    virtual string description() const{return "This is "+pname;}
};
 
class Dog : public Pet{
    string favoriteActivity;
public:
    Dog(const string& name, const string& activity) : Pet(name), favoriteActivity(activity) {}
    virtual string description() const {return Pet::name() + " like to " + favoriteActivity;}
};
 
void describe(Pet p)
{
    cout<<p.description()<<endl;
}

void describe1(Pet *p)
{
    cout<<p->description()<<endl;
}
 
int main()
{
    Pet p("Alfred");
    Dog d("Fluffy", "sleep");
    describe(p);
    describe(d);

    describe1(&p);
    describe1(&d);
    return 0;
}