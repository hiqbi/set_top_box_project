#include "Multimedia.h"
#include <iostream>
#include <string>

using namespace std ;

Multimedia::Multimedia(){
    name = "" ;
    path = "" ;
}

Multimedia::Multimedia(string name, string path){
    this->name = name ;
    this->path = path ;
}

void Multimedia::setName(string newName){
    name = newName ;
}

void Multimedia::setPath(string newPath){
    path = newPath ;
}

string Multimedia::getName() const {
    return name ;
}

string Multimedia::getPath() const {
    return path ;
}

void Multimedia::print(ostream& output) const {
    output << "Multimedia : "
           << endl
           << "Path name : " << path
           << endl
           << "name : " << name
           << endl;
}

Multimedia::~Multimedia() {
    cout << "Multimedia instance " << name << " destroyed." << endl
         << "Mission accomplished !" << endl ;
}
