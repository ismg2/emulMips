L’ensemble du code executable se trouve dans le dossier code_inter.

Les fichiers test boucle.o et procedure.o et pile.o se trouvent dans le dossier « res » 



Directory testbasicfunction :

dico_def.txt : Petit dictionnaire qui nous a servi pour les premiers test 

dico_definitif.txt : Dictionnaire finale contenant toutes les commandes

test_affichage_op.c :Premier essai pour afficher les différentes opérandes d'un mot pris du fichier ELF.On affiche les numero des registres pour le moment ! Pas de mnemonique !

test_function.c : Recherche basique de nom de registre pour verifier si ces registres existent

test_get_type.c : Recherche des types de variable Hexadecimal,WORD,BYTE,DECIMAL ou plus exotique…

test_lecture_dico.c : Mise en mémoire du dictionnaire et affichage de toutes les commandes ainsi que son descriptif

test_registre.c : Mise en place du tableau de registre et conversion du numero du registre à la mnémonique correspondante pour la fonction de desassamblage

Directory test_fonction_registre : Contient un main pour le test de l’ensemble des fonction de manipulation des registres.

Directory fonction_mips : Test des différentes fonctions du Mips