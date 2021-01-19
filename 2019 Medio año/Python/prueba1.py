def list(expre):
    numbers = { str(i):True for i in range(10)}
    a = []
    i = 0
    while i < len(expre):
        if expre[i] in numbers:
            valor = expre[i] 
            while i + 1 < len(expre) and expre[ i + 1] in numbers:
                i += 1
                valor += expre[i]
            a.append(valor)
        else:
            a.append(expre[i])
        i += 1
    return a
    
def addParenthesis(a):
    numbers = { str(i):True for i in range(10)}
    operators = {"+":0, "-":0, "/":1, "*":1, "^":2, "(":3, ")":3}
    numeros = []
    operadores = []
    for val in a: 
        if val in operators:
            operadores.append((val,operators[val]))
        else:
            numeros.append(val)
    sort(operadores)
    i,j = 0,0
    a.clear()
    while True:# 2+2*3            
        if j < len(operadores):
            a.append(operadores[j][0])
            j += 1
        elif i < len(numeros):
            a.append(numeros[i])
            i += 1
        else:
            break
    
def sort(a):
    for numPasada in range(len(a)):
        for i in range(numPasada):
            if a[i][1] > a[i+1][1]:
                a[i], a[i+1] = a[i+1], a[i]
                
def strg(a):
    expre = ""
    return expre.join(a)
    
def verif(a):
    if a == []: return 0
    cant1 = a.count('(') 
    cant2 = a.count(')')
    if cant1 > cant2: return 1
    elif cant1 < cant2: return 2
    return 3
def rec_exp(a): a.pop(0) # Corrimiento a la derecha
def sim(s): 
    operators = "+-*/()"
    return s in operators# es un operador
def prio(s1, s2):# quien tiene mas prioridad
    operators = ["+-","*/","()"]
    p1 = p2 = i = 0
    for row in operators:
        if s1 in row:
            p1 = i
        if s2 in row:
            p2 = i
        i += 1
    if p1 < p2:# p2 tiene prioridad
        return -1
    elif p1 == p2: # misma prioridad
        return 0
    else: # p1 tiene prioridad
        return 1

def conv_pos(expr):#((2+2)*3)   [((2]  +2)*3)
    before = expr.copy()
    after = []
    pila = []
    while before != []:
        #print(f"before: {before}, after: {after}, pila: {pila}")
        simb = before.pop(0)
        if simb == '(':#lo inserta a la pila
            pila.append(simb)
        elif simb == ')':# pasa todo de la pila hasta '(' a la nueva expresion
            while 0 <= len(pila)-1 and pila[len(pila)-1] != '(':
                after.append(pila.pop())
            if pila != []:
                pila.pop()
        elif sim(simb):# es un operador
            if pila != []:# la pila no esta vacia
                while 0 <= len(pila)-1 and prio(simb, pila[len(pila)-1]) <= 0:#prioridad   -1   1,  o ambos
                    after.append(pila.pop())#inserta todo lo que esta en la pila 
                    if len(pila) < 0:
                        break;
            pila.append(simb)#si la pila esta vacia se inserta sin importar prioridad
        else:#Si es un numero lo pone en la nueva expresion
            after.append(simb)
    while pila != []:
        after.append(pila.pop())
    for i in range(len(after)):
        while i < len(after) and (after[i] == ')' or after[i] == '('):
            after.pop(i)
    return after

def inver(expre):
    before = expre.copy()
    before.reverse()
    return [ i for i in before]
    
def conv_pre(expre):
    return inver(conv_pos(expre))
    
if __name__ == '__main__':
    while True:
        #expr = list(input("Digite la expresion:"))
        expr = list("(2+((5*3)/4))")#list(input())#"((2+2)*3)"
        if verif(expr) != 3:
            print("La expresion no es valida",expr)
            i = verif(expr)
            if  i == 0: print("esta mal la funcion")
            elif i == 1: print("le faltan parentesis derechos")
            elif i == 2: print("le faltan parentesis izquierdos.")
            input()
        else: break
    print(f"La conversion a postfija es: {conv_pos(expr)}")
    print(f"La conversion a prefija es: {conv_pre(expr)}")