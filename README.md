# 🏆 LanParty - Tournament Manager

O aplicație complexă dezvoltată în **C** pentru gestionarea unei competiții de gaming. Proiectul utilizează structuri de date avansate pentru a procesa echipele, a simula meciurile și a genera clasamente finale.

---

## Structura Proiectului

Proiectul este împărțit în trei module principale pentru o organizare eficientă:

* **`lanParty.c`**: Punctul central al programului. Gestionează fluxul de execuție, fișierele de I/O și apelarea task-urilor.
* **`functii_folositoare.c`**: "Motorul" aplicației. Conține implementările pentru liste, stive, cozi și arbori (BST/AVL).
* **`header.h`**: Definirea structurilor de date și prototipurile funcțiilor utilizate.

---

## Task-uri Implementate

### 1️ Gestiunea Echipelor
* Deschiderea și validarea fișierelor de date.
* Citirea informațiilor despre echipe și jucători.
* Introducerea datelor într-o **listă simplu înlănțuită**.
* Afișarea listei complete în fișierul de ieșire.

### 2️ Filtrarea Participanților
* Eliminarea echipelor cu punctajul cel mai mic până când numărul total devine o **putere a lui 2**.
* Verificarea puterii lui 2 se realizează eficient prin **operații pe biți**.
* Afișarea echipelor rămase pentru faza de concurs.

### 3️ Simularea Competiției
* **Cozi (Queues):** Organizarea meciurilor între echipe.
* **Stive (Stacks):** Distribuirea automată în stiva de *Câștigători* și stiva de *Pierzători*.
* **Update Scor:** Fiecare jucător din echipa câștigătoare primește +1 punct.
* **Top 8:** Extragerea ultimelor 8 echipe rămase pentru fazele finale.

### 4️ Clasament BST
* Construirea unui **Arbore Binar de Căutare (BST)** folosind echipele din Top 8.
* Afișarea arborelui pentru vizualizarea ierarhiei.

### 5️ Ierarhia de Elită (AVL)
* Crearea unui **Arbore AVL** (auto-echilibrat) prin inserarea datelor din BST.
* Afișarea nodurilor de pe **nivelul 2** al arborelui AVL.

---

## Structuri de Date Utilizate

* **Liste:** Pentru stocarea dinamică a echipelor.
* **Cozi & Stive:** Pentru logica fluxului de meciuri.
* **Arbori (BST & AVL):** Pentru sortare și organizare ierarhică eficientă.
* **Gestiune Memorie:** Funcții dedicate de `free` pentru a preveni memory leak-urile.

---

## Compilare și Rulare

Pentru a compila și rula proiectul, folosește următoarele comenzi în terminal:

```bash
# Compilare
gcc lanParty.c functii_folositoare.c -o lanParty

# Executție
./lanParty c.in d.in r.out
