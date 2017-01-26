# SSP

Um das programm zu kompilieren in das richtige directory wechseln
und einfach "make" in die Konsole eingeben.
Du kannst das Programm dann ausführen indem du "./prog" in die Konsole eingibst
und dann den namen der Test Instanz, also zum Beispiel "Instanz1.txt".

main.cpp:
erstellt ein objekt ssp, führt Run() auf diesem objekt aus und gibt dann mit bPrint() das Ergebnis aus

pqueue.cpp: 
implementierung der einer priority queue Klasse. Enthält Dijkstra.

resGraph.cpp:
residual graphen Klasse. Einzige wichtige Methode is der Konstruktor.
Darstellung des Graphen funktioniert folgendermaßen:
Es gibt ein array nodes von Knoten und ein array edges von Kanten. edges ist nach aufsteigendem tail 
Knoten sortiert. Genauer: Die Kanten die den i'ten Knoten verlassen sind in edges zwischen nodes[i].first und 
nodes[i+1].first.

resGraph.h:
Hier sind die meisten wichtigen Typen(wie z.B Edge und Node) definiert.

ssp.cpp:
Ziemlich genau wie der Pseudocode aus der Vorlesung.  
