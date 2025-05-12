% Author: Alexej Beňuš xbenus01@stud.fit.vutbr.cz
% Brief: Implementation of input parsing and output to debug

% Read tower from file
readTower(Tower) :-
    read_lines(RawLines),
    split_lines(RawLines, Split),
    parseChars(Split, Tower).

% Change characters
parseChars([], []).
parseChars([RowChars|RestChars], [RowAtoms|RestAtoms]) :-
    maplist(atom_chars, RowAtoms, RowChars),
    parseChars(RestChars, RestAtoms).

% Print solution
writeSolution([]).
writeSolution([Tower]) :-
    writeTower(Tower).
writeSolution([Tower|Rest]) :-
    writeTower(Tower),
    nl,
    writeSolution(Rest).

% Print just one state of tower
writeTower([]).
writeTower([Row|Rows]) :-
    atomic_list_concat(Row, ' ', Line),
    writeln(Line),
    writeTower(Rows).