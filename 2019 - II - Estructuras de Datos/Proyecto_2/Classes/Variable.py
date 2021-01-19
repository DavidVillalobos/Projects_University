"""
    Archivo: Variable.py
    Autor: David Villalobos
    Descripcion: Representa una variable, con su tipo de dato, nombre y valor
"""

class Variable:
        def __init__(self, myBlock, name, typeData, value, i):
            self.mistakes = []
            self.myBlock = myBlock
            self.value = None
            try:
                if value: 
                    if typeData == "string":
                        if -1 != value.find('"'):
                            self.value = value[value.find('"')+1:]
                            if -1 != self.value.find('"'):
                                self.value = self.value[:self.value.find('"')]
                            else:  
                                self.mistakes.append(f"Error - Linea {i}: Se esperaba '\"' al final en la definicion de '{name}'")
                                raise Exception("No coincide")
                        else: 
                            self.mistakes.append(f"Error - Linea {i}: Se esperaba '\"' al inicio en la definicion de '{name}'")
                            raise Exception("No coincide") 
                    elif typeData == "int":
                        self.value = int(value)
                    elif typeData == "float":
                        self.value = float(value)#– Línea 8: value de retorno no coincide con la declaración de ‘funcion’
                    else: self.mistakes.append(f"Error - Linea {i}: Tipo de dato '{type}' inexistente")
            except: 
                self.mistakes.append(f"Error - Linea {i}: El valor {value} de '{name}' no coincide con el tipo '{typeData}'")
            self.name = name
            self.typeData = typeData
        
        def __str__(self):
            return f"{self.typeData} {self.name} = {self.value}"
            
        def __repr__(self):
            return self.__str__()