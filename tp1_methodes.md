---
jupytext:
  encoding: '# -*- coding: utf-8 -*-'
  formats: ipynb,md:myst
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

# Méthodes expérimentales

Dans cette séquence, vous aller apprendre à :
1. Organiser une manipulation autour des trois axes : protocole, observation, exploitation.
2. Estimer l'incertitude d'un mesurande
3. Rendre compte de résultat sous différentes formes.
4. Utiliser certaines méthodes courantes d'exploitation des données

Cette séquence sera basée sur la détermination de la célérité des ultrasons dans l'air à température et pression ambiante.

__Compétences mises en jeu :__

ATTENTION : Les compétences mises en jeu ici sont transverses et seront réutilisées dans tous les TPs.

| Compétences | Je sais de quoi ça parle | Je peux explier la méthode | Je sais l'appliquer |
|:------------| :-:|:-:|:-:|
|Identifier les sources d'incertitude (opérateur, environnement, instruments, méthode)||||
|Procéder à l'évaluation d'une incertitude-type par une approche statistique (Type A)||||
|Procéder à l'évaluation d'une incertitude-type par une autre approche que statistique (Type B)||||
|Simuler un processus aléatoire permettant de caractériser la variabilité d'une grandeur composée (Monte-Carlo)||||
|Ecrire, avec un nombre adapté de chiffres significatifs, le résultat d'une mesure||||
|Comparer deux valeurs dont les incertitudes-types sont connues à l'aide de leur écart normalisé.||||
|Utiliser une méthode de régression linéaire afin d'obtenir les valeurs des paramètres du modèle.||||
|Procéder à la validation d'un modèle ajusté graphiquement ou par les écarts normalisés.||||
|Mesurer une longueur d’onde acoustique à l’aide d’un support gradué et d’un oscilloscope bicourbe.||||
|Mesurer la célérité d'une onde||||
