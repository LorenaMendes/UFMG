a = int(input("a: "))
b = int(input("b: "))
c = int(input("c: "))

delta = b**2 - 4*a*c
if(delta < 0): print("Sem solução")
elif(delta == 0):
	x1 = str((-b + delta**(1/5))/2*a)
	print("Solução única: " + x1)
else:
	x1 = str((-b + delta**(1/5))/2*a)
	x2 = str((-b - delta**(1/5))/2*a)
	if(x1 == x2): print("Solução única: " + x1)
	else: print("Soluções: " + x1 + " e " + x2)
