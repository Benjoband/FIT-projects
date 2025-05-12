% Author: Alexej Beňuš xbenus01@stud.fit.vutbr.cz
% Brief: Implementation of "solver" and Iterative deepening depth-first algorithm

% Start solving
solve(Start, Solution) :-
    between(1, 100, DepthLimit),
    % format('% Depth: ~w~n', [DepthLimit]),
    iDFS(Start, [], Solution, DepthLimit), !.

% Depth-first search with a limit
iDFS(State, _, [State], _) :-
    goalState(State).
iDFS(State, Visited, [State|Path], Limit) :-
    Limit > 0,
    move(State, Next),
    \+ member(Next, Visited),
    NewLimit is Limit - 1,
    iDFS(Next, [Next|Visited], Path, NewLimit).
