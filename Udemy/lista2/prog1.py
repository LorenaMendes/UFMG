import re

# seq1 = input("Sequência 1: ")
# seq2 = input("Sequência 2: ")

# EXPRESSÕES REGULARES
seq1 = "ATC.A" # O . REPRESENTA "QUALQUER COISA"
seq2 = "ATCGAAAAA"

busca = re.match(seq1, seq2)

if busca:
	print("Sequências idênticas.")
	print(busca.group())
else:
	print("Sequências diferentes.")