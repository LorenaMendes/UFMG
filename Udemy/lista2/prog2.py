def leArquivo(nome_arquivo):
	arq = open(nome_arquivo)
	texto = arq.read()
	print(texto)
	arq.close()

arquivo = input("Nome do arquivo: ")
leArquivo(arquivo)