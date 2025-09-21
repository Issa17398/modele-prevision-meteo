# 🌦️ Modèle simplifié de prévision météorologique

---

## 1. Introduction

La **prévision météorologique numérique (NWP – Numerical Weather Prediction)** repose sur la **résolution numérique d’équations aux dérivées partielles (EDP)** décrivant l’évolution des champs atmosphériques (température, pression, humidité, vitesse du vent, etc.).  
Les grands modèles comme **ARPEGE** ou **AROME** s’appuient sur des **supercalculateurs** et des millions de lignes de code, mais le principe de base reste la résolution des équations de la dynamique des fluides.

👉 Dans ce projet, nous développons un **modèle réduit** illustrant ces concepts :

- **Équation d’advection-diffusion** pour représenter le transport et la dispersion d’une grandeur scalaire (température, polluant, humidité).  
- **Méthode des différences finies** pour la résolution numérique.  
- **Parallélisation** via OpenMP et MPI pour exploiter les architectures multi-cœurs.  
- **Reproductibilité** grâce à Docker.  
- **Visualisations dynamiques** (images et animations) pour interpréter les résultats.  

Ce projet combine **mathématiques appliquées, simulation numérique et informatique scientifique**, avec une orientation pratique pour l’apprentissage du **HPC (High Performance Computing)**.

---

## 2. Modélisation mathématique

### 2.1. Advection pure

$$
\frac{\partial u}{\partial t} + v_x \frac{\partial u}{\partial x} + v_y \frac{\partial u}{\partial y} = 0
$$

👉 Le champ $u$ est transporté par le vent **sans se déformer**.

### 2.2. Diffusion pure

$$
\frac{\partial u}{\partial t} = D \left( \frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} \right)
$$

👉 Une "boule chaude" placée au centre se **dissipe progressivement**.

### 2.3. Advection-diffusion

$$
\frac{\partial u}{\partial t} + v_x \frac{\partial u}{\partial x} + v_y \frac{\partial u}{\partial y} = D \left( \frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} \right)
$$

👉 $u$ est **transporté** par le vent tout en **se diffusant**.

### 2.4. Discrétisation numérique

Schéma explicite aux différences finies :

⚠️ **Condition CFL (stabilité)** :

$$
\Delta t \leq \min \left( \frac{\Delta x}{|v_x|}, \frac{\Delta y}{|v_y|}, \frac{\Delta x^2 \Delta y^2}{2D(\Delta x^2+\Delta y^2)} \right)
$$

---

## 3. Organisation du code

### 📂 include/

Déclarations de fonctions, structures et constantes pour modularité et réutilisation.

### 📂 src/

- **`main.c`** : point d’entrée, coordonne modules et simulation.  
- **`grid.c`** : gestion du domaine de calcul et initialisation.  
- **`boundary.c`** : conditions aux limites (Dirichlet, Neumann, périodiques).  
- **`advection.c`** : schémas numériques pour transport.  
- **`diffusion.c`** : propagation isotrope.  
- **`parallel.c`** : parallélisation MPI + OpenMP.  
- **`io.c`** : lecture des paramètres et sauvegarde des résultats.

---

## 4. Visualisation

- **`visualize.py`** → cartes statiques de température ou concentration.  
- **`animate.py`** → vidéos de l’évolution temporelle du champ simulé.  

Résultats stockés dans `figures/` et `animations/`.

---

## 5. Déploiement avec Docker

Conteneur Docker contient :

- Python pour visualisation  
- MPI, OpenMP, GCC pour compilation  
- Organisation des fichiers (`src/`, `include/`, `output/`, `figures/`)  

---

## 6. Workflow et tests

### 6.1. Compilation et exécution

```bash
docker-compose build --no-cache
docker-compose run meteo bash

mkdir build && cd build
cmake ..
make -j$(nproc)
mkdir -p /app/output
mpirun --allow-run-as-root -np 4 ./build/meteo
