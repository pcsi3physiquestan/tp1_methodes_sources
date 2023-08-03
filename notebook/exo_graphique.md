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

La page ci-présente existe en version notebook téléchargeable grâce au bouton ![Bouton](./images/bouton_tl.png) (choisir le format `.ipynb`). On rappelle qu'l faut ensuite l'enregistrer dans un répertoire adéquat sur votre ordinateur (`tp1` par exemple dans votre répertoire personnel) puis lancer Jupyter Notebook depuis Anaconda pour accéder au notebook, le modifier et exécutez les cellules de code adéquates.


+++

# (TP) Application au tracé graphique (1h)

+++

## Analyse de la relation durée-distance

+++

### Votre travail
Vous aller devoir exploiter non plus une mesure de temps de vol pour une distance émetteur-récepteur mais regrouper l'ensemble de résultats de mesure
des groupes de TP pour affiner votre mesure de la célérité.

Pour pouvoir tester votre code, des données expérimentales __fictives__ sont entrées dans la cellule suivante.
En TP, vous récupérerez l'ensemble des données de mesure des différents binômes et modifierez ces listes.

```{code-cell}
:tags: [remove-output, hide-input]
import numpy as np  # Pensez à l'alias de la bibliothèques numpy pour la suite.
import matplotlib.pyplot as plt
"""Données expérimentales

Pensez à entre les 4 listes dans le même ordre.
"""
d = np.array([10, 20, 30])  # Liste des distances E-R (en cm - évitez les nombres trop petits)
ud = np.array([0.15, 0.26, 0.16])  # Liste des incertitudes sur d
dt = np.array([30, 60, 90])  # Liste des temps de vol (en ms)
udt = np.array([5.4, 5.8, 4.6])  # Liste des incertitudes sur Delta t
```


### C'est à vous.

+++

#### Codage
C'est à vous de coder maintenant la cellule suivante est entièrement à votre disposition. Vous devez obtenir en sortie
le graphique représentant $\Delta t$ en fonction $d$.

Pensez bien :
* aux légendes du graphiques
* aux barres d'incertitudes

