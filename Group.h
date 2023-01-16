#ifndef GROUP_H
#define GROUP_H

#include "Multimedia.h"
#include <list>
#include <memory>

using namespace std ;
typedef std::shared_ptr<Multimedia> ptrMultimedia ;

class Group : public list<ptrMultimedia>
{

private :

    string name{} ;

public :

    ~Group() {cout << "Group object " << name << " destructed successfully !" << endl ;}

    Group() {name = "" ;}
    Group(string name) : name{name}{}

    string getName() const {return name ;}

    void setName(string name_) {name = name_ ;}
};
#endif // GROUP_H
