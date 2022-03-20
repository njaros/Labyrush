# Labyrush

### MODE D EMPLOI ATM###

1/ make
2.1/ ./labyrush laby/laby1 ou une autre map que vous pouvez creer.
2.2/ executer labyrush sans argument lance une map generee aleatoirement (non implemente pour le moment).
3/ Le programme attent ensuite les bonnes commandes sur stdin. Vous pouvez taper HAUT, BAS, GAUCHE, DROITE ou autre chose.


###### EN TRAVAUX ######

- aff_vue_perso peut etre ameliorer, car pour le moment le personnage voit a travers les murs, pas cool.

- implementer un temps max pour l attente de stdin.

- mazer a faire (generateur de labyrinthe).

Tests a faire.

###### EN TRAVAUX ######

Ici est mon 1er sujet de rush.

Ce programme génère une carte 2D labyrinthique, retourne des données de la carte puis récupère des données de deplacement provenant d'un autre programme, et recommence jusqu'à ce qu'un scénario de fin advient.
Ce sujet est un pompage complet d'un sujet de codingame.

But du jeu :

MP = mon programme

PJ = progamme du joueur

MP crée un labyrinthe avec un point A de départ, un point B d'objectif.

### BUT DU JEU ###

- Un personnage dans un labyrinthe commence à un point A.
- Le personnage doit parcourir un labyrinthe inconnu dans le but de trouver l'objectif B.
- Une fois l'objectif B trouvé, le personnage doit au plus vite le ramener à A (son point de départ), il meurt s'il ne trouve pas le meilleur chemin.

### INITIALISATION ###

MP retourne avant le tour 1 la largeur et la longueur de la map (permettant a PJ d'allouer ses mémoires), la position de départ du personnage, ainsi que le temps à ne pas dépasser pour ramener B à A.

Concernant les caractères de la carte fourni par MP:
- '#' est un mur
- '.' est un sol
- 'P' est le personnage
- 'O' est l'objectif
- 'E' est le point de départ
- '?' est non visible par le personnage

### PROCESSUS ###

A chaque tour :
- MP retourne la vision actuelle du personnage (2 cases autour).
- PJ doit retourner "HAUT" "BAS" "GAUCHE" ou "DROITE".

Fin du jeu si :
- PJ écrit autre chose
- PJ fait foncer le personnage dans un mur
- PJ met trop de temps à répondre
- PJ ne ramène pas B dans les temps
- PJ gagne

### SCORE ###

MP compte chaque instruction de PJ, permettant de comparer les algo entre eux.

### INTERET DE LA SIMULATION ###

Le joueur devra coder un algorithme de découverte de carte ainsi qu'un algorithme de plus court chemin "pathfinding".

