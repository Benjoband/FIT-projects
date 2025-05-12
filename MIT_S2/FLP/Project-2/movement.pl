% Author: Alexej Beňuš xbenus01@stud.fit.vutbr.cz
% Brief: Defines all possible movements of the tower

% Function that generates all possible movements
move(State, Next) :-
    (rotate(State, Next) ; verticalUp(State, Next) ; verticalDown(State, Next)),
    \+ State = Next. % maybe useless, but i tried

% Rotate a row to left
rotateRowLeft(Row, Rotated) :-
    Row = [First | Rest],
    append(Rest, [First], Rotated).

% Rotate a row to right
rotateRowRight(Row, Rotated) :-
    append(Rest, [Last], Row),
    Rotated = [Last|Rest].

% Rotate a row
rotate(State, NewState) :-
    nth0(Index, State, Row),
    (rotateRowRight(Row, RotatedRow) ; rotateRowLeft(Row, RotatedRow)),
    \+ Row = RotatedRow,
    replace(State, Index, RotatedRow, NewState).

% Move the empty space up
verticalUp(State, NewState) :-
    findEmpty(State, RowIndex, ColIndex),
    RowIndex > 0,
    AboveIndex is RowIndex - 1,
    nth0(RowIndex, State, Row),
    nth0(ColIndex, Row, '**'),
    nth0(AboveIndex, State, AboveRow),
    nth0(ColIndex, AboveRow, Elem),
    replaceInMatrix(State, RowIndex, ColIndex, Elem, Tmp),
    replaceInMatrix(Tmp, AboveIndex, ColIndex, '**', NewState).

% Move the empty space down
verticalDown(State, NewState) :-
    findEmpty(State, RowIndex, ColIndex),
    length(State, RowCount),
    RowIndex < RowCount - 1,
    BelowIndex is RowIndex + 1,
    nth0(RowIndex, State, Row),
    nth0(ColIndex, Row, '**'),
    nth0(BelowIndex, State, BelowRow),
    nth0(ColIndex, BelowRow, Elem),
    replaceInMatrix(State, RowIndex, ColIndex, Elem, Tmp),
    replaceInMatrix(Tmp, BelowIndex, ColIndex, '**', NewState).

% Find the empty space in the tower
findEmpty(State, RowIndex, ColIndex) :-
    nth0(RowIndex, State, Row),
    nth0(ColIndex, Row, '**').

% Replace an element in a matrix at a given row and column index
replaceInMatrix(Matrix, RowIndex, ColIndex, Elem, NewMatrix) :-
    nth0(RowIndex, Matrix, Row, RestRows),
    replace(Row, ColIndex, Elem, NewRow),
    nth0(RowIndex, NewMatrix, NewRow, RestRows).

% Replace an element in a list at a given index
replace(List, Index, Elem, NewList) :-
    same_length(List, NewList),
    append(Prefix, [_|Suffix], List),
    length(Prefix, Index),
    append(Prefix, [Elem|Suffix], NewList).