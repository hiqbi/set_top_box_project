#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <string>
#include <iostream>

using namespace std ;

class Multimedia
{
private :
    string name{} ;
    string fileName{} ;

public:

    Multimedia() ;
    Multimedia(string name, string fileName) ;

    virtual ~Multimedia() ;

    void setName(string newName) ;
    void setFileName(string newFileName) ;

    string getName() const ;
    string getFileName() const ;

    virtual void print(ostream& output) const ;
};


#endif //MULTIMEDIA_H
