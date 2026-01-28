# EmbeddedEventLogger
Detta projekt är en firmware-liknande simulator för ett händelsedrivet inbyggt system, utvecklad inom kursen Algoritmer, datastrukturer och design patterns.

Systemet tar emot inkommande events via en EventQueue (ringbuffer), bearbetar dem i en event loop och lagrar dem i en EventLog (ADT). Loggen kan därefter skrivas ut, sorteras och genomsökas via ett textbaserat terminalgränssnitt.

Projektet är uppbyggt med tydlig modulindelning, väldefinierade gränssnitt och fokus på kontrollerad och säker minneshantering.

# Systemöversikt

Event-flödet i systemet:

Event producer → EventQueue → Event loop → EventLog


Arkitekturen efterliknar ett förenklat inbyggt system där events anländer asynkront, köas och bearbetas i kontrollerad takt enligt ett producer/consumer-mönster.

# Moduler och datastrukturer
# Event

Varje event innehåller:

timestamp (stigande räknare)

sensorId

type (TEMP, BUTTON, MOTION)

value

# EventQueue (ADT)

Implementerad som cirkulär buffer (ringbuffer)

Fast kapacitet

Effektiva enqueue och dequeue-operationer i O(1)

Ingen omflyttning av data vid borttagning

# EventLog (ADT)

Dynamisk lista som lagrar bearbetade events

Växer vid behov

Åtkomst sker via väldefinierade funktioner (inkapsling enligt ADT-principen)

Stöd för utskrift, sortering och sökning

# Event Loop

Implementerar ett producer/consumer-mönster

Producer genererar events och placerar dem i kön

Consumer hämtar events från kön och lagrar dem i EventLog

Säkerställer att EventLog endast fylls via event-flödet

# Funktionalitet

Generering och köning av events

Bearbetning av events via event loop

Utskrift av eventloggen

Sortering av loggen efter timestamp

Sökning efter events baserat på sensorId

Temperaturövervakning via AlarmSet (VG-alternativ A)

Terminalbaserad kommandomeny

# Design patterns
Strategy (lightweight)

Sorteringsalgoritmer väljs dynamiskt vid körning via funktionspekare (Strategy-mönster).

Exempel:

sort insertion

sort selection

Detta gör lösningen:

lätt att bygga ut med fler sorteringsalgoritmer

fri från hårdkodade algoritmval

tydligt kopplad till kursens designmönster

# Tidskomplexitet (översikt)
## Sortering

### Insertion sort

Bästa fall: O(n)

Värsta fall: O(n²)

### Selection sort

O(n²) i alla fall

## Övrigt

Sökning (linjär): O(n)

Queue-operationer: O(1)

# Minneshantering

Minne allokeras vid skapande av EventQueue och EventLog

EventLog expanderar dynamiskt vid behov

Ingen manuell minneshantering (new / delete) används

STL-containrar (std::vector) hanterar minnet automatiskt (RAII)

Allt allokerat minne frigörs korrekt vid programavslut

Risken för minnesläckor är därmed eliminerad

# Bygga och köra
Visual Studio (Windows)

Öppna lösningen:

EmbeddedEventLogger.sln


Välj konfiguration (t.ex. Debug | x64)

Bygg projektet

Kör med Ctrl + F5 (utan debugger)

# Kommandon
Kommando	Beskrivning
tick <n>	Kör n iterationer av event-loopen
print	Skriv ut hela eventloggen
sort <namn>	Sortera loggen efter timestamp
find <sensorId>	Visa alla events för vald sensor
alarms	Visa aktiva temperatur-larm
set-threshold <värde>	Ändra tröskelvärde för larm
exit	Avsluta programmet
## Exempel på testkörning
> tick 5
[tick] ran 5 iterations, log size=5

> tick 10
[tick] ran 10 iterations, log size=15

> print
Idx  Time  Sensor Type    Value
-----------------------------------------
   0     0       5   BUTTON     90
   1     1       5     TEMP     63
   2     2       3   MOTION     83
   ...

> sort insertion
[sort] done using strategy 'insertion'

> find 3
Events for sensor 3:
Idx  Time  Sensor Type    Value
-----------------------------------------
   2     2       3   MOTION     83

> alarms
[alarms] active sensors (threshold=50): 5, 4

> exit
Bye!


# GitHub-repo
https://github.com/hazaralmasri98-tech/EmbeddedEventLogger

# Avslutning

Sammanfattningsvis har projektet resulterat i en stabil och modulär lösning som uppfyller samtliga grundkrav samt VG-alternativ A.
Arbetet har bidragit till en fördjupad förståelse för C++ och algoritmisk systemutveckling, med särskilt fokus på datastrukturer, designmönster och tydlig arkitektur.

Jag tar gärna emot frågor, synpunkter eller konstruktiv feedback kring lösningen.
