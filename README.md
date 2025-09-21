# 🌦️ Modèle simplifié de prévision météorologique

---

## 1. Introduction

La **prévision météorologique numérique (NWP – Numerical Weather Prediction)** repose sur la **résolution numérique d’équations aux dérivées partielles (EDP)** décrivant l’évolution des champs atmosphériques (température, pression, humidité, vitesse du vent, etc.).  
Les grands modèles comme **ARPEGE** ou **AROME** s’appuient sur des **supercalculateurs** et des millions de lignes de code, mais le principe de base reste la résolution des équations de la dynamique des fluides.

👉 Dans ce projet, nous développons un **modèle réduit** permettant d’illustrer ces concepts :

- Utilisation d’une **équation d’advection-diffusion** pour représenter le transport et la dispersion d’une grandeur scalaire (par exemple : température, concentration d’un polluant, humidité).  
- Résolution numérique par **méthode des différences finies**.  
- Mise en œuvre de la **parallélisation** (OpenMP et MPI) afin de tirer parti des architectures multi-cœurs.  
- Déploiement reproductible grâce à **Docker**.  
- Génération de **visualisations dynamiques** (images et animations) pour interpréter les résultats.  

Ce projet combine donc **mathématiques appliquées, simulation numérique et informatique scientifique**, avec une orientation pratique pour l’apprentissage du **HPC (High Performance Computing)**.

---

## 2. Modélisation mathématique

### 2.1. Advection pure

On considère une grandeur $u(x,y,t)$ (température, polluant, humidité) transportée par un champ de vitesse constant $\vec{v}=(v_x,v_y)$.

**Équation :**

$$
\frac{\partial u}{\partial t} + v_x \frac{\partial u}{\partial x} + v_y \frac{\partial u}{\partial y} = 0
$$

👉 **Interprétation** : le champ $u$ est transporté par le vent **sans se déformer**.

---

### 2.2. Diffusion pure

La diffusion est modélisée par l’**équation de la chaleur** :

$$
\frac{\partial u}{\partial t} = D \left( \frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} \right)
$$

👉 **Interprétation** : une "boule chaude" placée au centre se **dissipe progressivement**.

---

### 2.3. Équation couplée : advection-diffusion

En combinant les deux phénomènes :

$$
\frac{\partial u}{\partial t} + v_x \frac{\partial u}{\partial x} + v_y \frac{\partial u}{\partial y} = D \left( \frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} \right)
$$

👉 **Interprétation** : $u$ est **transporté** par le vent tout en **se diffusant**.

---

### 2.4. Discrétisation numérique

Le domaine $[0,L_x] \times [0,L_y]$ est discrétisé en $N_x \times N_y$ points.

**Schéma explicite aux différences finies :**

$$
u_{i,j}^{n+1} = u_{i,j}^n - \Delta t \left( v_x \frac{u_{i+1,j}^n - u_{i-1,j}^n}{2\Delta x} + v_y \frac{u_{i,j+1}^n - u_{i,j-1}^n}{2\Delta y} \right)
+ D \Delta t \left( \frac{u_{i+1,j}^n - 2u_{i,j}^n + u_{i-1,j}^n}{\Delta x^2} + \frac{u_{i,j+1}^n - 2u_{i,j}^n + u_{i,j-1}^n}{\Delta y^2} \right)
$$

⚠️ **Condition CFL (stabilité)** :

$$
\Delta t \leq \min \left( \frac{\Delta x}{|v_x|}, \frac{\Delta y}{|v_y|}, \frac{\Delta x^2 \Delta y^2}{2D(\Delta x^2+\Delta y^2)} \right)
$$

---

## 3. Organisation du code

### 📂 include/

Le dossier `include/` contient les fichiers d’en-tête (`.h`) qui déclarent les **fonctions, structures et constantes** du projet.  

Rôles principaux :
- **Modularité** : séparer déclarations (`.h`) et implémentations (`.c`).  
- **Réutilisation** : un même `.h` peut être inclus dans plusieurs modules.  
- **Cohérence** : garantit la correspondance des types et prototypes.  
- **Lisibilité** : fournit une vue d’ensemble claire des fonctions disponibles.  

---

### 📂 src/

Chaque fichier source (`.c`) implémente un **aspect précis de la simulation numérique**.  

