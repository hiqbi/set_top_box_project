#ifndef MAPPING_H
#define MAPPING_H

#include "Group.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include <iostream>
#include <map>

using namespace std ;
typedef shared_ptr<Group> ptrGroup ;

class Mapping{

private :

    map<string, ptrMultimedia> allMultimedia{} ;
    map<string, ptrGroup> allGroups{} ;

public :

    shared_ptr<Photo> createPhoto(string name, string fileName, int latitude, int longitude) {
        shared_ptr<Photo> photo(new Photo(name, fileName, latitude, longitude)) ;
        allMultimedia.insert(pair<string, ptrMultimedia>(name, photo)) ;
        return photo ;
    }

    shared_ptr<Video> createVideo(string name, string fileName, float length) {
        shared_ptr<Video> video(new Video(name, fileName, length)) ;
        allMultimedia.insert(pair<string, ptrMultimedia>(name, video)) ;
        return video ;
    }

    shared_ptr<Film> createFilm(string name, string fileName, float length, int chaptersNumber, int * chapters) {
        shared_ptr<Film> film(new Film(name, fileName, length, chaptersNumber, chapters)) ;
        allMultimedia.insert(pair<string, ptrMultimedia>(name, film)) ;
        return film ;
    }

    ptrGroup createGroup(string name) {
        ptrGroup group(new Group(name)) ;
        allGroups.insert(pair<string, ptrGroup>(name, group)) ;
        return group ;
    }

    ptrMultimedia findMultimedia(string toFind) const {
        auto it = allMultimedia.find(toFind) ;
        if (it != allMultimedia.end()) {
            return it->second ;
        } else {
            cout << "The multimedia object " << toFind << " was not found !" << endl ;
            return nullptr ;
        }
    }

    ptrGroup findGroup(string toFind) const {
        auto it = allGroups.find(toFind) ;
        if (it != allGroups.end()) {
            return it->second ;
        } else {
            cout << "The group " << toFind << " was not found !" << endl ;
            return nullptr ;
        }
    }

    void printMultimedia(string toPrint, ostream & output) const {
        ptrMultimedia found = this->findMultimedia(toPrint) ;
        if (found != nullptr) found->print(output) ;
        else output << "Nothing to print !" ;
    }

    void printGroup(string toPrint, ostream & output) const {
        ptrGroup found = this->findGroup(toPrint) ;
        if (found != nullptr) found->print(output) ;
        else output << "Nothing to print" ;
    }

    void play(string name) const {
        ptrMultimedia m = findMultimedia(name) ;
        if (m != nullptr) m->play() ;
        else cout << "Nothing to play !" ;
    }
};

#endif // MAPPING_H
