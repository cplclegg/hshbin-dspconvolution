import matplotlib.pyplot as plt
import numpy as np

# 1. Parameter festlegen
fs = 10              # Abtastrate (10 Hz)
f_slow = 2           # Die "echte" langsame Frequenz (2 Hz)
f_alias = fs + f_slow # Die Alias-Frequenz (12 Hz) -> 10 + 2

# Zeitachsen für die glatten Kurven (stetig)
t_fine = np.linspace(0, 1, 1000)
y_slow = np.sin(2 * np.pi * f_slow * t_fine)
y_alias = np.sin(2 * np.pi * f_alias * t_fine)

# Zeitachse für die Abtastpunkte (diskret)
t_sampled = np.arange(0, 1.1, 1/fs)
y_sampled = np.sin(2 * np.pi * f_slow * t_sampled)

# 2. Plot erstellen
plt.figure(figsize=(12, 6))

# Die langsame Welle (Soll-Signal)
plt.plot(t_fine, y_slow, label=f"Original-Signal ({f_slow} Hz)", color='blue', linewidth=2)

# Die schnelle Welle (Alias-Signal)
plt.plot(t_fine, y_alias, label=f"Alias-Signal ({f_alias} Hz)", color='red', linestyle='--', alpha=0.6)

# Die Abtastpunkte (Lote / Stem)
markerline, stemlines, baseline = plt.stem(t_sampled, y_sampled, linefmt='black', markerfmt='ko', label=f'Abtastpunkte ($f_s$ = {fs} Hz)')
plt.setp(stemlines, linewidth=1, alpha=0.5)

# Beschriftung
plt.title("Visualisierung von Aliasing: Zwei Frequenzen, dieselben Abtastwerte")
plt.xlabel("Zeit in Sekunden")
plt.ylabel("Amplitude")
plt.legend(loc='upper right')
plt.grid(True, linestyle=':', alpha=0.7)

# Speichern
plt.savefig('./aliasing_vergleich.pdf', bbox_inches='tight')
plt.show()