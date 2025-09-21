import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import glob
import os

def animate_simulation(pattern="output/output_step_*.csv", output_file="animation.mp4"):
    """
    Crée une animation à partir des fichiers CSV générés par le modèle et la sauvegarde en MP4.
    """
    files = sorted(glob.glob(pattern))
    if not files:
        print("Aucun fichier trouvé.")
        return

    fig, ax = plt.subplots()
    data = np.loadtxt(files[0], delimiter=",")
    im = ax.imshow(data, cmap="coolwarm", origin="lower")
    plt.colorbar(im, ax=ax, label="Température")

    def update(frame):
        data = np.loadtxt(files[frame], delimiter=",")
        im.set_array(data)
        ax.set_title(f"Étape {frame}")
        return [im]

    ani = animation.FuncAnimation(fig, update, frames=len(files), interval=200, blit=True)

    # Sauvegarde en MP4
    ani.save(output_file, writer="ffmpeg", dpi=150)
    print(f"Animation sauvegardée : {output_file}")
    plt.close()

if __name__ == "__main__":
    animate_simulation()
