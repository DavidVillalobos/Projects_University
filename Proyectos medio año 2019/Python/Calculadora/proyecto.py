"""
    Fecha: 10/07/2019
    Autor: Luis David Villalobos Gonzalez
    Proyecto: Expresiones algebraicas utilizando Arboles binarios
        Descripcion:
            El siguiete programa lee una expresion algebraica y
            genera una expresion matematica en una lista y convierte esta en 
            notacion prefija para con ella luego crear un arbol binario de 
            dicha expresion para proceder a evaluarlo incluye todas las 
            verificaciones como errores de sintaxis.
        
        Errores y Notas:

"""

class Expresion:
    def __init__(self, expresion):#Inicializador de la clase
        if not isinstance(expresion,str) and not isinstance(expresion,list):
            raise Exception('La expresion debe ser string o una lista')
        self.operadores = { '+':1, '-':1, '*':2, '/':2, '(':3, ')':3}
        self.numeros = {'0':True, '1':True,'2':True, '3':True,'4':True,
                        '5':True,'6':True, '7':True, '8':True, '9':True}
        if not self.verificaDatos(expresion):#Verificando lenguaje
            raise Exception('***Lenguaje invalido***') 
        self.digitos = 0
        self.operaciones = 0
        self.expresion = self.list(expresion)
        if not self.verificaSintaxis(self.expresion): # Verificando numeros y parentesis
            raise Exception('***Error sintactico ***')
            
    def list(self, expresion):#casteo de string a lista
        lista = []
        i = 0
        while i < len(expresion):
            if expresion[i] in self.numeros:
                valor = expresion[i] 
                while i + 1 < len(expresion) and (expresion[ i + 1] in self.numeros or expresion[ i + 1] == ','):
                    i += 1
                    valor += expresion[i]
                lista.append(valor)
                self.digitos += 1
            elif expresion[i] != ' ':
                lista.append(expresion[i])
            i += 1
        return lista
    
    def verificaDatos(self, expresion):# verifica que los datos sean numeros, parentesis o operadores        
        admitidos = dict(self.numeros, **self.operadores)
        admitidos.setdefault(' ',True)
        for valor in expresion:#la busqueda en diccionarios es constante
            if valor not in admitidos: return False
        return True
    
    def verificaParentesis(self, expresion):#verifica que los parentesis esten correctos
        for operador in self.operadores:
            if operador != '(' and operador != ')':
                self.operaciones += expresion.count(operador)
        aux = expresion.count('(') + expresion.count(')')        
        if 0 < aux and aux/2 == self.operaciones:
           return True
        return False
        
    def verificaSintaxis(self, expresion):
        if not self.verificaParentesis(expresion):
            if not self.agregarParentesis(expresion):
                return False
        if not self.digitos-1 == self.operaciones:
            return False
        return True
    
    def agregarParentesis(self, expresion):
        return False
        i = 0
        while i < len(expresion):
            print(expresion)
            if expresion[i] in self.operadores:# (2 * 1) + 3
                if expresion[i] != '(' and expresion[i] != ')': 
                    print("voy por",i)
                    if 0 <= i-1:
                        if expresion[i - 2] != '(':#    (2+2)*2
                            if expresion[i - 2] == ')':
                                if 0 <= i-5:
                                    expresion.insert(i - 4, '(')
                                else: return False
                            else: expresion.insert(i - 5, '(')
                    else: expresion.insert(i - 1, '(')
                    if i+2 < len(expresion):
                        if expresion[i + 2] != ')':
                            expresion.insert(i + 3, ')')
                    else: expresion.insert(i + 3, ')')
            i += 1
        
            # ( # ° # )   ° = operador
            #   (( # ° #) ° # )   ° = operador
        return True 
    def ordenarOperadores(a): # Recibe un diccionario operador:numPrioridad
        for e in range(len(a)):# y lo ordena segun sus valores
            for i in range(e):
                if a[i][1] > a[i+1][1]:
                    a[i], a[i+1] = a[i+1], a[i]
                
    def toString(self,lista):# casteo de lista a string
        expre = ''
        return expre.join(lista)
    
    def __str__(self):
        return self.toString(self.expresion)
    
    def __repr__(self):
        return self.toString(self.expresion)
        
    def invertir(self, expre):#retorna una expresion invertida
        return expre[::-1]
    
    def postFija(self):#Retorna la expresion con post-orden   I-D-P
        before = self.expresion.copy()
        after = []
        pila = []
        while before != []:
            #print(f'before: {before}, after: {after}, pila: {pila}')
            simb = before.pop(0)
            if simb == ')':# pasa todo de la pila hasta '(' a la nueva expresion
                while pila[len(pila)-1] != '(': 
                    after.append(pila.pop())
                pila.pop()# eliminar el (
            elif simb in self.operadores:# es un operador
                pila.append(simb)
                # Before  
                #   Pila  
                #  After 
            else:#Si es un numero lo pone en la nueva expresion
                after.append(simb)# o si es un '('
        while pila != []:
            after.append(pila.pop())
        for i in range(len(after)): #Quitamos los parentesis
            while i < len(after) and (after[i] == ')' or after[i] == '('):
                after.pop(i)
        return after

    def preFija(self):#Retorna la expresion con pre-orden   P-I-D
        return self.invertir(self.postFija())
        
    def inFija(self):#Retorna la expresion en orden I-P-D
        return self.expresion

