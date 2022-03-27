# FUNDAMENTOS DE PROGRAMACIÓN PARA INGENIERÍA
# SECCIÓN DEL CURSO: 0-C-6
# PROFESOR DE TEORÍA: ALFREDO GONZÁLEZ FUENTES
# PROFESOR DE LABORATORIO: PATRICIA MELLADO ACEVEDO
#
# AUTOR
# NOMBRE:
# RUT:
# CARRERA: Ingeniería Civil Informática
# DESCRIPCIÓN DEL PROGRAMA: El programa recibe como entrada un
#   ejercicio de fracciones en formato de string, con el orden de
#   precedencia siempre indicado por paréntesis, usando (+) para
#   indicar suma, (-) para indicar resta, (x) para indicar multipli-
#   cación y (:) para indicar división.
#   Adicionalmente, el numerador será un numero entero y el denominador
#   será siempre un numero entero positivo.
#   Ejemplo: "(5/6 + -4/8) x (9/5 – (12/5 x 6/4))"
#   Cada calculo es automaticamente simplificado e impreso, mostrando
#   paso a paso el desarrollo del ejercicio.

#   Para usar el programa se usa la función "calcular()", usando como entrada
#   la operación.

### BLOQUE DE DEFINICIONES ###

# Importación de Funciones
# No hay

# Definicion de Constantes
# No hay constantes globales

# Definicion de Funciones
def buscar_calculo_prioritario(expresion_completa):
    """
    Entrada: 1 string (str) que cumpla con las características especificadas
             en la descripción.
    Salida: 1 lista (list) que contiene 2 números enteros (int) que
            representan la posición (contando desde 0) la localización de 2
            paréntesis "(" y ")" en la string de entrada, en ese orden.
    Esta función busca la operación con mayor prioridad en la string de
    entrada.  Para lograr esto, recorremos la string carácter a carácter,
    en un ciclo "while", teniendo un valor "importancia" que aumenta
    cuando se encuentra un paréntesis abierto "(", luego cuando se encuentra
    un paréntesis cerrado ")" se compara la importancia de la operación que
    se encuentra dentro del paréntesis con la operación con mayor importancia
    registrada hasta el momento, si la actual resulta ser mayor, esta pasa
    a ser la operación con mayor importancia, luego se resta importancia
    y se continua buscando otra hasta recorrer toda la string.
    Si hay dos operaciones con importancia equivalente se mantiene la
    la primera encontrada.
    Si no hay paréntesis en la string (debido a la función "resolver_calculo()"
    esto es posible), el retorno será [0, 0] (luego se resolverá este
    problema en la función "calcular()")
    """
    # Variables
    i = 0
    inicio = 0
    inicio_aux = 0
    fin = 0
    importancia = 0
    importancia_aux = 0

    # Ciclo while para iterar por toda la string
    while i < len(expresion_completa):
        # Comprobar si el carácter [i] es (
        if expresion_completa[i] == "(":
            # Guardar la localización del primer paréntesis
            # en valor temporal
            inicio_aux = i
            # Aumentar la importancia
            importancia_aux += 1
        # Comprobar si el carácter [i] es )
        elif expresion_completa[i] == ")":
            # Comparar importancias
            if importancia_aux > importancia:
                # Reasignar importancia mayor
                importancia = importancia_aux
                # Guardar la localización del segundo
                # paréntesis
                fin = i
                # Guardar la localización del primer
                # paréntesis en otra variable
                inicio = inicio_aux
            # Restar importancia DESPUES de comparar
            importancia_aux -= 1
        # Aumentar iterador
        i += 1
    # Comprobar si no hubo paréntesis
    if fin == 0 and inicio == 0:
        return [0, 0]
    # Retornar las ubicaciones de los paréntesis con mayor prioridad
    else:
        return [inicio + 1, fin]


