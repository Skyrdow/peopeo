# FUNDAMENTOS DE PROGRAMACIÓN PARA INGENIERÍA
# SECCIÓN DEL CURSO: 0-C-6
# PROFESOR DE TEORÍA: ALFREDO GONZÁLEZ FUENTES
# PROFESOR DE LABORATORIO: PATRICIA MELLADO ACEVEDO
#
# AUTOR
# NOMBRE: LUCAS
# RUT:
# CARRERA: Ingeniería Civil Informática
# DESCRIPCIÓN DEL PROGRAMA: El programa toma como entrada el número del
# ultimo archivo a revisar de un conjunto de archivos llamado
# "mesa-<X>.txt", el programa revisará todos los archivos,
# y determinará la lista total de comunas presentes en todos
# los archivos, luego, una comuna a la vez, generará un informe que
# será guardado en un archivo llamado "<COMUNA>.txt", uno para cada
# comuna.

# BLOQUE DE DEFINICIONES

# DEFINICION DE FUNCIONES
from cgitb import text


def LeerArchivos(cant_archivos):
    """
    Entrada: 1 int, el numero del ultimo archivo "mesa-X.txt"
    Salida: 1 lista (list) con los textos de archivos cargados
    Esta función itera para abrir todos los archivos indicados,
    luego, al leerlos, convierte las lineas de formato string a
    una lista, con el objetivo de acceder eficientemente a los valores
    separados por comas posteriormente
    """
    # Nombre por defecto del resto del archivo
    nombre_archivos = "mesa-"
    # Se inicializa la lista vacía
    _lista_archivos = []
    # Iterador en 1 porque los archivos comienzan por mesa-1.txt
    i = 1
    while i <= cant_archivos:
        # "mesa-" + i + "txt"
        nom_archivo = nombre_archivos + str(i) + ".txt"
        # Se abre el i-esimo archivo y se guarda la referencia
        # utf-8 necesario por los carácteres españoles
        archivo = open(nom_archivo, "r", encoding="utf-8")
        # Se guarda el texto en formato de lista
        texto_archivo = archivo.readlines()
        # Se cierra el archivo, ya que ya se guardó en una variable
        # local la información necesaria
        archivo.close()
        # Ciclo para acomodar el texto de las lineas en listas
        j = 0
        while j < len(texto_archivo):
            # Se hace split(",") a cada linea del archivo
            texto_archivo[j] = texto_archivo[j].split(",")
            j += 1
        # Se agrega a la variable de salida el texto de este archivo
        _lista_archivos.append(texto_archivo)
        i += 1
    # Salida
    return _lista_archivos


def IndexarComunas(archivos):
    """
    Entrada: 1 lista con los textos de los archivos a revisar
    Salida: 1 lista con las comunas presentes en los archivos revisados
    Esta función compara con una lista que se va actualizando,
    si se repite el primer elemento de la primera linea de cada
    archivo, que en este caso, es la comuna de la mesa
    """
    # Lista vacía para la comparación y salida
    _lista_comunas = []
    i = 0
    # Ciclo para revisar cada archivo
    while i < len(archivos):
        # Se asume que la comuna del archivo no esta repetida
        repetido = False
        j = 0
        # Se revisa que la comuna no se repite
        while j < len(_lista_comunas):
            # Si la comuna a la que pertenece la mesa de este archivo
            # ya se encuentra en la lista, significa que anteriormente
            # apareció
            if archivos[i][0][0] == _lista_comunas[j]:
                repetido = True
            j += 1

        # Si la comuna del archivo no esta repetida se agrega
        # a la lista para detectar cuando archivos posteriores usen
        # esta comuna
        if not repetido:
            _lista_comunas.append(archivos[i][0][0])
        i += 1
    # Se retorna la lista de comunas
    return _lista_comunas


