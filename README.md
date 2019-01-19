# Road Fighter
**Freek De Sagher <br> s0171876** 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
Travis CI: [![Build Status](https://travis-ci.com/FreekDS/ProjectGP.svg?token=oRQDqQmpkBiWswbK3qg5&branch=master)](https://travis-ci.com/FreekDS/ProjectGP)
___________________________________

#### Controls


Player movement:

| Action        | Key           |
| ------------- |:-------------:|
| accelerate    | SPACE         |
| move up       | ARROW UP      |
| move down     | ARROW DOWN    |
| move left     | ARROW LEFT    |
| move right    | ARROW RIGHT   |
| shoot         | X             |
Player controls zijn gemakkelijk aanpasbaar in [deze](https://github.com/FreekDS/ProjectGP/blob/master/SFMLgame/src/World.cpp) source file met behulp van de functie 
```cpp
void readInput() override;
```

General controls:

| Action        | Key           |
| ------------- |:-------------:|
| exit game <br>at any time | ESC |
| proceed when game<br> finished |ENTER|


#### Project Structure
Dit project is verdeeld in meerdere subfolders:<br>
1. De map *cmake*:
    + *Modules*
        + *FindSFML.cmake*: bestand gebruikt om te zoeken naar SFML op het systeem.
2. De map *gll* (= Game Logic Library) bevat de logica voor de game en is onderverdeeld als volgt:
    + De *include* map:
        + *GLL*: bevat alle headers gebruikt voor de game logic.
        + *lib*: bevat de headers van de gebruikte externe libraries. <br>
        Voor dit project is de [mINI library](https://github.com/pulzed/mINI) gebruikt. Dit is een parser voor .ini bestanden. Een .ini bestand wordt gebruikt om de scores in op te slaan.
    + De *src* map: deze bevat alle gebruikte source files voor de Game Logic.
    + *CMakeListst.txt* om de Game Logic te builden.
3. De map *SFMLgame* bevat de sources voor een uitvoerbare versie van de game en is onderverdeeld als volgt:
    + De *include* map bevat alle headers die nodig zijn voor de SFML implementatie.
    + De *res* map bevat alle resources (afbeeldingen, score file) van de game.
    + De *src* map bevat alle source files die nodig zijn voor de SFML implementatie.
    + *CMakeLists.txt* om de executable te builden.
    + *main.cpp* de main file van de executable.
4. De map *tests* bevat alle tests die gebaseerd zijn op het [Googletest Framework](https://github.com/google/googletest)
    + De *include* map bevat alle headers voor de tests.
    + De *src* map bevat alle source files van de tests.
    + *CMakeLists.txt* om de tests te builden.
    + *CMakeLists.txt.in* wordt in *CMakeLists.txt* gebruikt om googletest te linken aan het project.
    + *main.cpp* de main voor de tests.
5. Overige bestanden:
    + *.gitignore*
    + *.travis.yml*
    + *CMakeLists.txt* de root CMakeLists van dit project.
    + *Readme.md*: deze readme file.

#### Documentatie
De volledige documentatie bevindt zich [hier](https://freekds.github.io/ProjectGP/) en is gegenereerd aan de hand van Doxygen. 

De bestanden van deze documentatie zijn terug te vinden in de aparte branch *gh-pages*

