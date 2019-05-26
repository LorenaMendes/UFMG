fun min3 (a,b,c) =
	if (a<b) andalso (a<c) then a
	else if (b<a) andalso (b<c) then b
	else c;

fun sort3 (a:real,b:real,c:real) =
	if a < b andalso b < c then [a,b,c]
	else if a < c andalso c < b then [a,c,b]
	else if b < a andalso a < c then [b,a,c]
	else if b < c andalso c < a then [b,c,a]
	else if c < a andalso a < b then [c,a,b]
	else [c,b,a];

fun del3 list =
	if null list then nil
	else [hd(list)] @ [hd(tl(list))] @ tl(tl(tl(list)));

fun sqsum n =
	if n = 0 then 0
	else n*n + sqsum(n-1);

fun cycle1 li =
	if null li then nil
	else (tl(li)) @ [hd(li)];

fun cycle (lj,n) =
	if null lj then nil
	else if n = 0 then lj
	else cycle(cycle1(lj),n-1);

fun pow(a:real,b) =
	if b = 0 then 1.0
	else a*pow(a, b-1);