def ProcesadoDeComuna(archivos, nombre_comuna):
    """
    Entrada: 1 lista (list) con los textos de todos los archivos
            a revisar y 1 string con el nombre de la comuna
            a la que se le va a hacer el informe
    Salida: 1 string con el informe de la comuna
    Esta función realizará los calculos necesarios para el informe
    y se redactará el informe en el formato requerido
    """
    # Variables de mesas
    mesas_escrutadas = 0
    lista_descuadradas = []
    votos_totales_comuna = 0

    # Variables de candidatos
    nombres_candidatos = []
    votos_candidatos = []

    # Ciclo para detectar las mesas descuadradas y eliminarlas
    # del conteo de votos
    i = 0
    # iterar entre todos los archivos
    while i < len(archivos):
        # Revisar si el archivo corresponde a la comuna actual
        # para el informe.
        # (Primer elemento de la primera linea del texto)
        if archivos[i][0][0] == nombre_comuna:
            # Se agrega 1 al total de mesas escrutadas
            mesas_escrutadas += 1
            # Iterador j = 1 debido a que la primera linea no contiene
            # votos
            j = 1
            suma_votos_mesa = 0
            # Ciclo para calcular mesas descuadradas
            while j < len(archivos[i]):
                # calculo para comprobar descuadre, se suman los votos
                # totales de los candidatos en la mesa
                suma_votos_mesa += int(archivos[i][j][1])
                j += 1

            # Si la suma de votos de cada candidato es diferente a
            # la cantidad indicada por el archivo en la primera linea
            # o la cantidad de votos es mayor al total de personas
            # habilitadas para votar en la mesa, se considera que
            # la mesa es descuadrada
            if suma_votos_mesa != int(archivos[i][0][2]) \
                    and int(archivos[i][0][2]) <= int(archivos[i][0][3]):
                # Se añade el numero de la mesa descuadrada a la lista
                lista_descuadradas.append(archivos[i][0][1])
                # y se elimina para el conteo de votos posterior
                archivos.pop(i)
                # se compensa el iterador por el pop()
                i -= 1
            else:
                # Caso contrario, la suma de los votos se agrega a la
                # cantidad de votos totales de la comuna
                votos_totales_comuna += suma_votos_mesa
        i += 1

    i = 0
    # Se realiza el mismo ciclo pero esta vez sin las mesas
    # descuadradas
    while i < len(archivos):
        if archivos[i][0][0] == nombre_comuna:
            j = 1
            while j < len(archivos[i]):
                # Suma de votos de candidatos individualmente
                # Se hace un procedimiento similar a la revisión
                # de comunas, pero guardando también el nombre del
                # candidato para añadir votos posteriormente
                c = 0
                repetido = [False, 0]
                # Se compara para buscar los nombres repetidos
                while c < len(nombres_candidatos):
                    if archivos[i][j][0] == nombres_candidatos[c]:
                        # Se guarda en c la posición
                        # del nombre repetido
                        repetido = [True, c]
                    c += 1
                if repetido[0]:
                    # Si se repite se añaden los votos al candidato en
                    # la posición c
                    votos_candidatos[repetido[1]] += int(archivos[i][j][1])
                else:
                    # Si no, se añade el nombre y los votos
                    # del candidato a las listas
                    # Destacar que gracias a este sistema,
                    # la posición c en ambas listas serán datos del
                    # mismo candidato
                    nombres_candidatos.append(archivos[i][j][0])
                    votos_candidatos.append(int(archivos[i][j][1]))
                j += 1
        i += 1

    # Se escribe el informe en el formato
    linea_separadora = "####################\n"
    texto_informe = linea_separadora + "GENERAL\n" + linea_separadora
    # Datos mesas
    texto_informe += "MESAS ESCRUTADAS: " + str(mesas_escrutadas) + "\n"
    # total de mesas - mesas descuadradas = mesas correctas
    texto_informe += "CORRECTAS: " \
                     + str(mesas_escrutadas - len(lista_descuadradas)) + "\n"
    texto_informe += "DESCUADRADAS: " + str(len(lista_descuadradas)) + "\n\n"
    texto_informe += linea_separadora + "RESULTADOS PARCIALES\n" \
                                      + linea_separadora + "\n"

    # Comprobar que la lista tiene votos, ya que si la comuna tiene
    # sólo mesas descuadradas esta parte del informe quedará vacio
    if len(nombres_candidatos) == 0:
        # Mensaje notificatorio
        texto_informe += "No hubo suficientes mesas correctas,\n"
        texto_informe += "No hay votos para ningún candidato\n"
    else:
        # Ciclo para escribir todos los candidatos
        i = 0
        while i < len(nombres_candidatos):
            # <Nombre>, <Votos>, <% del total>
            texto_informe += nombres_candidatos[i] + ", " \
                            + str(votos_candidatos[i]) + ", " \
                            + str(round((votos_candidatos[i] /
                                         votos_totales_comuna) * 100, 2)) \
                            + "%\n"
            i += 1
    texto_informe += "\n" + linea_separadora \
                     + "MESAS DESCUADRADAS\n" + linea_separadora
    # Si no hay mesas descuadradas se imprime un mensaje para mejorar
    # la claridad
    if len(lista_descuadradas) == 0:
        texto_informe += "NO HAY MESAS DESCUADRADAS"
    else:
        # Si hay mesas descuadradas se realiza un ciclo para
        # escribir la lista entera de estas mesas
        i = 0
        while i < len(lista_descuadradas):
            texto_informe += lista_descuadradas[i] + "\n"
            i += 1

    # Retorna el informe de la comuna
    return texto_informe


# BLOQUE PRINCIPAL

# ENTRADA

numero_de_archivos = int(input(
    "Ingrese el número del último archivo a revisar: "))

# PROCESAMIENTO
# Se obtienen los textos
texto_archivos = LeerArchivos(numero_de_archivos)
# Se obtienen las comunas, sin repetir
lista_comunas = IndexarComunas(texto_archivos)
# Ciclo para realizar los informes de todas las comunas
for comuna in lista_comunas:
    # Se realiza el informe
    informe_comuna = ProcesadoDeComuna(texto_archivos, comuna)
    # Se prepara el nombre del archivo
    nombre_informe = str(comuna) + ".txt"

# SALIDA
    # Se escribe el archivo
    with open(nombre_informe, "w", encoding="utf-8") as archivo:
        archivo.write(informe_comuna)
# Se confirma el fin del programa
print("Informes realizados con éxito")
