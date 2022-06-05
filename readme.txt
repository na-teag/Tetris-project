
Auteurs  :

	Gaétan Retel
	Clément Praud


Système d'exploitation supporté :

	Linux

Comment lancer le programme :

	1 - Téléchargez les différents dossiers et fichiers, placez les de préférence dans un dossier dédié.
	2 - ouvrez un terminal depuis ce dossier.
	3 - Dans le terminal, effectuer la commande "make".
	4 - Toujours dans le terminal, effectuer la commande "cd bin".
	5 - Enfin, tapez la commande "./exec".


Contenu des fichiers :

	main.c :	programme principal, contient les déclaration des variables, le menu principal, les boucles de jeu.
	functions.c :	contient les différentes fonctions de calcul qui n'interagisse pas avec l'utilisateur.
	display.c :	contient les fonctions qui interagisse avec l'utilisateur. (printf ou scanf, hors tutoriel).
	tetriminos.c :	contient les données des pièces de jeu, ainsi que la construction du tableau où elles sont rassemblées.
	tutorial.c :	contient le tutoriel de tetris.
	beta.c :	contient la version 2.0, actuellement en cours de débogage.
	header.h :	contient la déclaration de toutes les fonctions et les structures, ainsi que l'inclusion des bibliothèques requises.
	color.h :	contient la fonction permettant de changer les couleurs du teminal.
	Makefile :	contient la liste des commandes à exécuter par le terminal lorsque l'utilisateur tape la commande "make".
