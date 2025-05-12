**FLP 2. projekt, varianta Babylonská věž, rok 2025**
*Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)*

*Návod k použití*

Přeložení programu pomocí příkazu v kořenovém adresáři:
```make```

Poté lze program spustit obdobným příkazem:
```./flp24-log < input.txt```

K řešení přidávám také testovací vstupy, na kterých jsem řešení testoval. Nejedná se o testy jako takové, ale spíše příklady možných vstupů, které musí člověk zkontrolovat ručně. Spuštění testů:
```make test```
Výstupy jednotlivých testů se uloží do složky ./tests/out podle názvu testů, s výstupem řešení.

*Funkcionalita*
Program jako první načte vstup použitím poskytnuté knihovny (input2 .pl) a mou doimplemetovaných "wrapper" a dalších funkcí (myIO .pl). Poté se vykoná "solver". Solver spustí iterace IDFS (search .pl). Jednotlivé iterace používají sadu nadefinovaných pohybů (movement .pl). Postupně provádí pohyby a prohledá všechny možné stavy. Tyto stavy jsou zkontrolovány (goalState .pl) a pokud jsou řešením problému tak se vypíše celý postup a program se ukončí, jinak se přejde k další iteraci. 
Pro prohledávání stavového prostoru je implementován Iterative deepening depth-first search. K IDFS jsem dospěl po vyzkoušení BFS, který se mi nepodařilo implementovat v rozumné časové složitosti. Samotný DFS není optimální, takže jsem jej nepoužil. Takže důvod použití IDFS by se lidově dal nazvat "metoda pokus omyl". Algoritmus najde optimální řešení.

*Rychlost*
Rychlost není silná stránka tohoto kódu. Řešení do 6 kroků zvládne najít ve velice příjemném čase, při 7-8 krocích se řešení najde do pár minut (tedy člověk si stihne udělat kávu). No nad 9 kroků řešení není příliš dobré. 

*Rozšíření*
Žádná.

*Omezení*
Jediné omezení jehož jsem si vědom, je neseřazení sloupců abecedně (Čísla barev ale seřazená jsou).
