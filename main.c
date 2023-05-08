#include <stdio.h>
#include <stdlib.h>

/*
    --- Schiffe Versenken ---

    Erstelldatum: 03.05.2023

    Ersteller: Leon Dederer
    Version: 1.0 [FUNKTIONSFERTIG]

    Letzte Änderung: 08.05.2023

    - Schiffe platzieren Spieler 1                       ✓
    - Schiffe platzieren Spieler 2                       ✓
    - Spielablauf mit Schuss bis jemand 16 Punkte hat    ✓
    - Code kommentieren                                  ✓
    - Dauerpraktikant implementieren                     ✓
    - Gewinnerseite einbauen                             ✓
    - Gute Übersichtlichkeit beim Spielen gewährleisten  ✓
    - cmd-pause und cmd-cls für gute Übersicht einbauen  ✓
    - Aufrufen der Unterprogramme um Fehler zu vermeiden ✓

    Funktionsweise:
    Zunächst muss Spieler 1 angeben, wo das 2er Schiff
    platziert werden soll, danach kommt das nächste 2er
    Schiff, dann das 3er etc. Dasselbe muss nach Spieler 1
    auch Spieler 2 möglich sein. Wenn beide Spieler ihre
    Schiffe platziert haben, beginnt das Spiel. Zunächst
    muss es Spieler 1 möglich sein, ein Feld auszuwählen,
    auf das er schießen möchte. Wenn er trifft, bekommt
    er einen Punkt und darf erneut ein Feld beschießen.
    Wenn er nicht trifft, ist Spieler 2 an der Reihe und
    es geht genauso weiter. Dieser Ablauf wiederholt sich,
    bis ein Spieler 16 Treffer/Punkte erreicht hat. In
    diesem Fall ist das Spiel vorbei und es wird bekannt
    gegeben, wer gewonnen hat.
*/


// Globale Variablen:
char y; // Y Koordinate
int x; // X Koordinate
int vergleich = 1; // Variable damit if-verzweigungen nur 1 mal verwendet werden
char block1[10][10]; // Plazierte Schiffe von Spieler 1
char mainblock1[10][10]; // Getroffene Schiffe von Spieler 2
char block2[10][10]; // Plazierte Schiffe von Spieler 2
char mainblock2[10][10]; // Getroffene Schiffe von Spieler 1
char zeile; // Um die Buchstaben in der ersten zeile zu schreiben
char koortdinaten[3]; // Für die Koordinateneingabe von a1 bis j10
int punktSpieler1 = 0; // Punkte von Spieler 1
int punktSpieler2 = 0; // Punkte von Spieler 2
int laenge = 1; // Länge des Aktuell zu setzenden Schiffes (Wird in den jeweiligen if-verzweigungen umgestellt)

// Erstmaliges Aufrufen der Unterprogramme um Fehler zu vermeiden
void Spieler1Konfig();
void Spieler2Konfig();
void MainSpiel();
void Gewinner();

int main(){
    system("color 0a"); // Hintergrundfarbe und Schriftfarbe

    for (int i = 0; i <= 9; i++){ // erstmalig das Feld bauen für guten überblick
        for (int j = 0; j <= 9; j++){
            block1[j][i] = 'o';
            mainblock1[j][i] = 'o';
            block2[j][i] = 'o';
            mainblock2[j][i] = 'o';
        }
    }

    printf("Spieler 1 Schiffe Konfiguration\n\n"); // Spieler 1 darf seine Schiffe plazieren:
    system("pause");
    system("cls");

    Spieler1Konfig();

    printf("Spieler 2 Schiffe Konfiguration\n\n"); // Spieler 2 darf seine Schiffe plazieren:
    system("pause");
    system("cls");

    Spieler2Konfig();

    MainSpiel(); // Spiel ablauf mit Schuss bis jemand 16 treffer erzielt hat
    Gewinner(); // Gewinnerseite
}

