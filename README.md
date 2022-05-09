# Labyrush

### MODE D EMPLOI ATM ###

- 1/ make

- 2.1/ ./labyrush laby/laby1 ou une autre map que vous pouvez creer.

- 2.2/ executer labyrush sans argument lance une map generee aleatoirement.

- 3/ Le programme attent ensuite les bonnes commandes sur stdin. Vous pouvez taper HAUT, BAS, GAUCHE, DROITE ou autre chose.

###### INTRODUCTION ######

Ici est mon 1er sujet de rush.

Ce programme génère ou récupère une carte 2D labyrinthique, retourne des données de la carte puis récupère des données de deplacement provenant d'un autre programme, et recommence jusqu'à ce qu'un scénario de fin advient.
Ce sujet est un pompage quasi complet d'un sujet de codingame.

Ce programme crée ou récupère un labyrinthe avec un point E de départ, un point O d'objectif.

### BUT DU JEU ###

- Un personnage dans un labyrinthe commence à un point E.
- Le personnage doit parcourir un labyrinthe inconnu dans le but de trouver l'objectif O.
- Une fois l'objectif O trouvé, le personnage doit au plus vite le ramener à E (son point de départ), il meurt s'il ne le ramene pas assez vite.

### INITIALISATION ###

MP retourne avant le tour 1 la largeur et la longueur de la map (permettant a PJ d'allouer ses mémoires), la position de départ du personnage, ainsi que le temps à ne pas dépasser pour ramener O à E.

Concernant les caractères de la carte fourni par MP:
- '#' est un mur
- '.' est un sol
- 'P' est le personnage
- 'O' est l'objectif
- 'E' est le point de départ
- '?' est non visible par le personnage

### PROCESSUS ###

MP = mon programme

PJ = progamme du joueur

A chaque tour :
- MP retourne la vision actuelle du personnage (2 cases autour).
- PJ doit retourner "HAUT\n" "BAS\n" "GAUCHE\n" ou "DROITE\n".

Fin du jeu si :
- PJ écrit autre chose
- PJ fait foncer le personnage dans un mur
- PJ met trop de temps à répondre
- PJ ne ramène pas O dans les temps
- PJ gagne

### SCORE ###

MP compte chaque instruction de PJ, permettant de comparer les algo entre eux.

### INTERET DE LA SIMULATION ###

Les joueurs devront coder un algorithme de découverte de carte ainsi qu'un algorithme de plus court chemin "pathfinding".
Pour le pathfinding, on peut orienter les joueurs sur un algo dijkstra ou a*, ce qui augmentera leur maîtrise des listes.

L'algorithme de découverte de carte sera celui qui déterminera le meilleur score (en cas de succès), donc ce n'est pas le plus simple !
