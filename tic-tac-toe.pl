member(X, [X | _]).
member(X, [_ | L]) :- member(X, L).


% MiniMax Algorithm

minimax(Position, GoodSuccessor, Value) :-
	moves(Position, ListOfPositions), !,
	best(ListOfPositions, GoodSuccessor, Value);
	staticval(Position, Value).

best([Position], Position, Value) :- minimax(Position, _, Value), !.
best([Position1 | ListOfPositions], PositionBun, GoodValue) :-
	minimax(Position1, _, Value1),
	best(ListOfPositions, Position2, Value2),
	better(Position1, Value1, Position2, Value2, PositionBun, GoodValue).

better(Position0, Value0, Position1, Value1, Position0, Value0) :-
	move_min(Position0), Value0 > Value1, !;
	move_max(Position0), Value0 < Value1, !.
better(Position0, Value0, Position1, Value1, Position1, Value1).


% 1 2 3 <- positions on the table
% 4 5 6
% 7 8 9

other_player(x, 0).
other_player(0, x).

initial_grid([empty, empty, empty, empty, empty, empty, empty, empty, empty]).

% lines
final_grid([C, C, C, _, _, _, _, _, _], C) :- C \== empty, !.
final_grid([_, _, _, C, C, C, _, _, _], C) :- C \== empty, !.
final_grid([_, _, _, _, _, _, C, C, C], C) :- C \== empty, !.

% columns
final_grid([C, _, _, C, _, _, C, _, _], C) :- C \== empty, !.
final_grid([_, C, _, _, C, _, _, C, _], C) :- C \== empty, !.
final_grid([_, _, C, _, _, C, _, _, C], C) :- C \== empty, !.

% diagonals
final_grid([C, _, _, _, C, _, _, _, C], C) :- C \== empty, !.
final_grid([_, _, C, _, C, _, C, _, _], C) :- C \== empty, !.

% tie
final_grid(T, empty) :- \+member(empty, T).


moves(Position, ListOfPositions) :- bagof(Position1, s(Position, Position1), ListOfPositions).

/*
	state(J, Grid, N, M)
		J - player that currently has to place
		Grid - list containing the 9 spaces in the grid
		N - maximum number of moves that can be done in depth
		M - opposite player
*/

s(state(J, T, N, M), state(J1, T1, N1, M)) :- \+final_grid(T, _), N > 0, other_player(J, J1), N1 is N - 1, put(J, T, T1).

put(J, [empty | T], [J | T]).
put(J, [H | T], [H | T1]) :- put(J, T, T1).

staticval(state(_, T, _, MAX), Value) :- final_grid(T, C), !,
					(C == MAX, Value is 99 ; other_player(C, MAX), Value is -99 ; C == empty, Value is 0).
staticval(state(_, T, _, Max), Value) :- other_player(MIN, MAX), open_lines(MAX, T, D1), open_lines(MIN, T, D2),
					Value is D1 - D2.

open_lines(J, T, D) :- line1(J, T, L1), line2(J, T, L2), line3(J, T, L3),
				column1(J, T, C1), column2(J, T, C2), column3(J, T, C3),
				diagonal1(J, T, D1), diagonal2(J, T, D2),
				D is L1 + L2 + L3 + C1 + C2 + C3 + D1 + D2.

line1(J, [A, B, C, _, _, _, _, _, _], 1) :- other_player(J, J1), \+member(J1, [A, B, C]), !.
line1(_, _, 0).

line2(J, [_, _, _, A, B, C, _, _, _], 1) :- other_player(J, J1), \+member(J1, [A, B, C]), !.
line2(_, _, 0).

line3(J, [_, _, _, _, _, _, A, B, C], 1) :- other_player(J, J1), \+member(J1, [A, B, C]), !.
line3(_, _, 0).

column1(J, [A, _, _, B, _, _, C, _, _], 1) :- other_player(J, J1), \+member(J1, [A, B, C]), !.
column1(_, _, 0).

column2(J, [_, A, _, _, B, _, _, C, _], 1) :- other_player(J, J1), \+member(J1, [A, B, C]), !.
column2(_, _, 0).

column3(J, [_, _, A, _, _, B, _, _, C], 1) :- other_player(J, J1), \+member(J1, [A, B, C]), !.
column3(_, _, 0).

diagonal1(J, [A, _, _, _, B, _, _, _, C], 1) :- other_player(J, J1), \+member(J1, [A, B, C]), !.
diagonal1(_, _, 0).

diagonal2(J, [_, _, A, _, B, _, C, _, _], 1) :- other_player(J, J1), \+member(J1, [A, B, C]), !.
diagonal2(_, _, 0).


move_max(state(MAX, _, _, MAX)).
move_min(state(MIN, _, _, MAX)) :- other_player(MIN, MAX).


tic_tac_toe_minimax :- initialize(MAX, N), initial_grid(T), show_grid(T), game_minimax(state(x, T, N, MAX)).

MAX_player(M) :- write('Starting game...\n'), repeat, write('Want to play as X?( yes / no)\n'), read(T),
			(T == yes, M = 0 ; T == y, M = 0 ; T == no, M = x ; T == n , M = x), !.

initialize(M, N) :- MAX_player(M), nl, repeat, write('Difficulty( 1 - easy, 2 - normal, 3 - hard): '), read(N), integer(N), !, nl.

game_minimax(state(_, T, _, MAX)) :- final_grid(T, C), !, declare_winner(C, MAX).
game_minimax(state(MAX, T, N, MAX)) :- minimax(state(MAX, T, N, MAX), state(MIN, T1, N1, MAX), _), write('Computer took its turn\n'), show_grid(T1), game_minimax(state(MIN, T1, N, MAX)).
game_minimax(state(MIN, T, N, MAX)) :- other_player(MIN, MAX), repeat, write('Line: '), read(L), write('Column: '), read(C),
					P is 3 * (L - 1) + C, mark(MIN, T, P, T1), !, show_grid(T1), game_minimax(state(MAX, T1, N, MAX)).

mark(MIN, [empty | T], 1, [MIN | T]).
mark(MIN, [H | T], P, [H | T1]) :- P > 1, P1 is P - 1, mark(MIN, T, P1, T1).

declare_winner(J, MAX) :- J == MAX, write('You lost!\n') ; other_player(J, MAX), write('You won!\n') ; J == empty, write('Tie!\n').

show_grid([C1, C2, C3, C4, C5, C6, C7, C8, C9]) :- write('  1 2 3 \n'),
							write('1 '), write_symbol(C1),
							write(' '), write_symbol(C2),
							write(' '), write_symbol(C3), nl,
							write('2 '), write_symbol(C4),
							write(' '), write_symbol(C5),
							write(' '), write_symbol(C6), nl,
							write('3 '), write_symbol(C7),
							write(' '), write_symbol(C8),
							write(' '), write_symbol(C9), nl, nl.

write_symbol(X) :- X == empty, !, write('.') ; X == x, !, write('X') ; write('0').
