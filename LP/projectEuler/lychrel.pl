/*função para converter um inteiro em dígito*/
digit(N,X)
	:- digit(N,[],X), !.
digit(0,L,L).
digit(N,L,X)
	:- N1 is N//10, N2 is N rem 10, digit(N1,[N2|L],X).

/*função para converter um dígito em inteiro*/
integer([],0).
integer([A|As],X)
	:- integer(A,As,X), !.
integer(A,[],A).
integer(A,[B|Bs],X)
	:- C is 10*A+B, integer(C,Bs,X).

/*retorna 1 em caso de um número ser de lychrel*/
/*este procedimento é feito para cada valor entre 1 e 9999*/
num(1)
	:- between(1,9999,N), lychrel(N).

lychrel(N)
	:- lychrel(N,0).

/*realiza o procedimento 50 vezes*/
lychrel(_,V)
	:- V >= 50, !.
	
/*retorna true para um número não palíndromo*/
lychrel(N,V)
	:- rev_sum(N,R), not(is_palin(R)), succ(V,V1), lychrel(R,V1).

/*função append tirada das notas de aula de prolog*/
myAppend([], L, L).
myAppend([Head|TailA], B, [Head|TailC])
	:- myAppend(TailA, B, TailC).

/*função para reverso de um número tirada das notas de aula de prolog*/
myReverse([], []).
myReverse([H|T], X)
	:- myReverse(T, XAux), myAppend(XAux, [H], X).

/*função para somar um número ao reverso dele utilizando as funções de conversão inteiro-dígito*/
rev_sum(N,X)
	:- digit(N,L), myReverse(L,L1), integer(L1,N1), X is N+N1.

/*retorna true caso o valor seja palíndromo*/
is_palin(N)
	:- digit(N,L), myReverse(L,L).

result(X)
	:- aggregate(sum(N), num(N), X).
