# INF224 - TP C++

## Séance 1 : étapes 1-5

### Etape 4 : Polymorphisme dans la méthode `play()`

La fontion `play` n'a pas d'implémentation dans la classe de base `Multimedia` car chaque type d'objet nécessite un programme différent pour être joué.

> La méthode `play()` est donc **abstraite**.

Son déclaration est :

```c++
virtual void play() const = 0 ;
```

Corollairement, on ne peut plus instancier d'objet `Multimedia` car puisuqe, cette classe contient une méthode abtraite, elle est considérée abstraite également. Les sous-classes (Video & Photo à ce niveau) doivent obligatoirement implémenter la méthode `play()` pour être instanciables : ceci est fait avec le mot-clé `override` pour déclarer la redéfinition de la méthode.

### Etape 5 : Traitement uniforme (en utilisant le polymorphisme)

On veut traiter de manière uniforme une liste comprenant des photos et des vidéos sans avoir à se préoccuper de leur type. Il faut donc "détecter" le type de chaque objet contenu dans la liste pour appliquer la bonne méthode.

1. Créer dans `main.cpp` un **tableau** dont les élements sont tantôt une photo tantôt une vidéo.
2. Ecrire une boucle permettant d'afficher les attributs de tous les élements du tableau. 

```c++
auto ** multimedia = new Multimedia * [2]
unsigned int count = 0 ;
    multimedia[count++] = new Photo("photo", "photo file", 720, 1080) ;
    multimedia[count++] = new Video("video", "video file", 5.4) ;
for (unsigned int k = 0 ; k < count ; ++k) {
    multimedia[k]->print(cout) ;
}
```

> La proprieté caractéristique de l'orienté objet qui permet de faire cela : **le polymorphisme.**

> Ce qui est spécifiquement nécessaire de faire dans le cas de C++ : déclarer tous les objets contenus dans le tableau comme des instances de la classe `Multimedia` et aussi déclarer le tableau lui même comme conteneur d'objets de type `auto` pour pouvoir décider le type des objets à la compilation.

> Le type des élements du tableau : ce sont des **pointeurs** vers des objets du fait que `new` renvoie un pointeur.

## Séance 2 : étapes 6-7

### Etape 7 : Destruction et copie d'objets

Il faut modifier la classe `Film.h` pour éviter des fuites de mémoire.

> Le problème de la copie (*shallow*) d'objet quand des pointeurs sont mis en jeu comme variables d'instance :

Les objets créé via une copie contiendront des pointeurs vers les mêmes variables d'instance que l'objet d'origine. Dans ce cas, la destruction de l'objet d'origine entraînera la déstruction des variables d'instance de la copie. 

On utilisera donc une copie profonde (*deep copy*).

Pour ce faire, il faut modifier l'opérateur d'affectation :
```c++
Film &operator=(const Film &from)
```

## Séance : étapes 8-9

### Etape 8 : Créer des groupes

On crée une class `Group` qui hérite de `std::list<Multimedia *>`. Il est à noter que l'héritage est publique afin de pouvoir utiliser les méthodes de `std::list` sur un objet instancié de la classe `Group`

> La liste d'objets doit être une liste de pointeurs d'objets : en effet, les objets `Group` contienderons des objets de types différents (Photo, Video & Film). 

> Comparaison à JAVA : On stocke toujours des pointeurs vers des objets sans même faire la distinction si ces objets sont du même type ou pas.

### Etape 9 : Gestion automatique de la mémoire

On commence par définir un nouveau type `ptrMultimedia` de smart pointers vers des objets multumedia :
```c++
using namespace std ;
typedef std::shared_ptr<Multimedia> ptrMultimedia ;
```
La classe `Group` hérite publiquement de `list<ptrMultimedia>`.

On teste la bonne implémentation de cette classe dans `main.cpp` en créant une instance de `Photo` et une autre de `Video` ainsi que deux instances de `Group`. On vérifie bien que les objets des groupes sont détruits quand ils n'appartiennent plus à aucun groupe.

```c++
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
```
A l'exécution, on a que `img`, qui est partagée par deux smart pointers contenus dans les deux groupes, n'est détruite qu'après la destruction de `grp1` et `grp2`.

### Etape 10 : Gestion cohérente des données

On écrit la classe `Mapping` ayant deux attributs : `map<string, ptrMultimedia>` pour contenir tout les objets multimedia & `map<string, ptrGroup>` pour stocker tout les groupes. Avec `ptrMultimedia` & `ptrGroup` sont des smart pointers définis comme suit :

```c++
using namespace std ;
typedef shared_ptr<Multimedia> ptrMultimedia ;
typedef shared_ptr<Group> ptrGroup ;
```

> Si l'on crée directement un objet avec `new`, il n'appartiendra à aucune table. On peut interdire un tel usage en déclarant les constructeurs de la classe `Multimedia` comme étant `private` et déclarer la classe `Mapping` comme étant `friend`.

### Etape 11 : Client/Serveur

Dans main, on crée des objets multimedia ainsi qu'un group pour tester : 

```c++
Mapping all = Mapping() ;
shared_ptr<Photo> vvg = all.createPhoto("vvg.jpg", "./", 794, 1000) ;
shared_ptr<Video> rickroll = all.createVideo("rickroll.mp4", "./", 1) ;
ptrGroup group = all.createGroup("group") ;
group->push_back(vvg) ;
group->push_back(rickroll) ;
```

Dans le terminal :

##### En tapant `make run` dans le répertoire contenant le Serveur, on lance la boucle infinie de celui-ci : il est donc prêt à recevoir la requête du Client.
##### Dans le répertoire contenant le Client (`tcpserver` pour tester, puis le répertoire `swing` une fois l'interface graphique est faite), un `./client` (ou `make run` après l'ajout du `Makefile`) permet d'établir la connexion Client/Serveur. Il suffit après d'envoyer la requête depuis ce terminal.