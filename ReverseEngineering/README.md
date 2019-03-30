# Reverse Engineering

## Durée - Duration
3 heures - 3 hours.

## Nombre de participants - Number of participants
2 participants.

## Description

Préparez vos désassembleurs et vos débogueurs, gences du royaume! Un appareil permettant d’ouvrir des portails vers les autres dimensions a été découvert et nous avons besoin de votre aide pour découvrir ses secrets! Tout ce que nous savons est que ce dernier possède un processeur ARM. Nous savons aussi que des services sont disponibles et pourrait même être exploitables! Nous avons le microgiciel mais nous ne pouvons réussir sans vous. Vous serez récompensés grandement pour vos efforts!

Outils: Ordinateur portable, désassembleur/décompilateur ARM, débogueur, langage de scripting de votre choix, Binwalk, QEMU. Une image Docker vous sera fournie si vous n’avez pas ces outils.

Get your disassemblers and debuggers ready ladies and gentlemen, a device capable of opening portals to new dimensions has been discovered and we need your help to uncover its mysteries! All we know is that’s running an ARM processor. Also, some services are running on it and some might even be exploitable! We extracted the firmware from it but can’t continue without you. You will be rewarded greatly for your hard work!

Tools: Laptop, ARM disassembler/decompiler, Debugger, Scripting language of your choice, Binwalk, QEMU. A docker image with all the needed tools will be handed if you don’t have them.

## Dashboard description

### English
Since The Great Split of 2003, portals to parallel worlds needed to be secured. The GreyBeards wizards forged a device that would lock those virtual pathways. It is time we unlock those portals once and for all. Problem is, the GreyBeards don’t want us to open them for everyone as they think it would cause chaos and break the system they have spent some much time perfecting. We successfully extracted the firmware from one of the portal but we need you to find the keys to the five locks embedded in each portal. 

You can find the firmware at: http://svieg.com/firmware.bin

If you need tools, we can provide some that we think could be useful in the following Dockerfile. Here is how to start it:

    sudo docker build . -t re
    sudo docker run -dt re
    sudo docker exec -it <id> /bin/bash

Beware, we can only guarantee the access to the portals for the next 3 hours so you will have to be fast. Good luck. 

### Français

Depuis la Grande Séparation, les portails menant aux mondes parallèles ont dû être protégés. Les sorciers GreyBeards ont alors fabriqués un appareil qui agit comme une serrure rendant les portails impossibles à traverser sauf pour ceux connaissant leurs secrets. Cependant, les GreyBeards ne veulent pas partager leur connaissance et croient que d’ouvrir ces portails serait une erreur qui apporterait chaos et misère à notre monde. Ce monde qu’ils ont bâti depuis des années. Nous avons réussi à extraire le micrologiciel d’un des portails mais nous avons besoin de votre aide pour trouver les clés aux 5 différentes serrures qui protègent les portails.

Vous pouvez trouver le micrologiciel à l’adresse suivante: http://svieg.com/firmware.bin

Si vous avez besoin d’outils, nous avons préparé un Dockerfile avec des outils que nous pensons qui pourrait vous être utiles. Voici comment y avoir accès:

    sudo docker build . -t re
    sudo docker run -dt re
    sudo docker exec -it <id> /bin/bash

Faites attention, nous pouvons seulement vous garantir l’accès aux portails pour les 3 prochaines heures donc vous devez faire vite. Bonne chance.


## Build

* Build with openwrt 18.06: https://git.openwrt.org/openwrt/openwrt.git
* `The SOURCE\_ROOT` environment variable should point to the root of this repository.
* Copy the `DecompressingAColdOneWithPoly/files` directory into your openwrt directory.
* The `config` file should be renamed to `.config` and moved to the root of the openwrt directory.
* make
* The compressed firmware (both ext4 and squashfs version) are in the `bin/targets/targets/brcm2708/bcm2709` directory of the openwrt directory.
* Decompress it: gunzip openwrt-brcm2708-bcm2709-rpi-2-ext4-factory.img.gz
* The ext4 version can be flashed to a microSD card with dd: ```dd if=bin/targets/targets/brcm2708/bcm2709/openwrt-brcm2708-bcm2709-rpi-2-ext4-factory.img of=/dev/mmcblk0 bs=2M conv=fsync```
* The squashfs version (`openwrt-brcm2708-bcm2709-rpi-2-squashfs-factory.img`) is the one the participants had.

## Dockerfile

```
sudo docker build . -t re
sudo docker run -dt re
sudo docker exec -it <id> /bin/bash
```
