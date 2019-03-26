operacao = input("Digite sua operação com espaços entre os caracteres: ")
ops = operacao.split()

if ops[1] == "+":
	print(int(ops[0])+int(ops[2]))
elif ops[1] == "-":
	print(int(ops[0])-int(ops[2]))
elif ops[1] == "*":
	print(int(ops[0])*int(ops[2]))
elif ops[1] == "^":
	print(int(ops[0])**int(ops[2]))
elif ops[1] == "/":
	if(int(ops[2]) == 0):
		print("Não faço divisão por zero")
	else:
		print(int(ops[0])/int(ops[2]))