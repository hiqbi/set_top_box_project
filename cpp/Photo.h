#ifndef PHOTO_H
#define PHOTO_H

#include "Multimedia.h"

using namespace std ;

class Photo:public Multimedia {

private :

    int latitude{} ;
    int longitude{} ;

public :

    Photo(string name, string path, int latitude, int longitude) : Multimedia(name, path), latitude{latitude}, longitude{longitude} {}

    void setLatitude(int newLatitude) {latitude = newLatitude ;}
    void setLongitude(int newLongitude) {longitude = newLongitude ;}

    int getLatitude() const {return latitude ;}
    int getLongitude() const {return longitude ;}

    void print(ostream& output) const override {
        output << "Multimedia photo : "
               << endl
               << "-Name : " << this->getName()
               << endl
               << "-Path name : " << this->getPath()
               << endl
               << "-Latitude : " << latitude
               << endl
               << "-Longitude : " << longitude
               << endl ;
    }

    void play() const override {
        string sys = "xdg-open " + this->getPath() + this->getName() + " &" ;
        system(sys.data()) ; //data() : pour retourner un pointeur
    }

};

#endif // PHOTO_H
