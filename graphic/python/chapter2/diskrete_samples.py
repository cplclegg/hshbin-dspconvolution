import matplotlib.pyplot as plt
import numpy as np

# 1. Parameter definieren
f = 5           # Frequenz der Sinusschwingung
fs = 80         # Abtastrate (80 Samples pro Sekunde)

# 2. Zeit-Achse für die Samples (diskret)
t_sampled = np.arange(0, 1, 1/fs) 
y_sampled = np.sin(2 * np.pi * f * t_sampled)

# 3. Plotten
plt.figure(figsize=(10, 4))

# Der Stem-Plot (Lote)
markerline, stemlines, baseline = plt.stem(t_sampled, y_sampled)


# Styling der Linien
plt.setp(stemlines, linestyle='--', color='skyblue', linewidth=1) # Gestrichelte Lote
plt.setp(markerline, marker='o', color='black', markersize=3)   # Die Punkte oben
plt.setp(baseline, color='black', linewidth=0.5)             # Die Nulllinie

# Beschriftung
plt.title(f"Diskretes Signal")
plt.xlabel("Zeit in Sekunden")
plt.ylabel("Signalwert")
plt.grid(True, linestyle=':', alpha=0.6)

# Speichern
plt.savefig('./diskretes_signal.pdf')
#plt.show()