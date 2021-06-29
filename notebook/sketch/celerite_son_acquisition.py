# -*- coding: utf-8 -*-
from serial import *
from numpy import *

"""Données pour la connexion série
"""
nom_port = "/dev/ttyACM0" # A modifier suivant le branchement de l'arduino
vitesse_baud = 115220  # Doit être le même que dans le programme Arduino
read_timeout = 1
write_timeout = 1

"""Récupération des réglages

On demande le nom du fichier pour enregistrer les données
et le nombre d'échantillons à mesurer pour une distance donnée.
"""
filename = input("Entrez le nom du fichier (sans extension - attention si le fichier existe, son contenu sera supprimé) : ") + ".dat"
n_echantillons = int(input("Combien d'échantillons (MAX : 5000) pour chaque mesures de temps de vol ? "))
# filename = "vitesse_son_inconnue.dat"
# n_echantillons = 1000

with open(filename, 'w') as file:
    """Ecriture de l'entête du fichier de données
    """
    entete = "d(cm)"
    for i in range(1, n_echantillons + 1):
        entete += ",E" + str(i)
    entete += "\r\n"
    file.write(entete)

    continuer = True  # Servira à recommencer pour une autre mesure
    while continuer:
        # Entrée de la distance pour le tableau de mesures.
        distance = input("Entrez la distance entre l'émetteur et l'obstacle (en cm) : ")
        # distance = "40"
        mesures = distance + ","  # Chaîne de caractère où seront enregistrées les mesures.
        # Ouverture de la communication avec l'Arduino
        with Serial(port=nom_port, baudrate=vitesse_baud, timeout=read_timeout, writeTimeout=write_timeout) as port_serie:
            if port_serie.isOpen():
                time.sleep(2)  # Un temps de latence est nécessaire au démarrage de la communication série
                # Les deux lignes suivantes servent à vider le buffer au cas où
                toread = port_serie.inWaiting()
                port_serie.read(toread)
                port_serie.write("P".encode('ascii'))  # Pour prévenir Arduino que c'est Python qui parle
                port_serie.write(struct.pack('>H', n_echantillons))  # On envoie à Arduino le nombre d'échantillon
                # port_serie.write(str(n_echantillons).encode('ascii'))
                time.sleep(.1)
                tic = time.time()  # Fait office de timeout dans le programme qui attend les mesures.
                toread = port_serie.inWaiting()  # Nombre de bytes dans le buffer
                while(toread < 1 and time.time() - tic < 2):  # On attend le début de l'envoi
                    toread = port_serie.inWaiting()
                print("Début de la mesure")
                tic = time.time()  # Fait office de timeout dans le programme qui attend les mesures.
                acquisition = True
                while(acquisition and time.time() - tic < 1000):  # Tant qu'on ne lit pas un "E" sur le buffer on enregistre la mesure
                    mesure = port_serie.read(1).decode('ascii')
                    if (mesure == "E"):
                        acquisition = False
                    elif (mesure == "A"):
                        print("Il y a eu un problème avec la communication. Vous pouvez recommencer")
                        acquisition = False
                    else:
                        mesures += mesure
        print(len(mesures))
        file.write(mesures)
        file.write("\r\n")
        continuer = bool(int(input("Faire une autre mesure ? Entrez(1/0)")))
        # continuer = False