def resolver_calculo(expresion_completa, inicio_y_fin):
    """
    Entrada: 1 string (str) que contiene la expresión del ejercicio
             completo, o lo que queda por calcular, ej:
             "(5/6 + -4/8) x (9/5 – (12/5 x 6/4))".

             1 lista (list) que contiene 2 números enteros, los cuales
             son las ubicaciones en la expresion_completa, el inicio y
             el fin de la operación, en ese orden
             de los paréntesis del cálculo que se va a realizar
    Salida: 1 string (str) que representa el valor simplificado
            de la fracción resultante de la operación realizada con
            el formato "X/Y"

    Esta función corta la string expresion_completa a la operación
    encasillada por los dos paréntesis localizados por inicio_y_fin,
    después separa en componentes los elementos de la operación para
    resolverla posteriormente
    """
    # Parte 1: expresion_completa[inicio_y_fin[0]:inicio_y_fin[1]]
    # Acortar la expresión completa a solo la operación con mayor preferencia
    # "(5/6 + -4/8) x (9/5 – (12/5 x 6/4))" -> "12/5 x 6/4"

    # Parte 2: .split(" ")
    # Separar los componentes en elementos de una lista
    # "12/5 x 6/4" -> ["12/5", "x", "6/4"]
    argumentos_calculo = \
        expresion_completa[inicio_y_fin[0]:inicio_y_fin[1]].split(" ")
    # Separar la fracción en 2 números enteros
    # "12/5" -> ["12", "5"] (notar que son strings todavía)
    # Notar que expresion_l -> Expresión de la izquierda, donde
    # el valor 0 es el numerador y el valor 1 es el denominador
    # Y expresion_r -> Expresión de la derecha
    expresion_l = argumentos_calculo[0].split("/")
    expresion_r = argumentos_calculo[2].split("/")
    # Hacer la operación correspondiente al operador guardado
    if argumentos_calculo[1] == "+":
        # Realizar la suma de fracciones para bases diferentes
        # Multiplicamos ambos denominadores
        denominador = int(expresion_l[1]) * int(expresion_r[1])
        # Amplificaciones
        expresion_l[0] = int(expresion_l[0]) * int(expresion_r[1])
        expresion_r[0] = int(expresion_r[0]) * int(expresion_l[1])
        # Suma
        numerador = expresion_l[0] + expresion_r[0]
        # Retorno simplificado
        return simplificar([numerador, denominador])

    # Tomar en cuenta ambos "–" y "-", son simbolos diferentes,
    # pero pueden causar confusión en el usuario, asi que evitamos eso
    if argumentos_calculo[1] == "–" or argumentos_calculo[1] == "-":
        # Desarrollo similar a la suma
        denominador = int(expresion_l[1]) * int(expresion_r[1])
        expresion_l[0] = int(expresion_l[0]) * int(expresion_r[1])
        expresion_r[0] = int(expresion_r[0]) * int(expresion_l[1])
        # Restar en vez de sumar, es el único cambio con respecto a la suma
        numerador = expresion_l[0] - expresion_r[0]
        # Retorno simplificado
        return simplificar([numerador, denominador])

    # Tomar en cuenta ambos "X" y "x", son simbolos diferentes,
    # pero pueden causar confusión en el usuario, asi que evitamos eso
    if argumentos_calculo[1] == "x" or argumentos_calculo[1] == "X":
        # Productos del numerador * numerador y denominador * denominador
        numerador = int(expresion_l[0]) * int(expresion_r[0])
        denominador = int(expresion_l[1]) * int(expresion_r[1])
        # Retorno simplificado
        return simplificar([numerador, denominador])

    # Similar desarrollo a la multiplicación
    if argumentos_calculo[1] == ":":
        # Producto cruzado de denominador * numerador
        numerador = int(expresion_l[0]) * int(expresion_r[1])
        denominador = int(expresion_l[1]) * int(expresion_r[0])
        # Retorno simplificado
        return simplificar([numerador, denominador])


def simplificar(fraccion):
    """
    Entrada: 1 lista (list) con 2 números enteros (int) que representan
             una fracción, numerador y denominador respectivamente
    Salida: 1 string (str) que representa una fracción, de formato
            "X/Y", donde X es el numerador e Y es el denominador.

    Esta función simplifica dos números con su máximo común divisor.
    """
    mcd = sacar_mcd(fraccion[0], fraccion[1])
    # Se dividen ambos por el mcd
    numerador_simplificado = int(fraccion[0] / mcd)
    denominador_simplificado = int(fraccion[1] / mcd)
    return str(numerador_simplificado) \
        + "/" + str(denominador_simplificado)


def sacar_mcd(numero1, numero2):
    """
    Entrada: 2 números enteros (int)
    Salida: 1 número entero (int) que va a ser el mcd de los numeros
            de la entrada

    Esta función itera guardando el resto de la división del primero
    con el segundo, cuando el resto es 0, el último resto es el mcd
    """
    while numero2 > 0:
        resto = numero2
        numero2 = numero1 % numero2
        numero1 = resto
    return numero1


def calcular(entrada):
    """
    Entrada: 1 string (str) con la operación que se desea realizar
             con el formato correcto
    Salida: No retorna nada, ya que los resultados se imprimen
            directamente a la consola

    Esta función se encarga de realizar las operaciones, ordenar e
    imprimir los resultados e iterar este proceso hasta tener
    el resultado de una sola fracción
    """
    # .split necesario para revisar si el resultado esta listo o no
    check_entrada = entrada.split("/")
    # Iterar hasta que la cantidad de argumentos separados por un "/"
    # sea 2, lo que sería una fracción sola
    while len(check_entrada) > 2:
        # Buscar la operación prioritaria
        index_operacion = buscar_calculo_prioritario(entrada)
        if index_operacion == [0, 0]:
            # Si el retorno de buscar_calculo_prioritario() es [0, 0]
            # y hay más de 2 argumentos restantes en la string entrada
            # se asume que debido al retorno de la función
            # resolver_calculo(), la string entrada se debe encontrar
            # así: "X/Y + A/B", entonces se le debe agregar "(" y ")"
            # para que buscar_calculo_prioritario() pueda encontrar
            # correctamente los indices
            entrada = "(" + entrada + ")"
            # Se realiza denuevo la operación
            index_operacion = buscar_calculo_prioritario(entrada)

        # Se calcula el resultado simplificado de la operación
        resultado = resolver_calculo(entrada, index_operacion)

        # Se divide la string entrada en 2 partes:
        # "(5/6 + -4/8) x (9/5 – (12/5 x 6/4))" ->
        # ["(5/6 + -4/8) x (9/5 – ", ")"]
        # (notar que no se incluyen los paréntesis de la operación anterior)
        entrada_a = entrada[:index_operacion[0] - 1]
        entrada_b = entrada[index_operacion[1] + 1:]
        # Se reemplaza la operación con el resultado en la string:
        # "(5/6 + -4/8) x (9/5 – (12/5 x 6/4))" ->
        # "(5/6 + -4/8) x (9/5 – 18/5)"
        entrada = entrada_a + resultado + entrada_b
        # Se imprime el paso realizado
        print(entrada)
        # Se comprueba la nueva cantidad de argumentos separados por "/"
        check_entrada = entrada.split("/")

### BLOQUE PRINCIPAL ###

# Entrada
entrada_ppal = input("Ingrese el problema con el formato correcto: ")

# Procesamiento y Salida
# Ya que se imprimen los resultados en la función calcular()
calcular(entrada_ppal)
