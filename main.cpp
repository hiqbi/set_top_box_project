//
// main.cpp
// Created on 21/10/2018
//

#include "Multimedia.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include <iostream>
#include <string>

using namespace std ;


int main(){

    // Après polymorphisme, on ne peut plus instancer des objeys de la classe de base Multimedia, car elle devient une classe abstraite
    //Multimedia *m = new Multimedia("m", "Random file") ;
    //m->print(cout) ;

    //Etape 4
    cout << endl << "#----- Etape 4 : Les classes Photo et Video -----#" << endl ;

    Video * video = new Video("video", "video file", 5) ;
    video->print(cout) ;

    Photo * photo = new Photo("photo", "photo file", 720, 1080) ;
    photo->print(cout) ;


    //Etape 5 :
    cout << endl << "#----- Etape 5 : Polymorphisme -----#" << endl ;

    auto ** multimedia = new Multimedia * [2] ;
    unsigned int count = 0 ;
    multimedia[count++] = new Photo("photo", "photo file", 720, 1080) ;
    multimedia[count++] = new Video("video", "video file", 5.4) ;

    for (unsigned int k = 0 ; k < count ; ++k) {
        multimedia[k]->print(cout) ;
    }

    //Etape 6
    cout << endl << "#----- Etape 6 : La classe Film -----#" << endl ;

    Film * film1 = new Film("film1", "film1 file", 10, 4, new int[4]{2, 3, 1, 4}) ;
    film1->print(cout) ;

    //Etape 7
    cout << endl << "#----- etape 7 : Destruction et copie des objets -----#" << endl ;

    Film film2 ;
    film2 = *film1 ;
    film2.print(cout) ;
    delete film1 ;
    film2.print(cout) ;
    cout << "La copie film2 rest inchangée et garde les même valeurs de ses attributs."

    return 0 ;
}
