#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <string>
#include <iostream>

using namespace std ;

class Multimedia
        //La classe est abstraite car elle a des méthodes abstraites
{
private :
    string name{} ;
    string path{} ;

public:

    Multimedia() ;
    Multimedia(string name, string path) ;

    virtual ~Multimedia() ;

    void setName(string newName) ;
    void setPath(string newPath) ;

    string getName() const ;
    string getPath() const ;

    virtual void print(ostream& output) const = 0 ; //méthode abstraite car son implémentation dépend du type du multimedia

    virtual void play() const = 0 ;
};


#endif //MULTIMEDIA_H
