#ifndef GROUP_H
#define GROUP_H

#include "Multimedia.h"
#include <list>
#include <memory>

using namespace std ;
typedef std::shared_ptr<Multimedia> ptrMultimedia ;

class Group : public list<ptrMultimedia>
        // Une classe Group qui hérite dd'une liste d'objets
{

private :

    string name{} ;

public :

    ~Group() {cout << "Group object " << name << " destructed successfully !" << endl ;}

    Group() {name = "" ;}
    Group(string name) : name{name}{}

    string getName() const {return name ;}

    void setName(string name_) {name = name_ ;}

    void print(ostream& output) const {
        output << "Group : " << name << endl
               << "Elements : " << endl ;
             for (auto multimedia : *this){
                  output << "++ " ;
                  multimedia->print(output) ;
        }
    }
};
#endif // GROUP_H

