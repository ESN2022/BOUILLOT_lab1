# BOUILLOT_lab1

Sommaire :

a. Introduction

b. System architecture with QSYS components and their interaction, HW blocks, design choices

c. Conclusion, progress and result

### Introduction

Dans ce premier lab, je vais mettre en application le cours d'esn 10 en réalisant un flow complet de conception à travers un exemple assez
simple : il s'agit d'un chenillard. Ce programme va venir allumer et etteindre plusieurs Leds présente sur notre cible de manière à créer une
"chenille de lumière". La cible pour ce lab est une carte de développement DE10-Lite contenant un FPGA Max10 que l'on viendra configurer sur Quartus
(nous prendrons la version 18.1 pour limiter les bugs). L'ensemble de ce lab va allors mettre en lumière qu'un programme d'apparence basique peut se
réveller beaucoup plus compliqué que prévu notaament avec l'utilisation des périphériques tels que les Leds (permettant d'afficher le chenillard), 
les boutons poussoirs et enfin les switchs. Tous ces périphériques vont alors être amené à communiquer avec le FPGA amenant parfois à quelques conflits.

### System architecture
1-- Configuration du projet sous Quartus

Dans un premier temps, on va venir configurer Quartus à notre cible. Pour cela, on va venir entrer le modèle du FPGA dans Quartus lors de la création de 
notre nouveau project wizzard.
![image](https://user-images.githubusercontent.com/121939768/211576860-034593fd-edbd-4765-896f-a611ebca1268.png)

Quartus est maintenant configuré pour notre cible. Pour effectué ce premier exercice, il nous faut plusieurs choses, notamment un Nios2 et ses périphériques
permettant la gestion des boutons et des Leds. Tout cela est donc configuré sous Platform Designer via l'intégration d'IP (Intellectual properties). J'ai 
alors utilisé :
 - Nios 2
 - Clock (cadencera toute la carte)
 - Onchip memory (mémoire qui permettra d'avoir notre soft)
 - Jtag (permettant l'intérraction avec la cible)
 - 3 PIO
Les 3 PIO vont permettre de gérer nos entrée-sorties avec le premier permettant de gérer les sorties, les deux derniers permettant la gestion des entrées. 
Le montage final sur Platform Designer est le suivant :
![image](https://user-images.githubusercontent.com/121939768/211581020-386ebe2c-e44b-4f15-a099-31b3c6954899.png)

Chaque bloc (ou IP) possède une fonctionnalité spécifique sur notre cible. Comme expliqué précedemment, le bloc Clock va venir définir la cadence de communication entre chaque bloc et au sein d'un même bloc. Le Nios2 est le softcore que l'on va programmer sur le FPGA et qui va venir éxecuter notre script en C. Le Onchip Memory va venir sauvegarder notre soft avec toutes ses variables et bibliothèques. Enfin les PIO sont créés pour raccorder les périphériques (boutons, switchs et Leds) avec le Nios.J'ai d'abord commencé par créé le chenillard sans actionneur à l'aide du premier PIO. Le PIO 0 est alors utilisé pour gérer les sorties (soit l'allumage des Leds). 
Il ne faut pas oublier de paramétrer les broches du FPGA via Pin planer. J'ai alors cherché dans la datasheet de la carte DE10-Lite qulles broches correspond la clock, le reset et enfin les Leds.

![image](https://user-images.githubusercontent.com/121939768/211594484-83545a5f-690b-47a9-93b1-348d7c277c79.png)

Ainsi la vidéo suivante montre le fonctionnement du chenillard.

https://user-images.githubusercontent.com/121939768/211591566-910c652c-735b-41a7-86a2-a1ca4c984cd1.mov

2-- Gestion de la vitesse du chenillard

![image](https://user-images.githubusercontent.com/121939768/211847682-d80ade8b-1514-4c5f-a955-81068b2ee8e2.png)

Une fois cette fonction comprise et fonctionnelle, j'ai commencé à modifier la fonction usleep me permettant de gérer la durée d'allumage des leds 
(et donc la vitesse du chenillard). Deux méthodes peuvent alors être utilisée : soit par scrutation (pulling) ou par interruption. Aussi pour gérer les entrées générées par les switchs, un autre PIO doit être ajouté à Platform Designer.
![image](https://user-images.githubusercontent.com/121939768/211593754-cd00b4fa-7adb-49b5-9c71-c25246c9271e.png)

Il faut alors retourner sous Pin planer pour assigner les nouvelles broches du FPGA.
![image](https://user-images.githubusercontent.com/121939768/211594844-37b05c0d-f041-4e59-ba3a-fabdff8599e4.png)

Comme les switchs sont réalisés en pulling, le chenillard doit revenir au début pour prendre en compte la modification de vitesse. Le principe du pulling est que le programme va aller intérroger le périphérique sur son état espacé d'un temps précis. Malheureusement, la vidéo est trop longue et je ne peux pas l'uploader sur ce rapport.

Afin de pouvoir prendre en compte plus rapidement le changement de vitesse, je choisis d'utiliser le PIO en interruption. Je modifie donc le PIO 1 sur Platforme designer :

![image](https://user-images.githubusercontent.com/121939768/211602239-bb84ab33-87f2-4f0f-bbba-4f705a6b2997.png)

On vient alors spécifier que l'on choisis le mode d'interruption sur front et non sur niveau (pour éviter des problèmes de rebond des switch). Je choisis également de prendre sur front montant et descendant afin d'avoir une interruption qui m'informe que je suis repassé dans l'état de base (sans aucun switch). Cela va me permettre de définir une vitesse par défaut lorsqu'aucun switch est activé.
![image](https://user-images.githubusercontent.com/121939768/211602852-78ca8d5c-540b-491d-ba9e-bbcb7ba7754c.png)

On vient alors entrer le niveau d'interruption dans la colonne irq. Une fois cela effectuer on vient ajouter ce périphérique dans le vhdl et le fichier .c. Dans le fichier .c on vient spécifier qui porte l'interruption ainsi que la routine d'interruption à effectuer. Cela se fait via les commandes suivantes :

![image](https://user-images.githubusercontent.com/121939768/211603863-85401543-f2ba-4d3a-a6d9-10e692122a84.png)

A noter que ces macros sont incluse dans le fichier alt_irq.h qu'il faut alors inclure. (voir le main.c)
On peut alors voir que le chenillard change de vitesse en fonction du switch activé et qu'il n'a pas besoin de revenir au début pour changer de vitesse. On voit alors toute l'utilité des interruptions. 

https://user-images.githubusercontent.com/121939768/211765944-18b00004-7b51-41e3-a6db-1c2c605bfc30.mov

3-- Ajout d'un bouton poussoir

![image](https://user-images.githubusercontent.com/121939768/211847534-4094e2de-b75f-4b9d-a4d4-c0b5e9fcd8fa.png)

Enfin la dernière étape est d'ajouter un boutton qui va permettre le lancement (trigger) du chenillard. Plusieurs choix s'offre à nous : soit on ajoute une entrée au PIO 1 et on peut l'utiliser en pulling ou en interruption, soit créer un 3ème PIO que l'on pourra utiliser également en pulling et en interruption. En testant les deux façons, j'ai préféré utiliser un PIO séparé puisque, pour ma solution, il est mieux d'effectuer un pulling sur le bouton pour éviter de créer une interruption trop gourmande en temps (permettant la génération du chenillard) et possiblement blocante.
Il aurait alors fallu avoir 2 boutons sur ce PIO, le premier lançant le chenillard par une interruption et le second l'arrêtant. Cela aurait alors permis de bien choisir la vitesse du chenillard par interruption (voir la seconde vidéo).

A noter que pour ce dernier PIO il faut refaire le flow de developpement complet avec le Pin planner, le VHDL ainsi que le main. (voir codes)

![image](https://user-images.githubusercontent.com/121939768/211607119-547483a0-ce8a-444e-85ed-187f1bacc834.png)

Le fichier VHDL reprend alors toutes les connections hardware des PIO, clock et reset connectés au FPGA.

Voici une vidéo montrant le fonctionnement du boutton trigger :

https://user-images.githubusercontent.com/121939768/211772193-5c8eac64-8597-4229-9de5-53cf713102e3.MOV


### Conclusion, progress and result

Ma progression pour ce premier lab est la suivante :
 - Génération du chenillard
 - Gestion de la vitesse via switchs en pulling puis interruption
 - Ajout de la fonction trigger sur bouton poussoir

Ce lab m'a donc permis de comprendre comment dérouler un flow de conception du début à la fin, voir les différentes configuration que peut avoir un PIO (nottamment avec la gestion en pulling et en interruption). 
Quelques pièges dont j'ai dû faire attention sont les valeurs à mettre dans le switch case (permettant de gérer la vitesse). En effet, les switchs sont mappés en puissance de 2. Par exemple pour 4 switchs, le premier sera 0b0001 (soit 1), le second 0b0010 (soit 2), le troisième 0b0100 (soit 4) et ainsi de suite. 
Aussi à chaque modification sur Platform Designer, le flow entier de conception doit être regénéré avec les bon chemin d'accès. En passant d'un ordinateur à l'autre il faut également regénérer le Makefile.

Mes résultats ont été présentés tout au long de la présentation de l'architecture, et j'ai pu obtenir, à la fois en pulling et en interruption, la gestion du démarrage du chenillard ainsi que la gestion de sa vitesse, mais également le démarrage et le reset du système via les boutons poussoirs. J'ai néanmoins une préférence pour l'utilisation du bouton de trigger en pulling car, à mon sens, l'interruption serait beaucoup trop longue et bloquerait la gestion de la vitesse lorsque l'interruption apparaitrait.

En résumé, ce lab m'a permis de comprendre et mettre en application la démarche nécessaire au bon fonctionnement d'un système conçu pour être implanté en codesign.

