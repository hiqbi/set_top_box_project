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