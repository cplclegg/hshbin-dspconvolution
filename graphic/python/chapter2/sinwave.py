import matplotlib.pyplot as plt
import numpy as np

#Array von 1000 Werten, zwischen 0 und 1
t = np.linspace(0, 1, 1000)

#Frequenz: 440Hz
f = 5

#Sinuswerte berechnen
y = np.sin(2 * np.pi * f * t)

#plotten
plt.plot(t, y)
plt.title("Stetiges Audiosignal (5 Hz)")
plt.xlabel("Zeit in Sekunden")
plt.ylabel("Signalwert")
plt.grid(True)

plt.savefig('./stetiges_signal.pdf')
#plt.show()

print("Finished")