% Author: Alexej Beňuš xbenus01@stud.fit.vutbr.cz
% Brief: Definition of goal state of the tower

% Definition of goal state
goalState(State) :-
    transpose(State, Columns),
    maplist(validColumn, Columns).

% Check if the column is valid
validColumn(Column) :-
    splitColumn(Column, Balls, Stars),
    Balls \= [],
    allStars(Stars),
    extractColorsNumbers(Balls, Colors, Numbers),
    sameColor(Colors),
    ascending(Numbers).

% Split the column into balls and stars
splitColumn([], [], []).
splitColumn(['**'|T], [], ['**'|T]) :- !.
splitColumn([Ball|T], [Ball|Balls], Stars) :-
    Ball \= '**',
    splitColumn(T, Balls, Stars).

% Check if all elements are stars
allStars([]).
allStars(['**'|T]) :-
    allStars(T).

% Parses the balls into colors and numbers
extractColorsNumbers([], [], []).
extractColorsNumbers([Ball|Rest], [Color|Colors], [Number|Numbers]) :-
    atom_chars(Ball, [Color|Digits]),
    atom_chars(AtomNumber, Digits),
    atom_number(AtomNumber, Number),
    extractColorsNumbers(Rest, Colors, Numbers).

% Check if all colors are the same
sameColor([_]).
sameColor([Color, Color | Rest]) :-
    sameColor([Color | Rest]).

% Check if the numbers are ascending
ascending([_]).
ascending([A,B|Rest]) :-
    B =:= A + 1,
    ascending([B|Rest]).

% Transpose the matrix
transpose([], []).
transpose([[]|_], []).
transpose(Matrix, [Row|Rows]) :-
    maplist(nth0HT, Matrix, Row, RestMatrix),
    transpose(RestMatrix, Rows).

nth0HT([H|T], H, T).

% Skip if the first element is a star
dropStars(['**'|Rest], Balls) :-
    dropStars(Rest, Balls).
dropStars([Ball|Rest], [Ball|Rest]) :-
    Ball \= '**'.
dropStars([], []).