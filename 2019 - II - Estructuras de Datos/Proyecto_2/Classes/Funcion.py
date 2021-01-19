"""
    Archivo: Metodo.py
    Autor: David Villalobos
    Descripcion: Representa una funcion, con su cuerpo, valor de retorno y parametros
"""
class Funcion:

        def __init__(self, myBlock, returnType, name):
            self.myBlock = myBlock
            self.returnType = returnType
            self.body = dict()
            self.parameters = list()
            self.name = name
            self.retorno = "void";
            self.mistakes = list()
        
        def addParameter(self, parameter):
            self.parameters.append(parameter)
        
        def addPieceInBody(self, piece):
            self.body.setdefault(piece.name, piece)
        
        def search(self, namePiece):
            for parameter in self.parameters: 
                if parameter.name == namePiece: return parameter
            return self.body.get(namePiece)

        def __str__(self):
            s = f"{self.retorno_name} {self.name}("
            for i in self.parameters:
                s += self.parameters[i]
                if i < len(self.parameters):
                    s += ", "
            s += "){\n"
            for line in self.body.values:
                s+= line + "\n"
            s += "}"
            
        def __repr__(self):
            return self.__str__()