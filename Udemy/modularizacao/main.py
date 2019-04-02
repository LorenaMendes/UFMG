import aleatorio as a
import media as m

# lista = a.geraListaInteiro(10);
lista = [57, 66, 69, 71, 72, 73, 74, 77, 78, 78, 79, 79, 81, 81, 82, 83, 83, 88, 89, 94]

media = m.media(lista)
print("A média é " + str(media))

mediana = m.mediana(lista)
print("A mediana é " + str(mediana))

moda = m.moda(lista)
print("A moda é " + str(moda))
