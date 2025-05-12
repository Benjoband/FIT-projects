% Author: Alexej Beňuš xbenus01@stud.fit.vutbr.cz
% Brief: Main file of Babylon Tower puzzle

% Main function calling IO, parser and solver
start :-
    readTower(Tower),
    solve(Tower, Solution),
    writeSolution(Solution),
    halt.
