"""
    Archivo: Reservada.py
    Autor: David Villalobos
    Descripcion: Representa las palabras reservadas condicionales
    'If' y 'While'
"""
class Reservada:
    def __init__(self, myBlock, name, valorA, operadorLogico, valorB):
        self.myBlock = myBlock
        self.name = name
        self.valorA = valorA
        self.operadorLogico = operadorLogico
        self.valorB = valorB 
        self.body = dict()
        self.mistakes = list()
    
    def addPieceInBody(self, piece):
        self.body.setdefault(piece.name, piece)

    def search(self, namePiece):
        return self.body.get(namePiece)