#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <string>
#include <iostream>

using namespace std ;

class Multimedia
{
    string name{}, fileName{} ;

public:
    virtual ~Multimedia(){cerr << "Destruction of " << name << "\n" ;} ;

    Multimedia();
    Multimedia(string name, string fileName) ;

    void setName(string newName) ;
    void setFileName(string newFileName) ;

    string getName() const ;
    string getFileName() const ;

    virtual void print(ostream& output) const = 0;
};


#endif //MULTIMEDIA_H
