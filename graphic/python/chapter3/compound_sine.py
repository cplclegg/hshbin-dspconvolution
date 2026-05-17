import matplotlib.pyplot as plt
import numpy as np
from matplotlib.lines import Line2D
# 1. Parameter definieren
f0 = 1
f1 = 10
f2 = 20           # Frequenz der Sinusschwingung
fs = 40         # Abtastrate (80 Samples pro Sekunde)

# 2. Zeit-Achse für die Samples (diskret)
t_sampled = np.arange(0, 1, 1/fs)
y_sampled = np.sin(2 * np.pi * f0 * t_sampled)+np.sin(2 * np.pi * f1 * t_sampled)/10+np.sin(2 * np.pi * f2 * t_sampled)/20

# 3. Plotten
plt.figure(figsize=(10, 4))

# Der Stem-Plot (Lote)
markerline, stemlines, baseline = plt.stem(t_sampled, y_sampled)


# Styling der Linien
plt.setp(stemlines, linestyle='--', color='skyblue', linewidth=1) # Gestrichelte Lote
plt.setp(markerline, marker='o', color='black', markersize=3)   # Die Punkte oben
plt.setp(baseline, color='black', linewidth=0.5)             # Die Nulllinie

# Beschriftung
plt.title(f"Zusammengesetzter Sinus")
plt.xlabel("Zeit in Sekunden")
plt.ylabel("Signalwert")
plt.grid(True, linestyle=':', alpha=0.6)

# Speichern
plt.savefig('./compound_sinusoid.pdf')
#plt.show()

kernel = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1]

filtered = []

for i in range(len(y_sampled)):
    sample = 0
    for j in range(len(kernel)):
        if i-j < 1:
            continue
        sample += kernel[j] * y_sampled[i-j]
    filtered.append(sample)

plt.figure(figsize=(10, 4))

# Der Stem-Plot (Lote)
markerline, stemlines, baseline = plt.stem(t_sampled, filtered)

# Styling der Linien
plt.setp(stemlines, linestyle='--', color='skyblue', linewidth=1) # Gestrichelte Lote
plt.setp(markerline, marker='o', color='black', markersize=3)   # Die Punkte oben
plt.setp(baseline, color='black', linewidth=0.5)             # Die Nulllinie

# Beschriftung
plt.title(f"Zusammengesetzter Sinus nach Anwendung des Moving Average Filters")
plt.xlabel("Zeit in Sekunden")
plt.ylabel("Signalwert")
plt.grid(True, linestyle=':', alpha=0.6)

# Speichern
plt.savefig('./filtered_compound_sinusoid.pdf')
#plt.show()

plt.figure(figsize=(10, 4))

kernel_sampled = np.arange(0, 1, 1/len(kernel))
# Der Stem-Plot (Lote)
markerline, stemlines, baseline = plt.stem(kernel_sampled, kernel)

# Styling der Linien
plt.setp(stemlines, linestyle='--', color='skyblue', linewidth=1) # Gestrichelte Lote
plt.setp(markerline, marker='o', color='black', markersize=3)   # Die Punkte oben
plt.setp(baseline, color='black', linewidth=0.5)             # Die Nulllinie

# Beschriftung
plt.title(f"Koeffizienten des Moving Average Filters als diskretes Signal interpretiert")
plt.xlabel("Zeit in Sekunden")
plt.ylabel("Signalwert")
plt.grid(True, linestyle=':', alpha=0.6)

# Speichern
plt.ylim(0, 1)
plt.savefig('./filter_kernel.pdf')
#plt.show()

# Optional: convert filtered to NumPy array if it is still a Python list
filtered = np.array(filtered)

# Colorblind-friendly colors (Okabe-Ito palette)
color_input = "#0072B2"     # blue
color_filtered = "#D55E00"  # orange / vermillion

plt.figure(figsize=(10, 4))
ax = plt.gca()

# Input signal stem plot
markerline1, stemlines1, baseline1 = ax.stem(
    t_sampled, y_sampled
)
plt.setp(stemlines1, linestyle='--', color=color_input, linewidth=1.2, alpha=0.9)
plt.setp(markerline1, marker='o', color=color_input,
         markerfacecolor='white', markeredgecolor=color_input, markersize=4)
plt.setp(baseline1, color='black', linewidth=0.5)

# Filtered signal stem plot
markerline2, stemlines2, baseline2 = ax.stem(
    t_sampled, filtered
)
plt.setp(stemlines2, linestyle='-', color=color_filtered, linewidth=1.2, alpha=0.9)
plt.setp(markerline2, marker='s', color=color_filtered,
         markerfacecolor='white', markeredgecolor=color_filtered, markersize=4)

# Custom legend
legend_handles = [
    Line2D([0], [0],
           color=color_input, linestyle='--',
           marker='o', markerfacecolor='white',
           markeredgecolor=color_input,
           label='Eingangssignal'),
    Line2D([0], [0],
           color=color_filtered, linestyle='-',
           marker='s', markerfacecolor='white',
           markeredgecolor=color_filtered,
           label='Ausgangssignal')
]

ax.legend(handles=legend_handles, loc='best')

# Labels
plt.title("Gegenüberstellung von Eingangs- und Ausgangssignal des Moving Average Filters")
plt.xlabel("Zeit in Sekunden")
plt.ylabel("Signalwert")
plt.grid(True, linestyle=':', alpha=0.6)

# Save combined plot
plt.tight_layout()
plt.savefig('./comparison_compound_filtered.pdf')
# plt.show()