class Nodo:
    def __init__(self, valor, der = None, izq = None): 
        self.valor = valor
        #if isinstance(der, Nodo) and isinstance(izq, Nodo):
        self.der = der
        self.izq = izq
        #else: raise Exception('***Error izq y der Deben ser Nodos') 
    def evaluar(self):
        if self.der == None and self.izq == None : return int(self.valor)
        if self.valor == '+': return self.izq.evaluar() + self.der.evaluar()
        elif self.valor == '-': return self.izq.evaluar() - self.der.evaluar()
        elif self.valor == '*': return self.izq.evaluar() * self.der.evaluar()
        elif self.valor == '/': return self.izq.evaluar() / self.der.evaluar()
        raise Exception(' Operador inexistente')
    
    def imprimir(self):
        if self.der and self.izq:
            return f'({self.izq.imprimir()} {self.valor} {self.der.imprimir()})'
        return self.valor

    def __repr__(self):
        return str(self.imprimir())
   
    def __str__(self):
        return self.imprimir()
    
class Arbol:
    def __init__(self, raiz):
        self.raiz = raiz
    def evaluar(self):
        return self.raiz.evaluar()
    def imprimir(self):
        return self.raiz.imprimir()
    def __repr__(self):
        return self.imprimir()
    def __str__(self):
        return self.imprimir()
    def insertarNodo(self, raiz):
        self.raiz = raiz
        
def solve(expresion):# Constructor de arbol
    try:
        E = Expresion(expresion)
        #print('La expresion es', E.toString(E.inFija()))
        A = E.preFija()
        #print('La expresion preFija es:',E.toString(A))
        #print('La expresion postFija es:',E.toString(E.postFija()))
        operadores = {'+':True,'-':True,'*':True,'/':True}  
        Construccion = []
        NodoAux = None
        #  ((2+1)*3)
        #  *3+1 2
        #  (2 + 1)  + 3*
        while A != []:
            aux = False
            simb = A.pop()#print(f'{i}){a}  simb:{simb} Construccion: {Construccion} A: {A} Nodo: {NodoAux}')
            while simb not in operadores:#Introduzca todos los numeros hasta un operador
                aux = True
                Construccion.append(simb)
                simb = A.pop()#print(f'{i}){a}  simb:{simb} Construccion: {Construccion} A: {A} Nodo: {NodoAux}')
            if NodoAux == None:# si no hay residuo  
                NodoAux = Nodo(simb, Nodo(Construccion.pop()), Nodo(Construccion.pop()))
            else:# si hay residuo
                if aux:#Colocacion de el residuo
                    NodoAux = Nodo(simb, Nodo(Construccion.pop()), NodoAux)
                else:
                    NodoAux = Nodo(simb, NodoAux, Nodo(Construccion.pop()))
                    #print(f'{i}){a}  simb:{simb} Construccion: {Construccion} A: {A} Nodo: {NodoAux}')
        B = Arbol(NodoAux)
        #print(B)
        #print('SOLUCION: ', B.evaluar())
        return B.evaluar()
    except:
        return "ERROR"