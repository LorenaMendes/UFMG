import matplotlib.pyplot as plt

# CASO MAIS SIMPLES
# x = [1, 2] # EIXO X
# y = [2, 3] # EIXO Y
# plt.plot(x, y)
# titulo = "Gráfico simples"
# eixox = "Eixo X"
# eixoy = "Eixo Y"


# GRÁFICO DE BARRAS SIMPLES
# x = [1,2,3,4,5]
# y = [2,3,7,1,0]
# plt.bar(x, y)
# titulo = "Gráfico de barras"
# eixox = "Eixo X"
# eixoy = "Eixo Y"


# GRÁFICO DE BARRAS DUPLAS
# x1 = [1,3,5,7,9]
# y1 = [2,3,7,1,0]

# x2 = [2,4,6,8,10]
# y2 = [5,1,3,7,4]

# plt.bar(x1, y1, label = "Grupo 1")
# plt.bar(x2, y2, label = "Grupo 2")
# plt.legend() # MOSTRA LEGENDA
# titulo = "Gráfico de barras 2"
# eixox = "Eixo X"
# eixoy = "Eixo Y"


# GRÁFICO DE SCATTER
# x = [1,3,5,7,9]
# y = [2,3,7,1,0]
# plt.scatter(x, y, label = "Meus pontos", color="r", marker=".", s=200)
# plt.plot(x, y, color="k", linestyle=":")
# plt.legend()
# titulo = "Scatterplot: gráfico de dispersão"
# eixox = "Eixo X"
# eixoy = "Eixo Y"

# GRÁFICO DE SCATTER TUNADO
x = [1,3,5,7,9]
y = [2,3,7,1,0]
z = [200,25,400,3300,100]
titulo = "Scatterplot Tunado"
eixox = "Eixo X"
eixoy = "Eixo Y"
plt.plot(x, y, color="k", linestyle="-.")
plt.scatter(x, y, label="Meus pontos", color="k", marker=".", s=z)

plt.title(titulo) # TÍTULO
plt.xlabel(eixox) # LABEL X
plt.ylabel(eixoy) # LABEL Y
plt.savefig("scatter.png", dpi=72) # SALVA O GRÁFICO
plt.show() # MOSTRANDO O PLOT



"""
TIPOS DE STYLES

color:	cor (ver exemplos abaixo)
label:	rótulo
linestyle:	estilo de linha (ver exemplos abaixo)
linewidth: largura da linha
marker:	marcador (ver exemplos abaixo)

CORES (color)
'b'	blue
'g'	green
'r'	red
'c'	cyan
'm'	magenta
'y'	yellow
'k'	black
'w'	white

Marcadores (marker)
'.'	point marker
','	pixel marker
'o'	circle marker
'v'	triangle_down marker
'^'	triangle_up marker
'<'	triangle_left marker
'>'	triangle_right marker
'1'	tri_down marker
'2'	tri_up marker
'3'	tri_left marker
'4'	tri_right marker
's'	square marker
'p'	pentagon marker
'*'	star marker
'h'	hexagon1 marker
'H'	hexagon2 marker
'+'	plus marker
'x'	x marker
'D'	diamond marker
'd'	thin_diamond marker
'|'	vline marker
'_'	hline marker

Tipos de linha (linestyle)
'-'	solid line style
'--'	dashed line style
'-.'	dash-dot line style
':'	dotted line style

Fonte: https://matplotlib.org/api/_as_gen/matplotlib.pyplot.plot.html"""