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
Le projet a été développé et testé principalement sous **Fedora**, mais il reste compatible avec les autres distributions Linux (comme Ubuntu/Debian) disposant des outils de compilation standard.

### 2. Installation de Git LFS (Obligatoire)
Le dépôt contient des fichiers lourds, des binaires et les dossiers `obj`, `tina` et `models` gérés via **Git LFS**. Vous devez l'installer avant de cloner le dépôt :

- **Sur Fedora :**
  ```bash
  sudo dnf install git-lfs
  git lfs install
  ```

### 3. Clonage
```bash
git pull lfs
```

### 4. Outils pour la modélisation
Installation indispensable pour lancer le logiciel de modélisation TINA :
```bash
sudo dnf install libXScrnSaver
```

### 5. Bonus
En cas d'ajout de fichiers lourds (comme des modèles avec Tina dans `models/`) :
```bash
git lfs track "dossier_ou_type/*"
git add .gitattributes
git add <vos_fichiers_lourds>
git commit -m "Ajout de fichiers via Git LFS"
git lfs push origin main
git push origin main
```

---

## ⚙️ Compilation

Le projet dispose d'un Makefile personnalisé permettant de gérer la compilation ciblée et d'isoler les objets :
```bash
make -f Makefile
```
