Daniele Gamba - Sfera con effetti ottici di rifrazione per Zuru Tech, aprile 2019

Il codice è da compilare in Unreal Engine 4.21.2

L'implementazione si articola in tre classi:

La classe Trackball rimpiazza la Pawn predefinita e implementa un sistema apposito di 
movimento della camera nello spazio tridimensionale. Inoltre intercetta gli input da tastiera 
dell'utente e li passa all'oggetto GlassBall presente in scena.

La classe MyPlane crea un piano e gli assegna come materiale lo Shader
che ho scritto. Inoltre crea in scena un attore di tipo GlassBall, che rappresenta
la sfera con i suoi parametri.

La classe GlassBall riceve come input i parametri dalla Trackball e li passa al materiale
del piano. 


Comandi:

WASD			movimento sfera
Numpad + e - 		cambia dimensioni sfera
MN			cambia indice rifrazione vetro
Barra spaziatrice	inizia animazione della luce