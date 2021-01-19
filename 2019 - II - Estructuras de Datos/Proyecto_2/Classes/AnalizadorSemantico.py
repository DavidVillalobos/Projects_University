"""
    Archivo: AnalizadorSemantico.py
    Autor: David Villalobos
    Descripcion: Esta clase se encarga de analizar el code fuente
"""
from Classes.Funcion import  Funcion
from Classes.Variable import Variable
from Classes.Reservada import Reservada

class AnalizadorSemantico:   

    def __init__(self, path):
        self.path = path
        self.code = self.getLines(path)
        self.mistakes = list()
        self.globalVariables = dict()
    
    def getMistakes(self):
        if self.mistakes == []:
            mistakes = f"El programa {self.path} compilo correctamente"
        else:
            mistakes = "Lista de errores\n"
            for mistake in self.mistakes: mistakes += mistake + '\n'
        return mistakes
        
    def getCode(self):
        code = "          SOURCE CODE\n"
        i = 1
        for line in self.code:
            code += f" {i} | {line}"
            i += 1
        return code

    def getLines(self, path):    
        file = open(path, "r")
        return file.readlines()

    def compileCode(self):
        self.examineCode()
        result = self.getCode() + "\n"
        result += self.getMistakes()
        return result

    def __str__(self): return self.compileCode()
            
    def __repr__(self): return self.__str__()
        
    def examineCode(self):
        i = 1
        CurrentBlock = Funcion(None, "void", "global")#Bloque de variables globales
        self.globalVariables = CurrentBlock
        for line in self.code:
            if line.split() != []:#Si la linea no esta vacia
                if -1 == line.find('if') and -1 == line.find('while') and - 1 != line.find('='):# si es una asignacion de variable (declaracion o cambio de valor)
                    if line.find("string") == line.find("int") == line.find("float") == -1:
                        self.redefineVariable(i, line, CurrentBlock)
                    else:
                        aux = self.makeVariable(CurrentBlock, i, line)
                        if aux: CurrentBlock.addPieceInBody(aux)# Anadir al bloque
                elif 0 <= line.find('{'):# Si es un bloque abriendo
                    CurrentBlock = self.makeBlock(CurrentBlock, i, line)
                    CurrentBlock.myBlock.addPieceInBody(CurrentBlock)#agregar al bloque anterior
                elif -1 != line.find('return'): 
                    self.readRetorn(CurrentBlock, i, line)
                    CurrentBlock.myBlock.mistakes.extend(CurrentBlock.mistakes)
                elif 0 <= line.find('}'):# si es un bloque cerrando
                    if(CurrentBlock.name != "global"):
                        CurrentBlock.myBlock.mistakes.extend(CurrentBlock.mistakes)
                        CurrentBlock = CurrentBlock.myBlock# actual debe devolverse al anterior
                    else: self.mistakes.append(f"Error - Linea {i}: Tipo de declaracion o definicion desconocida en la linea {line}")
                i += 1
        while CurrentBlock.name != "global":
            self.mistakes.append(f"Error - Linea {i}: No se encontro la llave de cierre de la funcion '{CurrentBlock.name}'")
            CurrentBlock.myBlock.addPieceInBody(CurrentBlock)#agregar al bloque anterior
            CurrentBlock.myBlock.mistakes.extend(CurrentBlock.mistakes)
            CurrentBlock = CurrentBlock.myBlock# actual debe devolverse al anterior
            self.mistakes.extend(self.globalVariables.mistakes)
    
    def getValue(self, block, typeData, name, value, i):
        try: return int(value)
        except:
            try: return float(value)
            except:
                if -1 != value.find('"') and -1 != value[value.find('"')+1:].find('"'):
                    return value
                blockTmp = block
                aux = None
                while blockTmp:
                    aux = blockTmp.search(value)
                    if aux: break;
                    blockTmp = blockTmp.myBlock
                if aux:
                    if aux.typeData == typeData: return aux.value
                    else: self.mistakes.append(f"Error - Linea {i}: El valor {value} de '{name}' no coincide con el tipo '{typeData}'")
                else: self.mistakes.append(f"Error - Linea {i}: la variable '{name}' no esta declarada")

    def makeVariable(self, block, i, line):
        def cheakValue(block, typeData, name, value, i):
            if len(value.split()) == 1:
                value = value.split()[0]
                return self.getValue(block, typeData, name, value, i)
            else: 
                if -1 != value.find('+') or -1 != value.find('-') or -1 != value.find('*') or -1 != value.find('/'):
                    values = value.split()#m + 4 
                    if len(values) >= 3:
                        if values[1] == '+' or values[1] == '-' or values[1] == '*' or values[1] == '/':
                            A = self.getValue(block, typeData, name, values[0], i)
                            B = self.getValue(block, typeData, name, values[2], i)
                            if A and B:
                                if typeData == "string" and -1 != A.find('"'):
                                    A = A[A.find('"')+1:]
                                    if -1 != A.find('"'):
                                        A = A[:A.find('"')]
                                if typeData == "string" and -1 != B.find('"'):
                                    B = B[B.find('"')+1:]
                                    if -1 != B.find('"'):
                                        B = B[:B.find('"')]
                                tipoA = str(type(A))
                                tipoA = tipoA[tipoA.find("\'")+1:]
                                tipoA = tipoA[:tipoA.find("\'")]
                                tipoB = str(type(B))
                                tipoB = tipoB[tipoB.find("\'")+1:]
                                tipoB = tipoB[:tipoB.find("\'")]
                                if tipoA == "str": tipoA += "ing"  
                                if tipoB == "str": tipoB += "ing"  
                                if tipoA == typeData and tipoB == typeData:
                                    result = None
                                    try:
                                        if values[1] == '+': result = A + B
                                        if values[1] == '-': result = A - B
                                        if values[1] == '*': result = A * B
                                        if values[1] == '/': result = A / B
                                    except: return None
                                    if typeData == "string": result = '\"' +  result + "\""
            if -1 != value.find('"') and -1 != value[value.find('"')+1:].find('"'): return value
            return None
            
        if -1 !=line.find(';'):
            line = line[:line.find(';')]#Eliminar el ;\n
            sentence = line.split()
            if len(sentence) >= 4:
                value = cheakValue(block, sentence[0], sentence[1], line[line.find("=")+1:], i)
                blockTmp = block
                aux = None
                while blockTmp:
                    aux = blockTmp.search(sentence[1])
                    if aux: break;
                    blockTmp = blockTmp.myBlock
                if aux:
                    self.mistakes.append(f"Error - Linea {i}: la variable '{sentence[1]}' ya esta declarada")
                else:
                    aux = Variable(block, sentence[1], sentence[0], value, i)
                    self.mistakes.extend(aux.mistakes)
                if aux.value: return aux
            else: self.mistakes.append(f"Error - Linea {i}: Declaracion de variable invalida")
        else: self.mistakes.append(f"Error - Linea {i}: Se esperaba el simbolo ';' al final de la linea")
        
    def makeBlock(self, blockPrev, i, line, ):
        if -1 !=line.find("("):
            sentence =  line[:line.find("(")].split()
            if len(sentence) == 1:
                if sentence[0] == "if" or sentence[0] == "while":
                    newCondicional = Reservada(blockPrev, sentence[0], None, None, None)
                    condicion =  line[line.find("(")+1:line.find(")")]
                    operadorLogico = None
                    for e in ['>','<','<=','>=','==','!=']:
                        if condicion.find(e) != -1:
                            operadorLogico = e
                            break
                    if operadorLogico: #    A  <  B 
                        newCondicional.valorA = condicion[:condicion.find(operadorLogico)] 
                        newCondicional.valorB = condicion[condicion.find(operadorLogico)+len(operadorLogico):] 
                        newCondicional.operadorLogico = operadorLogico
                    else: self.mistakes.append(f"Error - Linea {i}: Operador logico no encontrado")
                    return newCondicional
                else: self.mistakes.append(f"Error - Linea {i}: Declaracion de funcion invalida")
            else: 
                blockTmp = blockPrev
                aux = None
                while blockTmp:
                    aux = blockTmp.search(sentence[1])
                    if aux: break;
                    blockTmp = blockTmp.myBlock
                if aux:
                    self.mistakes.append(f"Error - Linea {i}: la funcion '{sentence[1]}' ya se encuentra declarada")
                newFuncion = Funcion(blockPrev, sentence[0], sentence[1])
                parametros =  line[line.find("(")+1:line.find(")")]
                if parametros != '':
                    parametros = parametros.split(',')
                for var in parametros:
                    aux = var.split()
                    newFuncion.addParameter(Variable(newFuncion, aux[1], aux[0], None ,i))
                return newFuncion 
        else: self.mistakes.append(f"Error - Linea {i}: Declaracion invalida")
        
    def redefineVariable(self, i, line, block):
        if -1 !=line.find(';'):
            line = line[:line.find(';')]#Eliminar el ;
            sentence = line.split()# slice de la linea
            if len(sentence) == 3:
                name = sentence[0]
                value = line[line.find("=")+1:]
                blockTmp = block 
                aux = None
                while blockTmp:
                    aux = blockTmp.search(name)
                    if aux: break;
                    blockTmp = blockTmp.myBlock
                if aux: 
                    try:
                        if aux.typeData == "string":
                            if -1 != value.find('"'):
                                value = value[value.find('"')+1:]
                                if -1 != value.find('"'):
                                    value = value[:value.find('"')]
                                else:  
                                    self.mistakes.append(f"Error - Linea {i}: Se esperaba '\"' al final en la definicion de '{nombre}'")
                                    raise Exception("Valor no coincide con el tipo")
                            else: 
                                self.mistakes.append(f"Error - Linea {i}: Se esperaba '\"' al inicio en la definicion de '{nombre}'")
                                raise Exception("Valor no coincide con el tipo") 
                        elif aux.typeData == "int":
                            value = int(value)
                        elif aux.typeData == "float":
                            value = float(value)
                        else: self.mistakes.append(f"Error - Linea {i}: Tipo de dato '{type}' inexistente")
                    except: 
                        while blockTmp:
                            aux2 = blockTmp.search(sentence[2])
                            if aux2: break;
                            blockTmp = blockTmp.myBlock
                        if aux2:
                            if aux2.typeData != aux.typeData:
                                self.mistakes.append(f"Error - Linea {i}: El valor '{value}' no coincide con el tipo de dato '{aux.typeData}' de '{name}'")
                        else: self.mistakes.append(f"Error - Linea {i}: '{name}' no esta declarada")
                else: self.mistakes.append(f"Error - Linea {i}: '{name}' no esta declarada")
            elif len(sentence) > 3:
                if sentence[3] == '+' or sentence[3] == '-' or sentence[3] == '*' or sentence[3] == '/':
                    blockTmp = block 
                    aux = None
                    while blockTmp:
                        aux = blockTmp.search(sentence[0])
                        if aux: break;
                        blockTmp = blockTmp.myBlock
                    if aux: 
                        A = self.getValue(block, aux.typeData, sentence[0], sentence[2], i)
                        B = self.getValue(block, aux.typeData, sentence[0], sentence[4], i)
                        if A and B:
                            try:
                                if aux.typeData == "string" and -1 != A.find('"'):
                                    A = A[A.find('"')+1:]
                                    if -1 != A.find('"'):
                                        A = A[:A.find('"')]
                                if aux.typeData == "string" and -1 != B.find('"'):
                                    B = B[B.find('"')+1:]
                                    if -1 != B.find('"'):
                                        B = B[:B.find('"')]
                            except: print(" ",end="")
                            tipoA = str(type(A))
                            tipoA = tipoA[tipoA.find("\'")+1:]
                            tipoA = tipoA[:tipoA.find("\'")]
                            tipoB = str(type(B))
                            tipoB = tipoB[tipoB.find("\'")+1:]
                            tipoB = tipoB[:tipoB.find("\'")]
                            if tipoA == "str": tipoA += "ing"  
                            if tipoB == "str": tipoB += "ing"  
                            if tipoA == aux.typeData and tipoB == aux.typeData:
                                result = ""
                                try:
                                    if sentence[3] == '+': result = A + B
                                    if sentence[3] == '-': result = A - B
                                    if sentence[3] == '*': result = A * B
                                    if sentence[3] == '/': result = A / B
                                except: return None
                                if aux.typeData == "string": result = '\"' +  result + "\""
                    else: self.mistakes.append(f"Error - Linea {i}: '{sentence[0]}' no esta declarada")
                elif -1 != line.find('"') and -1 != line[line.find('"')+1:].find('"'): 
                    val = line[line.find('\"')+1:]
                    val = val[:val.find('\"')]
                    name = sentence[0]
                    blockTmp = block 
                    aux = None
                    while blockTmp:
                        aux = blockTmp.search(name)
                        if aux: break;
                        blockTmp = blockTmp.myBlock
                    if aux: 
                        if aux.typeData != "string":
                            self.mistakes.append(f"Error - Linea {i}: El valor '{val}' no coincide con el tipo de dato '{aux.typeData}' de '{name}'")
                    else: self.mistakes.append(f"Error - Linea {i}: '{val}' no esta declarada")

    def readRetorn(self, block, i, line):
        if -1 !=line.find(';'):
            line = line[:line.find(';')]#Eliminar el ;\n
            sentence = line.split()
            blockTmp = block
            aux = None
            while blockTmp:
                aux = blockTmp.search(sentence[1])
                if aux: break;
                blockTmp = blockTmp.myBlock
            if aux:
                if block.returnType != aux.typeData:
                    self.mistakes.append(f"Error – Línea {i}: Valor de retorno no coincide con la declaración de '{block.name}'")
                block.retorno = sentence[1]
            else: self.mistakes.append(f"Error - Linea {i}: '{sentence[1]}' no esta declarado")
        else: self.mistakes.append(f"Error - Linea {i}: Se esperaba el simbolo ';' al final de la linea")