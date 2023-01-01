#include "Multimedia.h"
#include <iostream>
#include <string>

using namespace std ;

Multimedia::Multimedia(){
    this->name = "" ;
    this->fileName = "" ;
}

Multimedia::Multimedia(string name, string fileName){
    this->name = name ;
    this->fileName = fileName ;
}

void Multimedia::setName(string newName){
    this->name = newName ;
}

void Multimedia::setFileName(string newFileName){
    this->fileName = newFileName ;
}

string Multimedia::getName() const {
    return this->name ;
}

string Multimedia::getFileName() const {
    return this->fileName ;
}

void Multimedia::print(ostream& output) const {
    output << "file name : " << this->fileName
           << endl
           << "name : " << this->name
           << endl;
}

Multimedia::~Multimedia() {
    cout << "Multimedia instance " << this->name << " destroyed." << endl
         << "Mission accomplished !" << endl ;
}
