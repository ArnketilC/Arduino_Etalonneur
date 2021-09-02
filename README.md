# Arduino-Etalonneur
Code Arduino pour étalonneur SENSY.
## Upload the software

-------
### Matériel
* PC
* 1 cable usb B male -> usb
* IDE Arduino (https://www.arduino.cc/en/software)

### Step by step
* Brancher le cable usb
* Ouvrir  _sketch_eltalonneur.ino_ dans l'ide arduino
* Dans le menu _outil_ sélectionner : 
    * Type de carte
    * Processeur
    * Port de communication
* Cliquer sur la flèche -> Téléverser

## Diagnostique
---------
Petit code pour faire le diagnostique du système.
### Matériel

* 1 second arduinos mega
* 1 cable usb B male -> usb
* 2 fils compatible pin arduino

### Step by step
* Connecter l'arduino connecters les arduinos de la façon suivante : 
    Arduino 1 | Arduino 2
    
    --------|--------
    Rx1 | Tx1
    Tx1 | Rx1
    
* Uploader _sketch_serial.ino_ dans le second arduino mega
* Ouvrir le moniteur série en utilisant la loupe (baud rate 9600)

### Interpreter
L'arduino mega d'interface devrait renvoyer:

    "I read the value: {value}, next."

Voir code pour plus de détails sur la structure de la string.
