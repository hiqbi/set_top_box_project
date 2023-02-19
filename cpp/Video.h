#ifndef VIDEO_H
#define VIDEO_H

#include "Multimedia.h"

using namespace std ;

class Video : public Multimedia {

private :

    float length{} ;

public :


    Video() : Multimedia() {length = 0 ;}
    Video(string name, string path, float length) : Multimedia(name, path), length{length} {}

    void setLength(float newLength) {length = newLength ;}

    int getLength() const {return length ;}

    void print(ostream& output) const override {
        output << "Multimedia video : "
               << endl
               << "-Name : " << this->getName()
               << endl
               << "-Path name : " << this->getPath()
               << endl
               << "-Length : " << length
               << endl ;
    }

    void play() const override {
        string sys = "mpv " + this->getPath() + this->getName() + " &" ;
        system(sys.data()) ; //data() : pour retourner un pointeur
    }
};

#endif // VIDEO_H
