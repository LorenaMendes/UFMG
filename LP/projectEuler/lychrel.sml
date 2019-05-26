(*
	Inverte um número. Para isso, o transforma em lista a partir da conversão para lista
	de strings, inversão da lista, conversão para string e conversão para inteiro.
*)
fun revert value = IntInf.fromString(implode(rev(explode(IntInf.toString(value)))));

fun funAux(SOME(x)) = x;

fun intRev x = funAux(revert(x));

(* Checa se um número x é igual ao seu reverso *)
fun isPalin x = intRev(x) = x;

(*
	Retorna se um número é de Lychrel fazendo, recursivamente,
	a checagem de ser ou não palíndromo
*)
fun isLych (num, 0) = true
|   isLych (num, x) =    
let
    val temp = num + intRev(num)
in
    if isPalin(temp) then false
    else isLych(temp, x-1)
end;

(*
	Gera uma lista com todos os números que, em até 50 iterações, não são
	palíndromos ao serem somados ao seu reverso
*)
(* Os números até 9 são palíndromos e não são de Lychrel *)
fun test 0 = []
|	test 1 = []
|	test 2 = []
|	test 3 = []
|	test 4 = []
|	test 5 = []
|	test 6 = []
|	test 7 = []
|	test 8 = []
|	test 9 = []
|	test x =
	if isLych(x,50) then x::test(x-1)
	else test(x-1);

(* A função foldr faz a contagem do número de elementos da lista gerada *)
fun count L = foldr (fn (_,b) => b+1) 0 L;

(*
	Função que retorna o valor do contador para números de 0 (seed) até o máximo
	(no caso desse problema, 10000)
*)
fun result max = count(test max);
