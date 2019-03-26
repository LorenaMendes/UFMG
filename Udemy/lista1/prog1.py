""" Faça um programa que receba a idade do usuário
e diga se ele é maior ou menor de idade """

idade = int(input("Digite a idade do usuário: "))
if idade >= 18:
	print("Maior de idade.")
elif idade > 0 and idade < 18:
	print("Menor de idade.")
else:
	print("Idade inválida")
