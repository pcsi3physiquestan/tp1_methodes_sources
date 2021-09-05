---
jupytext:
  encoding: '# -*- coding: utf-8 -*-'
  formats: ipynb,py:percent
  split_at_heading: true
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.10.3
kernelspec:
  display_name: Python 3
  language: python
  name: python3
---

Vous allez maintenant mettre en oeuvre l'utilisation de l'écart normalisé et de la régression linéaire pour comparer les valeurs expérimentales avec la valeur théorique.

+++

# (TP) Utilisation d'une régression linéaire. (1h)
Cette partie est relativement libre __mais il faudra changer et ajouter beaucoup d'éléments__. Vous allez utiliser la cellule suivante pour réaliser une régression linéaire à partir de la relation $d = c \Delta t$. Vous devrez :
* Vérifier la compatibilité avec le modèle linéaire par régression linéaire et tracé graphique (pensez aux écarts normalisés)
* Estimer ainsi la célérité et son incertitude au moyen d'une simulation de Monte-Carlo sur la régression linéaire.
* Comparer la valeur estimée aux attentes.

Pensez à utiliser [l'exemple complet](https://pcsi3physiquestan.github.io/tp_incertitude/notebook/exemple.html) pour écrire le code adéquat.

```{code-cell}
"""
------- MODULES UTILES -----------
N'oubliez pas d'importer les bibliothèques utiles. Toutes ne sont pas importées.
"""
import numpy as np

"""
------- DONNEES EXPERIMENTALES -----------
Pensez à changer les valeurs des données expérimentales. Les suivantes sont fictives
"""

d = np.array([10, 20, 30, 40, 50, 60, 70, 80])  # Liste des distances E-R (en cm - évitez les nombres trop petits)
ud = np.array([0.15, 0.26, 0.16, 0.26, 0.14, 0.12, 0.41, 0.32])  # Liste des incertitudes sur d
dt = np.array([30, 60, 90, 120, 150, 180, 210, 240])  # Liste des temps de vol (en ms)
udt = np.array([5.4, 5.8, 4.6, 6.3, 8.3, 10, 5.1, 3.2])  # Liste des incertitudes sur Delta t

"""
------- LOI COMPATIBLE A L'OEIL -----------
Commencez par tracer un graphique approprié pour vérifier à l'oeil si le modèle attendue est possible.
"""






"""
------- AJUSTEMENT LINEAIRE -----------
Vous devez réaliser un ajustement linéaire et en déduire une valeur des paramètres
(pente et ordonnées à l'origine) AVEC LEUR INCERTITUDE par méthode de Monte-Carlo.
Vous devez dans l'ordre :
- dans une boucle, créer directement un vecteur de N simulations pour d et dt pour le binome i
et stocker ce vecteur dans une listes (un élément de la liste = un binôme)
- dans une seconde boucle, sélectionner les échantillons k de chaque binômes
et faire la régression linéaire avec ces échantillons. Stocker pente, ordonnée
à l'origine et valeur de célérité dans un vecteur de taille N créé au préalable.
- Calculer la moyenne et l'écart-type de la pente, de l'ordonnée à l'origine, de la célérité
pour avoir les valeurs estimées et leur incertitude.
"""
N = 10000
n_bin = len(d)  # Nombre de binômes











"""
------- TEST DE COMPATIBILITE DU MODELE -----------
1. Vérifier par un tracé graphique que la droite ajustée passe par les croix d'incertitude
2. Vérifier par un tracé graphique que tous les écarts normalisés entre
les valeurs expérimentales et les valeurs ajustées sont inférieurs à 2
"""



"""
------- TEST DE COMPATIBILITE DE C -----------
Vérifier par un calcul d'écart normalisé que la valeur estimée de la célérité
est compatible avec les données théoriques.
"""

```