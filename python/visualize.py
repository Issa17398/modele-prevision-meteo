import numpy as np
import matplotlib.pyplot as plt
import os

def visualize_grid(filename, output_dir="figures"):
    """
    Lit un fichier CSV généré par le modèle C et sauvegarde la grille en image.
    """
    os.makedirs(output_dir, exist_ok=True)  # crée le dossier si inexistant
    data = np.loadtxt(filename, delimiter=",")

    plt.imshow(data, cmap="coolwarm", origin="lower")
    plt.colorbar(label="Température")
    plt.title(f"Carte de température ({os.path.basename(filename)})")
    plt.xlabel("X")
    plt.ylabel("Y")

    # Sauvegarde
    out_file = os.path.join(output_dir, f"{os.path.basename(filename)}.png")
    plt.savefig(out_file)
    print(f"Figure sauvegardée : {out_file}")
    plt.close()  # ferme la figure pour libérer la mémoire

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python visualize.py <fichier.csv>")
    else:
        visualize_grid(sys.argv[1])
