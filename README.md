# BOUILLOT_lab1

Report content :
a. Introduction
b. System architecture with QSYS components and their interaction, HW blocks, design choices
c. Progress, results
d. Conclusion: What have you learned, comment progress, pitfalls and solutions

### Introduction

Dans ce premier lab, je vais mettre en applicationn le cours d'esn 10 en réalisant un flow complet de conception à travers un exemple assez
simple : il s'agit d'un chenillard. Ce programme va venir allumer et etteindre plusieurs Leds présente sur notre cible de manière à créer une
"chenille de lumière. La cible pour ce lab est une carte de développement DE10-Lite contenant un FPGA Max10 que l'on viendra configurer sur Quartus
(nous prendrons la version 18.1 pour limiter les bugs). L'ensemble de ce lab va allors mettre en lumière qu'un programme d'apparence basique peut se
réveller beaucoup plus compliqué que prévu notaament avec l'utilisation des périphériques tels que les Leds (permettant d'afficher le chenillard), 
les boutons poussoirs et enfin les switchs. Tous ces périphériques vont alors être amené à communiquer avec le FPGA amenant parfois à quelques conflits.

### Architecture
1-- Configuration du projet sous Quartus

Dans un premier temps, on va venir configurer Quartus à notre cible. Pour cela, on va venir entrer le modèle du FPGA dans Quartus lors de la création de 
notre nouveau project wizzard.
![image](https://user-images.githubusercontent.com/121939768/211576860-034593fd-edbd-4765-896f-a611ebca1268.png)