void Spieler1Konfig(){
    char richtung; // Welche Richtung geht es (Norden, Osten, Süden oder Westen)

    // Wie viele von jedem Schiff noch gebraucht wird
    int zweier1 = 1;
    int zweier2 = 1;
    int dreier = 1;
    int vierer = 1;
    int fuenfer = 1;

    while(laenge != 5){ // Wird wiederhohlt bis das längste Schiff vergeben wurde
        if (zweier1 == 1){ // Welche Schifflänge wird benötigt:
            laenge = 2;
            zweier1 = 0;
        }
        else if (zweier2 == 1){
            laenge = 2;
            zweier2 = 0;
        }
        else if (dreier == 1){
            laenge = 3;
            dreier = 0;
        }
        else if (vierer == 1){
            laenge = 4;
            vierer = 0;
        }
        else if (fuenfer == 1){
            laenge = 5;
            fuenfer = 0;
        }

        back1: // Hier zurückgesetzt falls der gesetzte punkt schlecht gesetzt war
        system("cls"); // Ausgabe Löschen

        printf("%der Schiff:\n\n", laenge);

        printf("  "); // Leerzeichen damit die Zahlenreiche richtig positioniert ist

        for (int k = 1; k <= 10; k++){ // Zahlenreihe ausgeben
            printf("%d ", k);
        }

        // Felder ausgeben:
        for (int i = 0; i <= 9; i++){
            zeile = i + 97; // Buchstabe am rand
            printf("\n%c ", zeile); // Buchstabe am rand ausgeben

            for (int j = 0; j <= 9; j++){
                printf("%c ", block1[j][i]);
            }
        }

        while(1){ // Koordinateneingabe
            printf("\n\nAusgangspunkt Koordinate: ");
            scanf("%s", &koortdinaten); // Eingabe der Koordinaten XY

            sscanf(koortdinaten, "%c%d", &y, &x); // In koordinaten X und Y aufteilen

            if (x > 10 || y > 'j' || x <= 0 || y < 'a' || block1[x-1][y-97] == 'S'){
                printf("\nError (Koordinaten beachten)");
            }
            else {
                printf("\n");
                break;
            }
        }

        system("cls"); // Ausgabe Löschen

        printf("In welche Himmelsrichtung soll das Schiff zeigen?\n\n");

        for (int i = 0; i <= 9; i++){ // i == y
            if (vergleich == 1){
                printf("  ");

                for (int k = 1; k <= 10; k++){
                    printf("%d ", k);
                }

                vergleich = 2;
            }

            zeile = i + 97; // Zahl in ASCII umwandeln
            printf("\n%c ", zeile);

            for (int j = 0; j <= 9; j++){ // j == x
                if (j == x-1 && i == y-97){
                    block1[j][i] = 'X'; // Koordinate auf X setzen
                }

                printf("%c ", block1[j][i]);
            }
        }

        vergleich = 1;

        while(getchar()!='\n'); // Eingabepuffer zurücksetzen

        // Eingabe der richtung in n, o, s oder w
        while(1){
            printf("\n\nNach Norden(n), Osten(o), Sueden(s) oder Westen(w): ");
            scanf("%c", &richtung);

            if (richtung == 'n' || richtung == 'o' || richtung == 's' || richtung == 'w') {
                if (richtung == 'n' && (y-97)-laenge >= 0 || richtung == 'o' && (x-1)+laenge <= 9 || richtung == 's' && (y-97)+laenge <= 9 || richtung == 'w' && (x-1)-laenge >= 0){
                    break;
                }
                else {
                    printf("Error (waehle eine andere Richtung)");
                }
            }
            else {
                printf("Error (n, o, s oder w)\n");
            }

            while(getchar()!='\n'); // Eingabepuffer zurücksetzen
        }

        // Testen ob ein Schiff im Weg ist:
        if (richtung == 'n'){ // Wenn es nach Norden geht:
            for (int i = (y-97); i <= (y-97)-laenge; i--){ // j == x; i == y
                if (block1[x-1][i] == 'S'){
                    block1[x-1][y-97] = 'o';
                    printf("Error (waehle einen anderen Punkt)\n\nDruecke eine beliebige Taste um Fortzufahren...");
                    system("pause >NULL");
                    while(getchar()!='\n'); // Eingabepuffer zurücksetzen
                    goto back1;
                }
            }
        }
        else if (richtung == 'o'){ // Wenn es nach Osten geht:
            for (int j = (x-1); j <= laenge+(x-1); j++){ // j == x; i == y
                if (block1[j][y-97] == 'S'){
                    block1[x-1][y-97] = 'o';
                    printf("Error (waehle einen anderen Punkt)\n\nDruecke eine beliebige Taste um Fortzufahren...");
                    system("pause >NULL");
                    while(getchar()!='\n'); // Eingabepuffer zurücksetzen
                    goto back1;
                }
            }
        }
        else if (richtung == 's'){ // Wenn es nach Süden geht:
            for (int i = (y-97); i <= laenge+(y-97); i++){ // j == x; i == y
                if (block1[x-1][i] == 'S'){
                    block1[x-1][y-97] = 'o';
                    printf("Error (waehle einen anderen Punkt)\n\nDruecke eine beliebige Taste um Fortzufahren...");
                    system("pause >NULL");
                    while(getchar()!='\n'); // Eingabepuffer zurücksetzen
                    goto back1;
                }
            }
        }
        else if (richtung == 'w'){ // Wenn es nach Westen geht:
            for (int j = (x-1); j == laenge-(x-1); j--){ // j == x; i == y
                if (block1[j][y-97] == 'S'){
                    block1[x-1][y-97] = 'o';
                    printf("Error (waehle einen anderen Punktw)\n\nDruecke eine beliebige Taste um Fortzufahren...");
                    system("pause >NULL");
                    while(getchar()!='\n'); // Eingabepuffer zurücksetzen
                    goto back1;
                }
            }
        }

        system("cls"); // Ausgabe zurücksetzen

        printf("Spieler 1 Feld:\n\n");

        printf("  "); // Leerzeichen damit die Zahlenreiche richtig positioniert ist
        for (int k = 1; k <= 10; k++){ // Zahlenreihe ausgeben
            printf("%d ", k);
        }

        if (richtung == 'n'){ // Schiff nach Norden
            for (int i = 0; i <= 9; i++){ // i == y
            zeile = i + 97; // Zahl in ASCII umwandeln
            printf("\n%c ", zeile);

            if (laenge == 2){ // Wenn das Schiff 2 Felder groß ist
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-98){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen:
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            if (laenge == 3){ // Wenn das Schiff 3 Felder Groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-98 || j == x-1 && i == y-99){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            if (laenge == 4){ // Wenn das Schiff 4 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-98 || j == x-1 && i == y-99 || j == x-1 && i == y-100){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            if (laenge == 5){ // Wenn das Schiff 5 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-98 || j == x-1 && i == y-99 || j == x-1 && i == y-100 || j == x-1 && i == y-101){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            }
        }

        if (richtung == 'o'){ // Schiff nach Osten
            for (int i = 0; i <= 9; i++){ // i == y
            zeile = i + 97; // Zahl in ASCII umwandeln
            printf("\n%c ", zeile);

            if (laenge == 2){ // Wenn das Schiff 5 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x && i == y-97){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            if (laenge == 3){ // Wenn das Schiff 3 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x && i == y-97 || j == x+1 && i == y-97){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            if (laenge == 4){ // Wenn das Schiff 4 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x && i == y-97 || j == x+1 && i == y-97 || j == x+2 && i == y-97){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            if (laenge == 5){ // Wenn das Schiff 5 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x && i == y-97 || j == x+1 && i == y-97 || j == x+2 && i == y-97 || j == x+3 && i == y-97){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            }
        }

        if (richtung == 's'){ // Schiff nach Süden
            for (int i = 0; i <= 9; i++){ // i == y
            zeile = i + 97; // Zahl in ASCII umwandeln
            printf("\n%c ", zeile);

            if (laenge == 2){ // Wenn das Schiff 2 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-96){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            if (laenge == 3){ // Wenn das Schiff 3 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-96 || j == x-1 && i == y-95){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            if (laenge == 4){ // Wenn das Schiff 4 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-96 || j == x-1 && i == y-95 || j == x-1 && i == y-94){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            if (laenge == 5){ // Wenn das Schiff 5 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-96 || j == x-1 && i == y-95 || j == x-1 && i == y-94 || j == x-1 && i == y-93){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            }
        }

        if (richtung == 'w'){ // Schiff nach Westen
            for (int i = 0; i <= 9; i++){ // i == y
            zeile = i + 97; // Zahl in ASCII umwandeln
            printf("\n%c ", zeile);

            if (laenge == 2){ // Wenn das Schiff 2 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-2 && i == y-97){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            if (laenge == 3){ // Wenn das Schiff 3 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-2 && i == y-97 || j == x-3 && i == y-97){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            if (laenge == 4){ // Wenn das Schiff 4 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-2 && i == y-97 || j == x-3 && i == y-97 || j == x-4 && i == y-97){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            if (laenge == 5){ // Wenn das Schiff 5 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-2 && i == y-97 || j == x-3 && i == y-97 || j == x-4 && i == y-97 || j == x-5 && i == y-97){
                        block1[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block1[j][i]);
                }
            }
            }
        }

        if (laenge == 5){ // Wenn die länge erreicht wurde dann stoppe den Code für mehr übersicht
            printf("\n\n");
            system("pause");
        }
        system("cls");
    }
}

void Spieler2Konfig(){
    char richtung; // Welche Richtung geht es (Norden, Osten, Süden oder Westen)

    // Wie viele von jedem Schiff noch gebraucht wird
    int zweier1 = 1;
    int zweier2 = 1;
    int dreier = 1;
    int vierer = 1;
    int fuenfer = 1;
    int laenge = 1;

    while(laenge != 5){ // Wird wiederhohlt bis das längste Schiff vergeben wurde
        if (zweier1 == 1){// Hier wird getestet welche länge dran ist
            laenge = 2;
            zweier1 = 0;
        }
        else if (zweier2 == 1){
            laenge = 2;
            zweier2 = 0;
        }
        else if (dreier == 1){
            laenge = 3;
            dreier = 0;
        }
        else if (vierer == 1){
            laenge = 4;
            vierer = 0;
        }
        else if (fuenfer == 1){
            laenge = 5;
            fuenfer = 0;
        }

        back2:
        system("cls");

        printf("%der Schiff:\n\n", laenge);

        printf("  "); // Leerzeichen damit die Zahlenreiche richtig positioniert ist

        for (int k = 1; k <= 10; k++){ // Zahlenreihe ausgeben
            printf("%d ", k);
        }

        // Felder ausgeben:
        for (int i = 0; i <= 9; i++){
            zeile = i + 97; // Buchstabe am rand
            printf("\n%c ", zeile); // Buchstabe am rand ausgeben

            for (int j = 0; j <= 9; j++){
                printf("%c ", block2[j][i]);
            }
        }

        while(1){
            printf("\n\nAusgangspunkt Koordinate: ");
            scanf("%s", &koortdinaten); // Eingabe der Koordinaten XY

            sscanf(koortdinaten, "%c%d", &y, &x); // In koordinaten X und Y aufteilen

            if (x > 10 || y > 'j' || x <= 0 || y < 'a' || block2[x-1][y-97] == 'S'){
                printf("\nError (Koordinaten beachten)");
            }
            else {
                printf("\n");
                break;
            }
        }

        system("cls"); // Ausgabe Löschen
        printf("In welche Himmelsrichtung soll das Schiff zeigen?\n\n");

        for (int i = 0; i <= 9; i++){ // i == y
            if (vergleich == 1){
                printf("  ");

                for (int k = 1; k <= 10; k++){
                    printf("%d ", k);
                }

                vergleich = 2;
            }

            zeile = i + 97; // Zahl in ASCII umwandeln
            printf("\n%c ", zeile);

            for (int j = 0; j <= 9; j++){ // j == x
                if (j == x-1 && i == y-97){
                    block2[j][i] = 'X'; // Koordinate auf X setzen
                }

                printf("%c ", block2[j][i]);
            }
        }

        vergleich = 1;

        while(getchar()!='\n'); // Eingabepuffer zurücksetzen

        while(1){
            printf("\n\nNach Norden(n), Osten(o), Sueden(s) oder Westen(w): ");
            scanf("%c", &richtung);

            if (richtung == 'n' || richtung == 'o' || richtung == 's' || richtung == 'w') {
                if (richtung == 'n' && x-1 >= 0 && x-1 <= 9 && y-(96+laenge) >= 0 && y-(96+laenge) <= 9 || richtung == 'o' && (x-1+laenge) >= 0 && x-(1+laenge) <= 9 && y-97 >= 0 && y-97 <= 9 || richtung == 's' && x-1 >= 0 && x-1 <= 9 && y-(97-laenge) >= 0 && y-(97-laenge) <= 9 || richtung == 'w' && x-(1+laenge) >= 0 && x-(1+laenge) <= 9 && y-97 >= 0 && y-97 <= 9){
                    break;
                }
                else {
                    printf("Error (waehle eine andere Richtung)\n");
                }
            }
            else {
                printf("Error (n, o, s oder w)\n");
            }

            while(getchar()!='\n'); // Eingabepuffer zurücksetzen
        }

        // Testen ob ein Schiff im Weg ist:
        if (richtung == 'n'){ // Wenn es nach Norden geht:
            for (int i = (y-97); i >= laenge-(y-97); i--){ // j == x; i == y
                if (block2[x-1][i] == 'S'){
                    block2[x-1][y-97] = 'o';
                    printf("Error (waehle einen anderen Punkt)\n\nDruecke eine beliebige Taste um einen neuen Punkt auszuwaehlen...");
                    system("pause >NULL");
                    while(getchar()!='\n'); // Eingabepuffer zurücksetzen
                    goto back2;
                }
            }
        }
        else if (richtung == 'o'){ // Wenn es nach Osten geht:
            for (int j = (x-1); j <= laenge+(x-1); j++){ // j == x; i == y
                if (block2[j][y-97] == 'S'){
                    block2[x-1][y-97] = 'o';
                    printf("Error (waehle einen anderen Punkt)\n\nDruecke eine beliebige Taste um Fortzufahren...");
                    system("pause >NULL");
                    while(getchar()!='\n'); // Eingabepuffer zurücksetzen
                    goto back2;
                }
            }
        }
        if (richtung == 's'){ // Wenn es nach Süden geht:
            for (int i = (y-97); i <= laenge+(y-97); i++){ // j == x; i == y
                if (block2[x-1][i] == 'S'){
                    block2[x-1][y-97] = 'o';
                    printf("Error (waehle einen anderen Punkt)\n\nDruecke eine beliebige Taste um Fortzufahren...");
                    system("pause >NULL");
                    while(getchar()!='\n'); // Eingabepuffer zurücksetzen
                    goto back2;
                }
            }
        }
        else if (richtung == 'w'){ // Wenn es nach Westen geht:
            for (int j = (x-1); j >= laenge-(x-1); j--){ // j == x; i == y
                if (block2[j][y-97] == 'S'){
                    block2[x-1][y-97] = 'o';
                    printf("Error (waehle einen anderen Punkt)\n\nDruecke eine beliebige Taste um Fortzufahren...");
                    system("pause >NULL");
                    while(getchar()!='\n'); // Eingabepuffer zurücksetzen
                    goto back2;
                }
            }
        }

        system("cls"); // Ausgabe zurücksetzen

        printf("Spieler 2 Feld:\n\n");

        printf("  "); // Leerzeichen damit die Zahlenreiche richtig positioniert ist
        for (int k = 1; k <= 10; k++){ // Zahlenreihe ausgeben
            printf("%d ", k);
        }

        if (richtung == 'n'){ // Schiff nach Norden
            for (int i = 0; i <= 9; i++){ // i == y
            zeile = i + 97; // Zahl in ASCII umwandeln
            printf("\n%c ", zeile);

            if (laenge == 2){ // Wenn das Schiff 2 Felder groß ist
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-98){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen:
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            if (laenge == 3){ // Wenn das Schiff 3 Felder Groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-98 || j == x-1 && i == y-99){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            if (laenge == 4){ // Wenn das Schiff 4 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-98 || j == x-1 && i == y-99 || j == x-1 && i == y-100){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            if (laenge == 5){ // Wenn das Schiff 5 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-98 || j == x-1 && i == y-99 || j == x-1 && i == y-100 || j == x-1 && i == y-101){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            }
        }

        if (richtung == 'o'){ // Schiff nach Osten
            for (int i = 0; i <= 9; i++){ // i == y
            zeile = i + 97; // Zahl in ASCII umwandeln
            printf("\n%c ", zeile);

            if (laenge == 2){ // Wenn das Schiff 5 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x && i == y-97){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            if (laenge == 3){ // Wenn das Schiff 3 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x && i == y-97 || j == x+1 && i == y-97){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            if (laenge == 4){ // Wenn das Schiff 4 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x && i == y-97 || j == x+1 && i == y-97 || j == x+2 && i == y-97){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            if (laenge == 5){ // Wenn das Schiff 5 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x && i == y-97 || j == x+1 && i == y-97 || j == x+2 && i == y-97 || j == x+3 && i == y-97){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            }
        }

        if (richtung == 's'){ // Schiff nach Süden
            for (int i = 0; i <= 9; i++){ // i == y
            zeile = i + 97; // Zahl in ASCII umwandeln
            printf("\n%c ", zeile);

            if (laenge == 2){ // Wenn das Schiff 2 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-96){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            if (laenge == 3){ // Wenn das Schiff 3 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-96 || j == x-1 && i == y-95){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            if (laenge == 4){ // Wenn das Schiff 4 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-96 || j == x-1 && i == y-95 || j == x-1 && i == y-94){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            if (laenge == 5){ // Wenn das Schiff 5 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-1 && i == y-96 || j == x-1 && i == y-95 || j == x-1 && i == y-94 || j == x-1 && i == y-93){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            }
        }

        if (richtung == 'w'){ // Schiff nach Westen
            for (int i = 0; i <= 9; i++){ // i == y
            zeile = i + 97; // Zahl in ASCII umwandeln
            printf("\n%c ", zeile);

            if (laenge == 2){ // Wenn das Schiff 2 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-2 && i == y-97){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            if (laenge == 3){ // Wenn das Schiff 3 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-2 && i == y-97 || j == x-3 && i == y-97){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            if (laenge == 4){ // Wenn das Schiff 4 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-2 && i == y-97 || j == x-3 && i == y-97 || j == x-4 && i == y-97){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            if (laenge == 5){ // Wenn das Schiff 5 Felder groß ist:
                for (int j = 0; j <= 9; j++){ // j == x
                    if (j == x-1 && i == y-97 || j == x-2 && i == y-97 || j == x-3 && i == y-97 || j == x-4 && i == y-97 || j == x-5 && i == y-97){
                        block2[j][i] = 'S'; // Koordinate/n auf S setzen
                    }

                    printf("%c ", block2[j][i]);
                }
            }
            }
        }

        if (laenge == 5){ // Wenn die länge erreicht wurde dann stoppe den Code für mehr übersicht
            printf("\n\n");
            system("pause");
        }
        system("cls");
    }
}

void MainSpiel(){
    int vergleich1 = 2;
    int vergleich2 = 2;
    int amZug = 1;

    while(getchar()!='\n'); // Eingabepuffer zurücksetzen

    while (punktSpieler1 <= 16 || punktSpieler2 <= 16){
        if (amZug == 1){ // Damit der der ein treffer gemacht hat nochmal am zug sein kann
            printf("Spieler 1 ist am zug:\n\n");

            for (int i = 0; i <= 9; i++){ // i == y
                if (vergleich == 1){
                    printf("  ");

                    for (int k = 1; k <= 10; k++){
                        printf("%d ", k);
                    }

                    vergleich = 2;
                }

                zeile = i + 97; // Zahl in ASCII umwandeln
                printf("\n%c ", zeile);

                for (int j = 0; j <= 9; j++){ // j == x
                    printf("%c ", mainblock1[j][i]);
                }
            }
            vergleich = 1;

            while(1){ // Eingabe der Koordinaten von Spieler 2 mit test ob das Feld schonmal beschossen wurde um mehrfachbeschuss auszuschließen
                printf("\nPunkte: %d\n\nZielkoordinate: ", punktSpieler1);
                scanf("%s", &koortdinaten); // Eingabe der Koordinaten XY

                sscanf(koortdinaten, "%c%d", &y, &x); // In koordinaten X und Y aufteilen

                if (block2[x-1][y-97] == 'C'){
                    printf("\nError (Dieses Feld wurde schonmal beschossen)");
                }
                else if (x > 10 || y > 'j' || x <= 0 || y < 'a'){
                    printf("\nError (Koordinaten beachten)");
                }
                else {
                    printf("\n");
                    break;
                }
            }

            system("cls"); // cls für mehr übersicht im Spiel

            printf("Spieler 1 ist am zug:\n\n"); // Nochmal weil das Spielfeld grade gesäubert wurde

            for (int i = 0; i <= 9; i++){ // i == y ; Hier wird das Feld gebaut
                if (vergleich == 1){
                    printf("  ");

                    for (int k = 1; k <= 10; k++){
                        printf("%d ", k);
                    }

                    vergleich = 2;
                }

                zeile = i + 97; // Zahl in ASCII umwandeln
                printf("\n%c ", zeile);

                for (int j = 0; j <= 9; j++){ // j == x
                    if (block2[x-1][y-97] == 'S'){
                        mainblock1[x-1][y-97] = 'X'; // Koordinate auf X setzen
                        vergleich1 = 1;
                        amZug = 1;
                    }
                    else {
                        amZug = 2;
                        mainblock1[x-1][y-97] = '@'; // Koordinate auf X setzen
                    }

                    printf("%c ", mainblock1[j][i]);
                }
            }
            vergleich = 1;

            if (vergleich1 == 1){
                block2[x-1][y-97] = 'C'; // Feld auf C setzen wenn getroffen damit es nicht nochtmal beschossen werden kann
                punktSpieler1++;
                vergleich1 = 2;
            }

            printf("\nPunkte: %d", punktSpieler1); // Ausgabe der Punkte von Spieler 1

            // Für mehr übersicht
            printf("\n\n");
            system("pause");
            system("cls");

            if (punktSpieler1 >= 16 || punktSpieler2 >= 16){break;} // Kurze Abfrage ob schon jemand die 16 punkte erreicht hat
        }


        if (amZug == 2){ // Damit der der ein treffer gemacht hat nochmal am zug sein kann
            while(getchar()!='\n'); // Eingabepuffer zurücksetzen

            printf("Spieler 2 ist am zug:\n\n");

            for (int i = 0; i <= 9; i++){ // i == y
                if (vergleich == 1){
                    printf("  ");

                    for (int k = 1; k <= 10; k++){
                        printf("%d ", k);
                    }

                    vergleich = 2;
                }

                zeile = i + 97; // Zahl in ASCII umwandeln
                printf("\n%c ", zeile);

                for (int j = 0; j <= 9; j++){ // j == x
                    printf("%c ", mainblock2[j][i]);
                }
            }
            vergleich = 1;

            while(1){ // Eingabe der Koordinaten von Spieler 2 mit test ob das Feld schonmal beschossen wurde um mehrfachbeschuss auszuschließen
                printf("\nPunkte: %d\n\nZielkoordinate: ", punktSpieler2);
                scanf("%s", &koortdinaten); // Eingabe der Koordinaten XY

                sscanf(koortdinaten, "%c%d", &y, &x); // In koordinaten X und Y aufteilen

                if (block1[x-1][y-97] == 'C'){
                    printf("\nError (Dieses Feld wurde schonmal beschossen)");
                }
                else if (x > 10 || y > 'j' || x <= 0 || y < 'a'){
                    printf("\nError (Koordinaten beachten)");
                }
                else {
                    printf("\n");
                    break;
                }
            }

            system("cls"); // cls für mehr übersicht im Spiel

            printf("Spieler 2 ist am zug:\n\n"); // Nochmal weil das Spielfeld grade gesäubert wurde

            for (int i = 0; i <= 9; i++){ // i == y
                if (vergleich == 1){
                    printf("  ");

                    for (int k = 1; k <= 10; k++){
                        printf("%d ", k);
                    }

                    vergleich = 2;
                }

                zeile = i + 97; // Zahl in ASCII umwandeln
                printf("\n%c ", zeile);

                for (int j = 0; j <= 9; j++){ // j == x
                    if (block1[x-1][y-97] == 'S'){
                        mainblock2[x-1][y-97] = 'X'; // Koordinate auf X setzen
                        vergleich2 = 1;
                        amZug = 2;
                    }
                    else {
                        mainblock2[x-1][y-97] = '@'; // Koordinate auf X setzen
                        amZug = 1;
                    }

                    printf("%c ", mainblock2[j][i]);
                }
            }
            vergleich = 1;

            if (vergleich2 == 1){
                block1[x-1][y-97] = 'C'; // Feld auf C setzen wenn getroffen damit es nicht nochtmal beschossen werden kann
                punktSpieler2++;
                vergleich2 = 2;
            }

            printf("\nPunkte: %d", punktSpieler2); // Ausgabe der unkte von Spieler 2

            // Für mehr übersicht:
            printf("\n\n");
            system("pause");
            system("cls");

            if (punktSpieler1 >= 16 || punktSpieler2 >= 16){break;} // Kleine if abfrage ob schon jemand 16 punkte erreicht hat
        }
    }
}

void Gewinner(){
    if (punktSpieler1 > punktSpieler2){ // Wenn Spieler 1 gewonnen hat:
        system("cls");
        printf("Spieler 1 hat gewonnen!\n");
    }
    else { // Wenn Spieler 2 gewonnen hat:
        system("cls");
        printf("Spieler 2 hat gewonnen!\n");
    }
}
