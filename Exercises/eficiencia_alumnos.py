import matplotlib.pyplot as plt


import random
import time


def sortBurbuja(lista):
    n = len(lista)
    i=0
    while i<n-1:
        j=i+1
        #print ("pasada #: {}\n".format(j))
        while j<n:
            if lista[i]>lista[j]:
                aux = lista[i]
                lista[i]=lista[j]
                lista[j]=aux
            j=j+1
        i=i+1
	
	
def insertionSort(n_lista):
    for index in range(1,len(n_lista)):
    	actual = n_lista[index]
    	posicion = index
    	#print("valor a ordenar = {}".format(actual))
    	while posicion>0 and n_lista[posicion-1]>actual:
    		n_lista[posicion]=n_lista[posicion-1]
    		posicion = posicion-1           
    	n_lista[posicion]=actual
    return n_lista	

    
def quicksort(lista):
    quicksort_aux(lista,0,len(lista)-1)

def quicksort_aux(lista,inicio, fin):
    if inicio < fin:

        pivote = particion(lista,inicio,fin)

        quicksort_aux(lista, inicio, pivote-1)
        quicksort_aux(lista, pivote+1, fin)

def particion(lista, inicio, fin):
    #Se asigna como pivote en número de la primera localidad
    pivote = lista[inicio]
    #print("Valor del pivote {}".format(pivote))
    #Se crean dos marcadores 
    izquierda = inicio+1
    derecha = fin
    #print("Índice izquierdo {}".format(izquierda))
    #print("Índice derecho {}".format(derecha))

    
    bandera = False
    while not bandera:
        while izquierda <= derecha and lista[izquierda] <= pivote:
            izquierda = izquierda + 1
        while lista[derecha] >= pivote and derecha >=izquierda:
            derecha = derecha -1
        if derecha < izquierda:
            bandera= True
        else:
            temp=lista[izquierda]
            lista[izquierda]=lista[derecha]
            lista[derecha]=temp
            
    #print(lista)

    temp=lista[inicio]
    lista[inicio]=lista[derecha]
    lista[derecha]=temp
    return derecha


