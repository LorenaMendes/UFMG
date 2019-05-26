# Função que retorna true se um número for palíndromo
def palindromo(num):
        rev = str(num)[::-1]
        if str(num) == rev: return True
        else: return False

# Retorna falso caso encontre um palíndromo ao somar um número
# a seu reverso. Esse procedimento é feito 50 vezes. Se não
# for encontrado um palíndromo dentro desse limite de iterações,
# então o número é de Lychrel e retorna-se verdadeiro
def isLychrel (num):
        atual = num
        for x in range(50):
                atual += int(str(atual)[::-1])
                if palindromo(atual): return False
        return True

# Cria um contador para incrementar a cada número de Lychrel
contador = 0

# Para esse problema, foi solicitado analisar números de 0 a 10000
for i in range(1, 10000):
        lych_num = isLychrel(i)
        if (lych_num): contador += 1

print("Quantidade: " + str(contador))
