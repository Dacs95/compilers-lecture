# Grammar analyser
# Determinar si una gramatica libre de contexto 
# no tiene producciones inutiles o redundantes
#
# Input:
# S -> A | B 
# A -> a
# B -> B b
# C -> c

import re
from sys import argv

#obtener el nombre del archivo con la gramatica
nomArchivo = argv[1]

#Abrir el archivo y leerlo
f = open(nomArchivo , "r")
archivo = f.read()

#Quitarle los espacios al archivo 
archivo = archivo.replace(" ", "")

#usamos re para definir las letras mayusculas y poder compararlas
mayus = re.compile(r'[A-Z]')

#Buscar en el archivo todas las mayusculas
simbolosNT = list(set(mayus.findall(archivo)))

#Detectamos una produccion con el simbolo de asignacion 
produccion = re.compile(r'(?<=\->).*')
producciones = list(produccion.findall(archivo))

# Para la detección de la recurcion buscamos con expreciones regulares 
# un simbolo no terminal con uno terminal juntos

recurcionRE = re.compile(r'((.*){1})->[A-Z][a-z]')
recurcion = list(recurcionRE.findall(archivo))

#print(recurcion)

resultados = []

for r in recurcion:
    resultados = resultados + (list(r))
resultados = list(set(resultados))

#print(resultados)

#Para detectar las producciones que no llamadas, S es la produccion inicial
prodLlamada = ['S']

for p in producciones:
    noTerminal = list(mayus.findall(p))
    prodLlamada = prodLlamada + noTerminal

#quitar las producciones repetidas
prodLlamada = list(set(prodLlamada))

#print(simbolosNT)
#print(prodLlamada)

print("Para la siguiente gramatica: "+ "\n" + archivo + "\n")

#Checar si una produccion no fue llamada
for s in simbolosNT:
    if s not in prodLlamada:
        print("La producción " + s + " no es llamada \n")

for r in resultados:
    print("La producción " + r + " es ciclica \n")
