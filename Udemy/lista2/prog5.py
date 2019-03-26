# multi_fasta = input("Nome do arquivo: ")
# arq = open(multi_fasta)

arq = open("multifasta.txt")
linhas = arq.readlines()
multifasta = {}

for linha in linhas:
	if linha[0] == ">":
		seq_atual = linha[1:].strip()
		multifasta[seq_atual] = ""
	else:
		multifasta[seq_atual] = multifasta[seq_atual] + linha.strip()

print(multifasta)
print(multifasta["seq2"])

