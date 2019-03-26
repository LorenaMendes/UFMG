import prog2 as p2

opcao = 0
print("O que você deseja fazer?")
print("1 -> Ler um arquivo de texto")
print("2 -> Fechar o programa\n")

while opcao < 1 or opcao > 2:
	opcao = int(input())
	if opcao == 1:
		nome_arquivo = input("Digite o nome do arquivo: ")
		p2.leArquivo(nome_arquivo)
	else:
		print("Fechando o programa...")
		break