_On rappelle que les vecteurs contenant les données ont déjà été créé dans la première cellule : `d, ud, dt, udt`. Pensez à utiliser le [modèle](https://pcsi3physiquestan.github.io/intro_python/notebook/plt_presentation.html#un-exemple-basique)._

```{code-cell}
:tags: [remove-output, hide-input]
"""Votre code

A vous de coder le graphique à tracer.
"""
# Créer la fenêtre graphique avec subplots

# Donner un titre (f.suptitle) et des légendes (ax.set_xlabel et ax.set_ylabel)

# Tracer la courbe Delta t (D) avec errorbar

# Afficher une grille (ax.grid) et afficher le graphique (plt.show)
```

#### Première analyse des données.
Lorsque vous aurez obtenu le graphique des données expérimentales réelles, analysez le :

* Que cherche-t-on à observer ?
* Observe-t-on ce qu'on attend ?
* Si oui, tant mieux, sinon essayez de comprendre où sont les problèmes.

Ecrire alors le compte-rendu de votre analyse.

+++



## (TP) Détermination des valeurs de la célérité

Quand on est face à une série de mesures, il y a deux analyses à réaliser en général:
* déterminer une mesure basées sur la série. On peut utiliser plusieurs méthodes mais on va ici simplement utiliser un calcul de moyenne des valeurs. On peut alors estimer l'incertitude de mesure comme étant l'incertitude sur la moyenne d'un échantillon.
* Vérifier (au moins _a posteriori_) que les mesures sont cohérentes entre elles (plus simplement ici avec la moyennes estimées).
+++

### Estimation de la célérité.
Cette partie va nous amener:
1. à estimer la célérité pour chaque couple de mesure. 
2. à réaliser ensuite la moyenne des mesures. 
3. à estimer l'incertitude comme pour un étude statistique (Type A):

$$
u(c_{moy}) = \frac{\sigma(echantillon)}{\sqrt{nombre_echantillons}}
$$
où $sigma$ est l'écart-type statistique calculé sur la série de mesures (réelles ici et non simulées !).

Détecter et modifier les lignes lorsque c'est nécessaire.


```{code-cell}
:tags: [remove-output, hide-input]
"""
Estimation des celerites pour chaque mesures
"""
c_ms = [0] * len(d)  # d et dt sont des vecteurs numpy : pensez à utiliser la vectorialisation.

"""
Calculer la célérité moyenne.
Utiliser la fonction np.mean(vecteur:ndarray) -> float pour calculer une moyenne en une seule ligne.
"""
c_mean = 0

"""
Calculer l'incertitude sur c_mean en utilisant la relation donnée.
On rappelle quie l'écart-type se calcule avec la fonction numpy.std(echantillon: ndarray, ddof=1) -> float
"""
c_u = 0

print("c = {} +/-".format(c_mean, c_u))
```

__Rendre compte de la valeur estimée en n'oubliant pas l'unité et la réflexion sur les chiffres significatifs.__

### Test de cohérence des données.
Pour tester la cohérence des données, on va tester la cohérence entre la mesure de $c$ pour chaque échantillon et la moyenne précédente. On connait déjà une méthode pour le faire : un calcul d'écart normalisé. Ainsi, on pourra, si nécessaire écarter ou au moins commenter une mesure qui semblerait incohérente.

On possède déjà les mesures des célérités `c_ms`, la célérité moyenne `c_mean` et son incertitude `c_u`, il manque l'incertitude sur mesure unique de célérité. On va reprendre la même méthode que pour la mesure unique de la partie précédente, mais pour gagner du temps, on part directement de $d, u(d), \Delta t, u(\Delta t)$ donnée et on va __utiliser des distributions uniformes.__ Donc:
1. On boucle sur le nombre d'échantillons:
    1. On simule N valeurs de $d$ et $\Delta t$ pour le j-ième échantillon et on en déduit N valeurs de c puis son incertitude. (Utiliser la méthode 3 qui est beaucoup plus rapide).
    2. On stocke l'incertitude obtenue dans une liste `c_us` qu'on aura préalablement initialisée.
    3. On calculer l'écart-normalisé entre le j-ième échantillon et la moyenne qu'on stocke dans une liste `en_s`
2. On représente les valeurs des écarts normalisés sur un graphique qu'on analuse ensuite.

```{code-cell}
:tags: [remove-output,hide-input]
"""
A vous de compléter la boucle en vous aidant de ce qui a été fait pour une mesure unique.
"""

c_us = []
en_s = []
k = len(d)  # Nombre d'échantillons
for j in range(k):
    """ Simuler les valeurs de d et dt puis estimer c et l'incertitude"""

    c_uj = 0
    c_us.append(c_uj)
    """Calculer l ecart normalise a la moyenne"""
    en_j = 0
    en_s.append(en_j)

print(en_s)  # Pour vérifier ce qu'il y a dedans

"""Tracé eds écart normalisés"""
f, ax = plt.subplots()
f.suptitle("Coherence des differentes mesures")
ax.set_xlabel("Distance (d) (cm)")
ax.set_ylabel("EN")

ax.plot(d, en_s, marker="+", linestyle="")  # On ne relit pas les points

ax.grid()
plt.show()
```

### Analyse des données
Réalisez une analyse des valeurs obtenues pour chaque groupe puis de la célérité moyenne en comparaison avec la valeur donnée dans la littérature.


### Bonus : Carte de controle
On pourrait, au lieu de tracer les ecarts normalisés, tracer une carte de controle qu représente les barres d'incertitudes et la moyenne (avec son incertitudes). Cette méthode est plus visuelle mais attention car les impressions ne correspondent pas tout à fait à ce que donne les EN (cf. TP).

```{code-cell}
:tags: [remove-output,hide-input]

f, ax = plt.subplots()
f.suptitle("Carte de controle des mesures")
ax.set_xlabel("Distance (d) (cm)")
ax.set_ylabel("EN")

# capsize sert à ajouter des barres aux extrémités simplement par esthétisime.
ax.errorbar(d, c_ms, marker="+", linestyle="", yerr=c_us, capsize=2)  # On ne relit pas les points

print(len([c_mean - c_u] * len(d)))
ax.plot(d, [c_mean] * len(d))  # Tracé de la moyenne
ax.plot(d, [c_mean - c_u] * len(d), linestyle=":")  # Valeur basse de l'intervalle associée à l'incertitude sur c_mean
ax.plot(d, [c_mean + c_u] * len(d), linestyle=":")  # Valeur haute de l'intervalle associée à l'incertitude sur c_mean


plt.show()

```