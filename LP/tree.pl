% Fatos
gerou(kelly, maria).
gerou(cleber, maria).
gerou(cleber, bruna).
gerou(maria, julia).
gerou(maria, pedro).
gerou(pedro, lucas).

feminino(kelly).
feminino(maria).
feminino(julia).
feminino(bruna).
masculino(cleber).
masculino(pedro).
masculino(lucas).

% Regras
filho(Y, X) :- gerou(X, Y).
mae(X, Y) :- feminino(X), filho(Y, X).
avo(X, Z) :- filho(Z, Y), filho(Y, X).

sentenca --> expr_nominal, predicado.
expr_nominal --> artigo, nome.
expr_nominal --> artigo, nome, expr_preposicional.
predicado --> verbo.
predicado --> verbo, expr_nominal.
predicado --> verbo, expr_nominal, expr_preposicional.
expr_preposicional --> preposicao, expr_nominal.
nome --> [menino]; [menina]; [pato]; [telescopio]; [musica]; [pena].
preposicao --> [ate]; [com].
verbo --> [e]; [viu]; [esta]; [toca]; [canta]; [surpreende].
artigo --> [a]; [o]; [uma]; [um].

string --> string, (string), [string], [].

