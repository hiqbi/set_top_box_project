#ifndef FILM_H
#define FILM_H

#include "Multimedia.h"
#include "Video.h"

using namespace std ;

class Film:public Video
        // Un tableau ne permet pas d'accéder à sa taille --> c'est préférable d'utiliser std::vector si l'on n'a pas de contraintes de performance/mémoire
        // La taille du tableau est déterminée dès sa définition et dépend du type de données qu'il stock
{

private :

    int chaptersNumber{} ;
    int * chapters ;

public :

    virtual ~Film() {
        delete[] chapters ;
        cout << this->getName() << " was deleted successfully" << endl ;
    }

    Film() : Video() {
        chaptersNumber = 0 ;
        chapters = nullptr ;
    }

    //Un tableau est passé en argument : on ne peut pas le copié dans un attribut d'instance comme un type de base

    Film(string name, string path, float length, int chaptersNumber, const int * chapters) : Video(name, path, length) {
        this->chaptersNumber = chaptersNumber ;
        this->chapters = new int[chaptersNumber] ;
        for (int i = 0 ; i < chaptersNumber ; i++) {
            this->chapters[i] = chapters[i] ;
        }
    }

    Film(string name, string path, float length) : Video(name, path, length) {
        chaptersNumber = 0 ;
        chapters = nullptr ;
    }

    void setChapters(const int * chapters_, int chaptersNumber_) {
        this->chaptersNumber = chaptersNumber_ ;
        delete[] chapters ; // delete est utilisée car chapters est toujours soit créé par new ou vaut le pointeur nul
        this->chapters = new int[chaptersNumber] ;
        for (int i = 0 ; i < chaptersNumber ; i++){
            this->chapters[i] = chapters_[i] ;
        }
    }

    int * getChapters() const{return chapters ;}
    int getChaptersNumber() const {return chaptersNumber ;}

    void print(ostream& output) const override {
        Video::print(output) ;
        output << "This is a film, and the length of its chapters is : "
               << endl ;
        for (int i = 0 ; i < chaptersNumber ; ++i) {
            output << "-Chapter " << i << " has length " << chapters[i] << endl ;
        }
    }
};

#endif // FILM_H
