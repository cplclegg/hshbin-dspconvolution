import numpy as np
import matplotlib.pyplot as plt

# 1. Parameter
fs = 1000              # Abtastrate (1000 Hz)
f0 = 50                # Frequenz der Sinuswelle (50 Hz)
duration = 0.1         # Dauer in Sekunden (für den Zeit-Plot)

# Zeitachse
t = np.linspace(0, duration, int(fs * duration), endpoint=False)
y = np.sin(2 * np.pi * f0 * t)

# 2. Frequenzbereich (Fourier-Transformation)
# Wir nehmen eine etwas längere Dauer für eine bessere Auflösung im Frequenzbereich
t_long = np.linspace(0, 1, fs, endpoint=False)
y_long = np.sin(2 * np.pi * f0 * t_long)

frequencies = np.fft.rfftfreq(len(y_long), 1/fs)
magnitude = np.abs(np.fft.rfft(y_long)) / (len(y_long)/2)

# 3. Plot erstellen
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 4))

# Zeitbereich
ax1.plot(t, y, color='blue')
ax1.set_title(f"Zeitbereich (Sinus mit {f0} Hz)")
ax1.set_xlabel("Zeit [s]")
ax1.set_ylabel("Amplitude")
ax1.grid(True, linestyle=':')

# Frequenzbereich
ax2.stem(frequencies, magnitude, linefmt='red', markerfmt='ro', basefmt=" ")
ax2.set_title("Frequenzbereich (Spektrum)")
ax2.set_xlabel("Frequenz [Hz]")
ax2.set_ylabel("Betrag")
ax2.set_xlim(0, 100) # Wir zoomen auf die ersten 100 Hz
ax2.grid(True, linestyle=':')

plt.tight_layout()
plt.savefig('zeit_frequenz_vergleich.pdf')
plt.show()