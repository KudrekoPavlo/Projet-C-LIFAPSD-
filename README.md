# TERRA


# 🗺️ TerraNova

Le jeu se déroule dans un monde carré constitué de différents terrains : plaines, forêts, maisons et océans. Au début, le joueur doit collecter des ressources pour construire ses premières structures et assurer sa survie.

L’objectif est de développer une civilisation à partir de rien, en gérant la population, les ressources et les relations avec d'autres peuples. Expansion, diplomatie et stratégie militaire seront essentiels pour dominer et remporter la partie.

# 📸 Aperçu

![Demo](https://s1.ezgif.com/tmp/ezgif-1695878a38737b.gif)

# 🛠️ Installation

## Clonez le dépôt depuis Forge de l’université Lyon 1:

Ouvrez un terminal et exécutez la commande suivante

```bash
git clone https://forge.univ-lyon1.fr/projet-bdw3/terra.git
```

## Accédez au dossier du projet 
```bash
cd terra
```
## Compilez le projet 
```bash
make
```
## Lancez le jeu
```bash
./bin/SDL2jeu  
```

# Description
**Jeu de Survie et Stratégie**

**Objectif** : Enseigner les bases de la survie, de la vitesse, de la stratégie et de la géopolitique. Le but est de construire sa propre civilisation et de survivre aux menaces en commençant avec des ressources limitées.

## Début du Jeu

Le joueur démarre avec :
1 personnage (ouvrier).
Une forêt (source de bois).
Du blé sauvage (ressource alimentaire).

## Mécaniques Clés

**Ressources** :
Bois : Obtenu en abattant des arbres. La forêt se régénère (réapparaît dans les cases vides) si plus de 50% est coupé.
Blé : Récolté pour créer de nouveaux personnages. Se régénère comme la forêt.

**Construction** :
Maison : Coûte du bois, occupe 4 cases, et protège jusqu’à 4 personnages.
Chaque maison construite permet de créer un nouveau personnage (si assez de blé).

## Menaces :

**Ennemis** :
Poursuivent les personnages non protégés.
Un contact = mort du personnage.

**Tsunami** :
Arrive à intervalles réguliers (affiché via un timer).
Tue les personnages non abrités et réduit la durabilité des maisons.
Après 5 tsunamis, une maison est détruite.

## Gestion
Le taux de récolte diminue avec chaque construction/nouveau personnage, obligeant le joueur à optimiser ses ressources.

## Objectif du Niveau 1

Créer une mini-civilisation de 15 personnages en :
Gérant les ressources (bois, blé).
Survivant aux vagues d’ennemis et tsunamis.

**Échec** : Si tous les personnages meurent

## Exemple de Stratégie:
Abattre des arbres → construire une maison → produire du blé → créer des personnages → répéter en anticipant les menaces.

## Notes

Un équilibre entre expansion et protection est crucial.
Les tsunamis ajoutent une urgence temporelle, tandis que les ennemis testent la réactivité.
Adaptabilité : Le jeu encourage la planification à long terme et la gestion des risques.

# 🔮 À venir dans les prochaines mises à jour
Malgré les contraintes de temps et les défis rencontrés tout au long du développement, nous avons posé les bases de notre univers de jeu. Mais ce n’est que le début.

Notre ambition est d’enrichir l’expérience avec des mécaniques plus poussées et des chemins de progression variés. Voici un aperçu de ce qui vous attend :

🌾 Un système de ressources étendu, offrant plus de diversité stratégique.
🛡️ Des rôles et statuts pour vos personnages (grades militaires, titres royaux...) afin de structurer une hiérarchie dans votre civilisation.
🏙️ La possibilité de fonder des villes entières, de forger des alliances ou de déclarer la guerre à vos ennemis.
🤝 Un système de diplomatie : négociez la paix, échangez des ressources, ou imposez votre pouvoir.
🚚 Exportez votre blé vers d'autres nations en échange d’avantages politiques ou économiques.

Ce n’est qu’un avant-goût. L’avenir de votre empire est entre vos mains!


# 🚀 Fonctionnalités

- 🟣 Menu principal avec affichage des règles et explication du gameplay
- 🎮 Mécaniques de survie et stratégie en temps réel
- 🌳 Récolte dynamique :
    Bois via l’abattage d’arbres dans la forêt.
    Blé pour nourrir la population et créer des personnages.
    Régénération automatique des ressources si surconsommées (forêt/blé)
- 🏠 Construction de maisons. Chaque maison permet d’augmenter la capacité de population
- 🧍‍♂️ Création de personnages
    (Dépend du stock de blé et du nombre de maisons disponibles.Chaque nouveau personnage impacte la vitesse de récolte globale)
- 💣 Gestion de menaces :
    👹 Ennemis qui poursuivent et tuent les personnages non protégés.
    🌊 Tsunamis :
    Se déclenchent à intervalles réguliers (timer visible).
    Tuent les personnages non abrités.
    Endommagent les maisons (2 tsunamis = 1 maison détruite)
- 🎵 Ambiance sonore pacifique intégrée pour l'immersion
- 💡 Interface intuitive :
    Interaction par clavier et souris
- 🔁 Boucle de jeu flexible :
    Possibilité de recommencer après défaite.
    Réinitialisation des événements entre les boucles de jeu    


# 🧑‍💻 Utilisation / Commandes

**Déplacement** : Cliquez sur un personnage, puis sur la case de destination pour le déplacer.
**Collecte** : Approchez un arbre ou une ressource
**Construction** : Appuyez sur "M", puis cliquez sur une case libre entourée de 4 cases vides pour construire un bâtiment.
**Création personnage** : Nécessite une maison + blé

# 📑 Documentation Doxygen
Lancez doxygen :
```bash 
doxygen Doxyfile
```
Ouvrez la documentation :
```bash 
 open ./docs/html/index.html 

```
# 🧱 Structure du projet

 \verbatim
 terra/
 ├── bin/           # Fichiers binaires générés (exécutables)
 ├── data/          # Données du jeu (images, sons, etc.)
 ├── docs/          # Documentation Doxygen (HTML/PDF/LaTeX)
 ├── obj/           # Fichiers objets (.o) compilés
 ├── src/           # Code source principal
 │   ├── SDL2/       # Bibliothèque graphique SDL
 │   ├── Case.*                     # Classe représentant une case de terrain
 │   ├── Chronolog.*               # Classe pour la gestion du temps
 │   ├── Events.*                  # Classe pour gérer les événements du jeu
 │   ├── Game.*                    # Moteur principal du jeu
 │   ├── Maison.*                  # Construction et gestion de maisons
 │   ├── Node.h                    # Nœud pour l’algorithme A* (recherche de chemin)
 │   ├── Personage.*              # Gestion des personnages
 │   ├── Terrain.*                # Génération du terrain
 │   └── Tsunami.*                # Gestion des tsunamis
 ├── Doxyfile        # Fichier de configuration Doxygen
 ├── Makefile        # Script de compilation
 └── README.md       # Documentation du projet
 \endverbatim
 



# 👤 Auteurs 

- [ ] Mariia Vashchenko p2304117
- [ ] Pavlo Kudrenko p2212309 
- [ ] Nadia Ben Shika p2309390   

# 🫂 Support
Si vous rencontrez des problèmes avec notre jeu, vous pouvez poser vos questions sur notre chat de support :'<https://t.me/+HH4fnCd6pktlNWNi>'

# 📄 Licence

Ce projet est sous licence MIT – voir le fichier LICENSE pour plus d’informations.

