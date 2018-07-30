#Erklärung des REPL Grundgerüst
In diesem Ordner befindet sich die erste Version des REPL. Was sie kann ist am Anfang der main Datei beschrieben.

#Grundablauf
Im der Main Funktion werden verschiedene Variablen angelegt, um die Eingaben des Nutzers zu speichern. In dem Hauptloop werden Funktionen aufgerufen zum Einlesen, Parsen, und Ausführen der richtigen Funktion (decide()).
Wenn decide() den Befehl quit erhält wird der Enum QUIT an den Loop zurückgegeben, woraufhin er abbricht und das Programm sich beendet.

#Einfache neue Sachen
Zuerst sollten die einfachen Sachen erklärt werden, die halbwegs neu sind.

##Enum action
Es kann nötig sein, dass die Eingabe eines Users etwas im Main Loop verändern sollen. Zurzeit gibt es nur die Aktionen CONT und QUIT, um den Loop entweder weiterlaufen zu lassen oder zu beenden.
Dafür wird ein enum vom Typ actions deklariert, der mehrere Konstanten deklariert. Die Funktion decide() hat als Rückgabewer eine dieser Konstanten.
Die Vorteile dieser Methode anstatt ein `int aktion` oder ein `bool beenden` zu verwenden sind: aussagekräftiger Code durch deutliche Namen, Erweiterbarkeit, wenn noch andere Aktionen dazukommen sollen.

##Aufteilung in verschiedene Dateien
Das Projekt ist in 4 Dateien aufgeteilt.
- standardheaders.h enthält alle Standardheader die benötigt werden. Sie wird zu Beginn von jeder .c Datei eingebunden.
- commands.h enthält die Funktionsköpfe der in commands.c definierten Funktionen. Sie wird in der main-Datei eingebunden.
- commands.c enthält die Befehle die der Nutzer am Ende aufrufen können soll.
- main.c enthält den Hauptloop und die Funktionen die für diesen notwendig sind.

Diese Aufteilung ermöglicht, dass immer nur die Dateien, die geändert wurden, neu kompiliert werden müssten. In einem großen Porjekt könnte das viel Zeit sparen, hier aber weniger.
Dadurch werden auch Sachen nötig wie die globale Variable DEBUG, die am Anfang von main.c definiert ist, in commands.c mit extern zu deklarieren.
Wir müssen dem Compiler quasi den Hinweis geben: wenn du commands.c kompilierst und auf DEBUG stößt, diese Variable gibts, sie ist in einer anderen Datei definiert.

##Makros
`if(strcmp(command,"echo")==0)` ist zu viel Schreibarbeit und sieht doof aus. Daher wurde das Makro isCmd(x) definiert. Damit lässt sich dieser Ausdruck abkürzen durch `if(isCmd("echo"))`.
Allgemein sind lauter ifs hintereinander nicht der beste Weg um aus dem vom User eingegeben Text herauszufinden, welche Funktion aufgerufen werden soll. Später werden vermutlich bessere Lösungen implementiert.

#Variablen
Folgende Variablen werden angelegt:
- char input[100] 
	- Ein Char Array um den vom User eingegebenen Text zu speichern.
	- Das Array wird per Referenz an die Funktion getInput gegeben, dort von fgets verändert.
	- Später wird es durch strtok geparst und auch verändert.
- `char *command`
	- Ein Char Pointer der per Referenz an die Funktion parseInput() gegeben wird und dort von strtok auf die Adresse des ersten Tokens des Userinputs gesetzt wird.
- `char *parameters[10]`
	- Ein Array von 10 char-Pointern.
	- Es wird per Referenz an die Funktion parseInput() gegeben und dort wird in die einzelnen Array-Positionen die Adresse der weiteren Tokens des UserInputs geschrieben.
	- Wenn strtok am Ende des UserInputs angekommen ist, gibt es NULL zurück. Wenn wir also das parameters-Array durchgehen, treffen wir irgendwann auf NULL und wissen dann, dass das alle Parameter waren.
