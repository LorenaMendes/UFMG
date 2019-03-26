def criaFasta(seq, nome_arquivo):
	arq = open(nome_arquivo, 'w')
	arq.write(">CABEÇALHO_DA_SEQUENCIA\n")
	arq.write(seq)
	arq.close()

seq = input("Digite a sequência: ")
criaFasta(seq, "out.txt")