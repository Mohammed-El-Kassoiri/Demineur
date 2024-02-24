# Description générale

Le jeu à développer est conçu pour un seul joueur. Il va essayer d’éviter les n mines cachées sous
un terrain de jeu présenté sous la forme d'une grille rectangulaire de taille 10×10 (Figure 1). 
terrain est composé des cases vides ou contenant une mine.

Le joueur choisit une case (activer une case) de la grille à chaque étape. Votre programme va faire
la vérification suivante :
   • Si la case choisie contient une mine, le joueur a perdu. Le jeu doit se terminer et le contenu
   de la grille est révélé.
  • Si la case est vide (c. -à-d. elle ne contient pas de mine), elle va être révéler et :
           ➢ Si une ou plusieurs de ses cases adjacentes comportent des mines, le programme
                doit afficher dans la case sélectionnée le nombre de ces mines.
           ➢ Si aucune mine dans son entourage, ses case voisines sont révélées d’une manière
               récursive.
Le![1234](https://github.com/erreur404-7M7/Demineur/assets/155988288/a88b1dfc-6fee-489b-9b5c-82370b8cb06e)


