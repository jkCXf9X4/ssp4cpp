
from pathlib import Path
import pandas as pd
import numpy as np
import matplotlib
matplotlib.use("Agg")                  # if you run in a headless/script env
import matplotlib.pyplot as plt

plt.style.use("fast")

df = pd.read_csv("./results/result.csv")

save_folder = Path("./results/plots/").resolve()
save_folder.mkdir(exist_ok=True)

df = df.sort_values("time")
x = df["time"].to_numpy()
print(df.columns)



# Downsample when huge (speeds draw & file size) — tweak max_points as you like
def downsample(y, max_points=100):
    n = y.shape[0]
    if n <= max_points:
        return x, y
    step = max(1, n // max_points)
    return x[::step], y[::step]

# Render the table
for col in df.columns[1:]:
    y = df[col].to_numpy()
    x_plot, y_plot = downsample(y)
    
    fig, ax = plt.subplots(figsize=(8, 5))
    ax.plot(x_plot, y_plot)
    ax.set_xlabel("time")
    ax.set_ylabel(col)
    ax.grid(True)
    # no legend() call (saves time)
    # no bbox_inches="tight" (saves time)

    fig.savefig(save_folder / f"{col}.png", dpi=100)
    plt.close(fig)