- `enum actions action`
	- Ein Enum das in der Bedingung des main-Loops verwendet wird.
	- Erhält den Rückgabewert der Funktion decide()

#Funktionsaufrufe
Diese sind sehr interessant, da zum Beispiel Pointer auf Pointer und Arrays von Pointern übergeben werden müssen.

##getInput()
- Kopf: `void getInput (char *input)`
- Aufruf: `getInput(input);`

Diese Funktion soll ein Char-Array mit dem vom User eingegeben Text füllen. Wir müssen ihr daher einen Pointer auf ein char-Array übergeben.
Wird der Name eines Arrays (egal welchen Datentyps) in einen Funktionsaufruf geschrieben, wird die Adresse auf die erste Stelle dieses Arrays übergeben. Man sagt, der Arrayname zerfällt in die Adresse auf das erste Element (nur in "Zeiger-Kontexten").
Es ist quasi synonym zu `getInput(&input[0])`, aber hübscher anzuschauen.


##parseInput()
- Kopf: `void parseInput (char *input, char **command, char *parameters[])`
- Aufruf: `parseInput(input, &command, parameters);`

Diese Funktion parst und verändert mithilfe von strtok() den User-Input. Sie soll außerdem die Ergebnisse von strtok dem Main-Loop zur Verfügung stellen.
Strtok liefert als Rückgabewert die Adresse des Speicherbereichs in dem der abgesplittete String steht. Aka ein Pointer. Wir brauchen also eine Variable die einen char-Pointer aufnehmen kann. Das ist unsere command-Variable.
Wir übergeben also die Adresse von command an parseInt(), damit an ihre Stelle die Adresse des Strings geschrieben werden kann und im Main-Loop zur Verfügung steht.
In parseInput() ist command damit ein Pointer auf einen Pointer. Wenn wir ihn dereferenzieren können wir die Adresse eines Strings in den Pointer command der in der main-Funktion angelegt wurde hineinschreiben.

Mit parameters ist es erstaunlich ähnlich.
Wir wollen in ein Array die Adressen der weiteren abgesplitteten Strings hineinschreiben, so dass sie in der Main-Funktion zur Verfügung stehen. Ein Array von Adressen -> ein Array an Pointern -> Genauer gesagt, ein Array an char-Pointern. Das ist unsere Variable parameters.
Wie schreiben bei der Übergabe von parameters so wie oben schon erwähnt nur den Namen des Arrays, was zur Adresse des ersten Elementes zerfällt.
In den Kopf der Funktion schreiben wir, dass wir ein Array an char-Pointern erwarten. Man hätte hier auch `char **parameters` schreiben können, das ist ebenso korrekt, da wir ja, wie erwähnt, nicht weiteres tun als die Adresse auf das erste Element eines char-Pointer-Arrays zu übergeben. Aber die gewählte Variante mach durch Ihre Schreibweise nochmal klar, dass es sich um ein Array handelt.
Im Funktionsrumpf schreiben wir einfach nur `parameters[i]=(adresse)`.

##decide()
- Kopf: `enum actions decide (char *command, char *parameters[])`
- Aufruf: `action = decide(command, parameters);`

Die Funktion soll aufgrund des Wertes in command die eigentliche Funktion aufrufen. Sie verändert nichts an command oder parameters.
Dazu übergeben wir command (char-Array, zerfällt beim Aufruf in die Adresse des ersten Elementes) und parameters (char-Pointer-Array, zerfällt beim Aufruf in die Adresse des ersten Elements).

##strtok()
strtok(str, delimiter) funktioniert, indem in dem Originalstring (hier input) an die Stellen die als Delimiter angegeben sind ein \0 geschreiben wird und die Anfangsadresse des Tokens zurückgegeben wird. Es verändert also den Originalstring und gibt die Adressen verschiedener Positionen darin zurück. Dadurch wird keine extra Speicherplatz angelegt.
Sollte man den Originalstring nochmal benötigen muss man vorher eine Kopie davon anlegen.
