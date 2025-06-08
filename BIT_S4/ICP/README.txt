# ICP Projekt
### Alexej Beňuš - xbenus01
### Samuel Čus - xcussa00
### Patrik Olszar - xolsza00


## Převzaté moduly
Grafika byla převzata z [opensource projektu pacman](https://github.com/blueskyson/Qt-pac-man/tree/master/game_objects) pod MIT licencí \
Třída byla převzata [NonCopyable](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Non-copyable_Mixin), podmínka použití je sdílení pod stejnou licencí, kterou používá nebo licencí kompatibilní. Creative commons používá licenci BY-SA, která je kompatibilní s naší licencí - GPLv3

## Charakteristika programu
Jelikož jsme 3-členný tým, museli jsme implementovat navíc rozšíření pro multiplayer.
Hra je hratelná v libovolném rozumném počtu hráčů.
Oddělení front endu od back endu jsme docílili tím, že klient pouze vypisuje data přijímaná ze serveru. Server má v sobě uloženou všechnu herní logiku. Klient pouze vypisuje data ze serveru.
Singleplayer je realizován připojením uživatele na server přes localhost.
Multiplayer je realizován založením serveru na straně hostujícího klienta a připojením ostatních klientů přes síť.

## Struktura programu
Program je strukturován do 2 částí: server a klient.
Hra využívá dvou hlavních tříd: Game a Map.
Map v sobě uchovává pouze pozici zdí a průchozích políček.
Všechny ostatní informace v sobě uchovává Game.
Game řeší celou herní logiku, jako jsou kolize, pohyby, načtení mapy a ukončení hry.
Dále existují třídy pro server(server) a klienta (client).
Server se stará o zásílání hracích updatů klientovi.
Klient pouze vypisuje příjmané data a případně odesílá serveru stisknuté klávesy.

## Nedodělaná funkcionalita
Nefunguje pohyb tlačítkem myši, funguje pohyb pouze pomocí šipek.
Známé bugy: hráč co se připojuje nesmí zmáčknout start tlačítko, při replayi se nesmí zmáčknout start tlačítko.