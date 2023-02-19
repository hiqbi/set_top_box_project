#define VERSION_2

#include "Multimedia.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"
#include "Mapping.h"
#include <iostream>
#include <string>

using namespace std ;

#ifdef VERSION_1

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

    //Etape 10
    cout << endl << "#----- Etape 10 : Gestion cohérente des données -----#" << endl ;

    Mapping map = Mapping() ;
    shared_ptr<Photo> photo_map = map.createPhoto("photo_map", "desktop", 480, 480) ;
    shared_ptr<Video> video_map = map.createVideo("video_map", "desktop", 1) ;
    map.printMultimedia("photo_map", cout) ;
    ptrGroup group_ptr = map.createGroup("group_ptr") ;
    group_ptr->push_back(video_map) ;
    group_ptr->push_back(photo_map) ;
    map.printGroup("group_ptr", cout) ;

    return 0 ;
}

#endif

#ifdef VERSION_2

#include <sstream>
#include "tcp/tcpserver.h"

const int PORT = 3331 ;

enum class Command {
    PRINT_MULTIMEDIA,
    PRINT_GROUP,
    PLAY_MULTIMEDIA,
    STOP,
    NOT_FOUND
};

map<string, Command> possible_commands = {
    {"print", Command::PRINT_MULTIMEDIA},
    {"print_group", Command::PRINT_GROUP},
    {"play", Command::PLAY_MULTIMEDIA},
    {"stop", Command::STOP},
};

Command cmd(string command) {
    if (possible_commands.find(command) != possible_commands.end()) return possible_commands[command] ;
    return Command::NOT_FOUND ;
}

int main(int argc, const char *argv[]) {

    Mapping all = Mapping() ;
    shared_ptr<Photo> vvg = all.createPhoto("vvg.jpg", "./", 794, 1000) ;
    shared_ptr<Video> rickroll = all.createVideo("rickroll.mp4", "./", 1) ;
    ptrGroup group = all.createGroup("group") ;
    group->push_back(vvg) ;
    group->push_back(rickroll) ;

    auto *server = new TCPServer([&](string const &request, string &response) // To initialize the server
    {
        cout << "Request : " << request << endl ;

        stringstream ss(request) ; // request a la forme, par exemple, de (print_group grp1)
        string command ;
        ss >> command ; // >> s'arrête dès quelle trouve un espace

        stringstream to_send = stringstream() ;

        switch(cmd(command)) {
            case Command::PRINT_MULTIMEDIA :
            {
                string name ;
                ss >> name ;
                all.printMultimedia(name, to_send) ;
                response = to_send.str() ;
                break ;
            }

            case Command::PRINT_GROUP :
            {
                string name ;
                ss >> name ;
                all.printGroup(name, to_send) ;
                response = to_send.str() ;
                break ;
            }

            case Command::PLAY_MULTIMEDIA :
            {
                string name ;
                ss >> name ;
                all.play(name) ;
                response = to_send.str() ;
                break ;
            }

            case Command::STOP :
            {
                response = "stop" ;
                return false ;
                break ;
            }

            default :
                response = "Command not found" ;
                return true ;
                break ;
        }

        cout << "Response : " << response << endl ;

        return true ;
    }) ;

    cout << "Starting server on port " << PORT << endl ;

    int status = server->run(PORT) ; // La boucle infinie du serveur est lancée

    if (status < 0) {
        cerr << "Something went wrong !" << endl ;
        return 1 ;
    }

    return 0 ;
}
#endif
