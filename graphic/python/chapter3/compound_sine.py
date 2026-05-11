import matplotlib.pyplot as plt
import numpy as np

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
plt.title(f"Zusammengesetzter Sinus nach Anwendung des Moving Averagers")
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
plt.title(f"Koeffizienten des Moving Averagers als diskretes Signal interpretiert")
plt.xlabel("Zeit in Sekunden")
plt.ylabel("Signalwert")
plt.grid(True, linestyle=':', alpha=0.6)

# Speichern
plt.ylim(0, 1)
plt.savefig('./filter_kernel.pdf')
#plt.show()