#include "Multimedia.h"

using namespace std ;

Multimedia::Multimedia() = default;

Multimedia::Multimedia(string name, string fileName){
    setName(name) ;
    setFileName(fileName) ;
}

void Multimedia::setName(string newName){
    Multimedia::name = newName ;
}

void Multimedia::setFileName(string newFileName){
    Multimedia::fileName = newFileName ;
}

string Multimedia::getName() const {
    return name ;
}

string Multimedia::getFileName() const {
    return fileName ;
}

void Multimedia::print(ostream& output) const {
    output << "file name : " << fileName
           << endl
           << "name : " << name
           << endl;
}
