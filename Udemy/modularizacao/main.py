import aleatorio as a
import media as m

# lista = a.geraListaInteiro(10);
lista = [4,2,5,3,6,2,2]

media = m.media(lista)
print("A média é " + str(media))

mediana = m.mediana(lista)
print("A mediana é " + str(mediana))

moda = m.moda(lista)
print("A moda é " + str(moda))
