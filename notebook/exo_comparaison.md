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

# (TP) Complément : Utilisation d'une régression linéaire.
Cette partie est entièrement libre. Vous allez utiliser la cellule suivante pour réaliser une régression linéaire à partir de la relation $d = c \Delta t$. Vous devrez :
* Vérifier la compatibilité avec le modèle linéaire
* Estimer ainsi la célérité et son incertitude au moyen d'une simulation de Monte-Carlo.
* Comparer la valeur estimée aux attentes.

Pensez à utiliser [l'exemple complet](https://pcsi3physiquestan.github.io/tp_incertitude/notebook/exemple.html) pour écrire le code adéquat.