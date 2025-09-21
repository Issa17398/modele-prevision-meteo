# Utiliser une image Ubuntu avec build tools
FROM ubuntu:22.04

# Installer dépendances système
RUN apt-get update && apt-get install -y \
    build-essential cmake openmpi-bin libopenmpi-dev \
    python3 python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Créer dossier de travail
WORKDIR /app

# Copier les fichiers du projet
COPY . .

# Installer dépendances Python
RUN pip3 install -r requirements.txt

# Commande par défaut (lancement séquentiel)
CMD ["./build/meteo"]