- **`main.c`** → Point d’entrée du programme.  
  Coordonne les modules, initialise la grille, applique les conditions aux limites, lance l’advection et la diffusion, puis sauvegarde les résultats.  

- **`grid.c`** → Gestion du domaine de calcul.  
  Crée et initialise la grille ($N_x \times N_y$), définit le pas spatial, réserve la mémoire pour les champs physiques.  

- **`boundary.c`** → Conditions aux limites.  
  Implémente Dirichlet, Neumann ou périodiques, nécessaires à la stabilité et au réalisme de la simulation.  

- **`advection.c`** → Transport des grandeurs.  
  Contient les schémas numériques (Upwind, Lax-Wendroff) pour simuler le déplacement d’une grandeur sous l’effet du vent.  

- **`diffusion.c`** → Propagation isotrope.  
  Implémente la diffusion de la chaleur/polluant via la discrétisation du Laplacien.  

- **`parallel.c`** → Parallélisation.  
  Division du domaine, communication entre sous-domaines via **MPI**, parallélisation de boucles via **OpenMP**. Permet d’exploiter plusieurs cœurs/machines.  

- **`io.c`** → Entrées/Sorties.  
  Lit les paramètres d’entrée (taille, pas de temps, nombre d’itérations) et sauvegarde les résultats (CSV, images, etc.) pour la visualisation.  

---

## 4. Visualisation

- **Images statiques** générées avec `visualize.py` → production de cartes de température ou concentration.  
- **Animations** générées avec `animate.py` → production de vidéos montrant l’évolution temporelle du champ simulé.  

Les résultats peuvent être stockés dans le dossier `figures/` ou `animations/`.  

---

## 5. Déploiement avec Docker

Un conteneur **Docker** garantit la reproductibilité.  
Il contient :  
- l’environnement Python (visualisation),  
- les dépendances de compilation (MPI, OpenMP, GCC),  
- et l’organisation des fichiers (`src/`, `include/`, `output/`, `figures/`).  

L’utilisateur peut donc compiler, exécuter et visualiser la simulation de manière isolée et portable.  

---

## 6. Déploiement et workflow

### 6.1. Compilation et exécution avec Docker

```bash
# Build de l'image Docker
docker-compose build --no-cache

# Lancer un conteneur interactif
docker-compose run meteo bash

# Créer le dossier build
mkdir build && cd build

# Compilation
cmake ..
make -j$(nproc)

# Créer le dossier de sortie
mkdir -p /app/output

# Exécution de la simulation MPI
mpirun --allow-run-as-root -np 4 ./build/meteo

[MPI Rank 2] OpenMP threads = 8
[MPI Rank 3] OpenMP threads = 8
[MPI Rank 1] OpenMP threads = 8
[MPI Rank 0] OpenMP threads = 8
Simulation 100x100, 100 pas de temps
MPI (Message Passing Interface) est utilisé pour distribuer le calcul entre plusieurs processus, éventuellement sur plusieurs machines ou cœurs. Ici, on a 4 processus MPI : Rank 0, 1, 2 et 3. OpenMP permet de tirer parti des cœurs multiples d’un CPU pour accélérer les calculs dans un processus donné. Ici, chaque processus MPI utilise 8 threads, donc la simulation peut utiliser 32 cœurs au total si disponible (4 MPI × 8 OpenMP). En résumé : chaque processus MPI gère une partie du domaine, et OpenMP accélère les calculs dans cette partie.


# Test advection
gcc -fopenmp -Iinclude src/grid.c src/advection.c tests/test_advection.c -o test_advection -lm
./test_advection

# Test diffusion
gcc -fopenmp -Iinclude src/grid.c src/diffusion.c tests/test_diffusion.c -o test_diffusion -lm
./test_diffusion

le test du flux net de diffusion au point (5,5) est de -40 unités. Cela correspond au fait qu’une "boule chaude" ou concentration initiale diminue en intensité à ce point car elle se disperse dans l’espace.
Le test du flux net d’advection au point (5,5) = -15 unités correspond à l’effet du transport par le vent ou le courant dans le domaine. Concrètement, cela signifie que la concentration ou la température au point (5,5) diminue parce qu’elle est transportée vers un autre point de la grille.#   m o d e l e - p r e v i s i o n - m e t e o  
 