def mergeSort(lista, inicio, fin):
    if len(lista)==1 or len(lista)==0:
        return lista
    else:
        arrBajo = mergeSort(lista[inicio:(fin//2)], 0,len(lista)-1)
        arrAlto = mergeSort(lista[(fin//2):fin], 0,len(lista)-1)
        com = merge(arrBajo, arrAlto)
    return com

def merge(arrBajo,arrAlto):
    # print("Merge in :", arrBajo, arrAlto)
    t=[]
    while(len(arrBajo)>0 and len(arrAlto)>0):
        if(arrBajo[0] <= arrAlto[0] ):
            t.append(arrBajo.pop(0))
        else:
            t.append(arrAlto.pop(0))
    
    # agregar los elemntos faltantes del primer sub arreglo
    if(len(arrBajo)>0):
        t=t+arrBajo

    # agregar los elemntos faltantes del segundo sub arreglo
    if(len(arrAlto)>0):
        t=t+arrAlto
    
    # print("Merge out:",t)    
    return t     
    

def graficarTiempos(numDatos,tiemposBurbuja, tiemposInsertionSort,tiemposQuick,tiemposMerge):
    fig, ax= plt.subplots()
    ax.plot(numDatos, tiemposBurbuja, label ="Ordenamiento de la Burbuja", marker="*", color ="r")
    ax.plot(numDatos, tiemposInsertionSort, label ="Ordenamiento de Insertion", marker=".", color ="g")
    ax.plot(numDatos, tiemposQuick, label ="Ordenamiento de Quick", marker="x", color ="b")
    ax.plot(numDatos, tiemposMerge, label ="Ordenamiento de Merge", marker="+", color ="y")
    
    ax.set_xlabel("Numero de Datos")
    ax.set_ylabel("Tiempo")
    ax.grid(True)
    ax.legend(loc=2)

    plt.title("Tiempos de ejecución [seg]")
    plt.show()

	
def eficienciaAlgoritmos(numDatos):
    tiemposBurbuja= []
    tiemposQuick = []
    tiemposInsertionSort = []
    tiemposMerge = []
    for n in numDatos:
        #lista_Burbuja = random.sample(range(1000), n)
        lista_Burbuja = random.sample(range(0, 100000), n)    #genera(n)
        lista_Quick = lista_Burbuja.copy()
        lista_insertionSort = lista_Burbuja.copy()
        lista_merge = lista_Burbuja.copy()

        print("\n=========\n")
        #print (lista_Burbuja)
        t0 = time.monotonic() 
        sortBurbuja(lista_Burbuja)
        dt = round(time.monotonic() -t0,6)
        tiemposBurbuja.append(dt)
        print("\nBurbuja(n={}): \tTiempo transcurrido: {} seg".format(n,round(dt,6)))
        #print("\nLISTA ORDENADA\n")
        #print (lista_Burbuja)
        
        t0 = time.monotonic() 
        insertionSort(lista_insertionSort)
        dt = round(time.monotonic() -t0,6)
        tiemposInsertionSort.append(dt)
        print("InsertionSort(n={}): \tTiempo transcurrido: {} seg".format(n,round(dt,6)))
        #print("\nLISTA ORDENADA\n")
        #print (lista_insertionSort)
              
        t0 = time.monotonic() 
        # lista_Quick.sort()
        quicksort(lista_Quick)
        dt = round(time.monotonic() -t0,6)
        tiemposQuick.append(dt)
        print("QuickSort(n={}):\tTiempo transcurrido: {} seg".format(n,round(dt,6)))
        
        #COLOCAR AQUI EL CODIGO FALTANTE
        t0 = time.monotonic()
        mergeSort(lista_merge,0,len(lista_merge)-1)
        dt = round(time.monotonic() -t0,6)
        tiemposMerge.append(dt)
        print("MergeSort(n={}):\tTiempo transcurrido: {} seg".format(n,round(dt,6)))
        
    print("\n=========\n")
    return tiemposBurbuja,tiemposInsertionSort,tiemposQuick,tiemposMerge


def main():

    #Tamaños de la lista de números aleatorios a generar
    #numDatos = [100,200,300,400,....,2000]
    numDatos = [n*100 for n in range(1,6)] 
    
    tiemposBurbuja= []
    tiemposInsertionSort = []
    tiemposQuick = []
    tiemposMerge = []
    tiemposBurbuja, tiemposInsertionSort, tiemposQuick, tiemposMerge = eficienciaAlgoritmos(numDatos)
    print ("Tiempos de ejecucion burbuja: \n{}\n".format(tiemposBurbuja))
    print ("Tiempos de ejecucion InsertionSort: \n{}\n".format(tiemposInsertionSort))
    print ("Tiempos de ejecucion QuickSort: \n{}\n".format(tiemposQuick))
    print ("Tiempos de ejecucion MergeSort: \n{}\n".format(tiemposMerge))
    
    # Se imprimen los tiempos totales de ejecución
    # Para calcular el tiempo total se aplica la función sum() a las listas de tiempo
    print("\nANALISIS DE TIEMPOS:")
    print("=======================")
    print("Tiempo total de ejecución en burbuja sort \t{} [s]".format(sum(tiemposBurbuja)))
    print("Tiempo total de ejecución en insert sort \t{} [s]".format(sum(tiemposInsertionSort)))
    print("Tiempo total de ejecución en quick sort \t{} [s]".format(sum(tiemposQuick)))
    print("Tiempo total de ejecución en merge sort \t{} [s]".format(sum(tiemposMerge)))
    
    graficarTiempos(numDatos,tiemposBurbuja,tiemposInsertionSort,tiemposQuick,tiemposMerge)

main()	
