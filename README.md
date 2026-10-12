# Traducteur de Modèles Réseaux de Petri vers C & VHDL

> **Projet SED (Systèmes à Événements Discrets) - Master 1 ISTR**  
> Outil de modélisation interactive et générateur automatique de code embarqué (C et VHDL) à partir de modèles Réseaux de Petri.

---

## 📌 Description du Projet

Ce projet propose une interface interactive permettant d'éditer, simuler et traduire des modèles de **Réseaux de Petri** en code exécutable pour systèmes embarqués :
- **Génération C** : Adaptée aux microcontrôleurs et systèmes temps réel.
- **Génération VHDL** : Adaptée à l'implémentation sur cibles matérielles (FPGA).

L'outil facilite le passage des modèles formels de conception (Réseaux de Petri) vers les modèles d'implémentation logicielle et matérielle.

---

## 📁 Structure du Projet

- `*.c / *.h` : Fichiers sources et en-têtes modifiables (`main.c`, `GenerateurCode.c`, `GenererLog.c`, etc.).
- `obj/` : Fichiers objets précompilés et compilés.
- `models/` : Répertoire contenant les fichiers de modèles `.ndr` / `.nd`.
- `moulinette.exe` : Exécutable généré à la racine.

---

## 🚀 Prérequis et Clonage

### 1. Système d'exploitation recommandé
Le projet a été développé et testé sous **Fedora**, il ne reste compatible qu'avec cette distribution de Linux en raison des fichiers pré-compilés.

### 2. Outils pour la modélisation
Installation indispensable pour lancer le logiciel de modélisation TINA :
```bash
sudo dnf install libXScrnSaver
./tina/bin/nd &
```
---

## ⚙️ Compilation

Le projet dispose d'un Makefile personnalisé permettant de gérer la compilation ciblée et d'isoler les objets :
```bash
make -f Makefile
```
