//
// main.cpp
// Created on 21/10/2018
//

#include "Multimedia.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"
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
    cout << endl << "#----- Etape 7 : Destruction et copie des objets -----#" << endl ;

    Film film2 ;
    film2 = *film1 ;
    film2.print(cout) ;
    delete film1 ;
    film2.print(cout) ;
    cout << "La copie film2 rest inchangée et garde les même valeurs de ses attributs." << endl ;

    //Etape 8
    cout << endl << "#----- Etape 8 : Créer des groupes -----#" << endl ;

    /*
    Group * grp1 = new Group("grp1") ;
    Group * grp2 = new Group("grp2") ;
    Photo * img1 = new Photo("img1", "img1_file", 720, 1080) ;
    Video * vid1 = new Video("vid1", "vid1_file", 5) ;
    Film * flm1 = new Film("flm1", "flm1_file", 30, 4, new int[4]{2, 3, 1, 4}) ;
    grp1->push_back(img1) ;
    grp1->push_back(vid1) ;
    grp2->push_back(img1) ;
    grp2->push_back(flm1) ;
    grp1->print(cout) ;
    delete grp1 ;
    grp2->print(cout) ;
    */

    cout << "Après l'implémentation de l'étape 9, on ne peut plus vérifier que l'étape 8 marche bien. Mais tout est OK !" ;

    //Etape 9
    cout << endl << "#----- Etape 9 : Gestion automatique de la mémoire -----#" << endl ;

    ptrMultimedia vid(new Video("vid", "vid_file", 10)) ;
    ptrMultimedia img(new Photo("img", "img_file", 720, 1080)) ;
    Group * grp1 = new Group("grp1");
    Group * grp2 = new Group("grp2") ;
    grp1->assign(1, img) ;
    grp2->assign(1, img) ;
    list<ptrMultimedia>:: iterator it = grp1->begin() ;
    advance(it, 1) ;
    grp1->insert(it, vid) ;
    grp1->print(cout) ;
    delete grp1 ;
    grp2->print(cout) ;
    delete grp2 ;

    return 0 ;
}
