from tkinter import *
import proyecto

def resolver():
    s.set(proyecto.solve(v.get()))
ventana =   Tk()
ventana.config(bd=15)
ventana.title("Calculadora de expresiones algebraicas")
ventana.geometry("360x200")
v = StringVar()
s = StringVar()
      
Label(ventana, text="Introduzca cada operacion\ncon parentesis").pack()
Label(ventana, text="Expresion").pack()
Entry(ventana, justify=CENTER, textvariable=v).pack()

Label(ventana, text="\nResultado").pack()
Entry(ventana, justify=CENTER, state=DISABLED, textvariable=s).pack()
Label(ventana).pack() # Separador
Button(ventana, text="Resolver", command=resolver).pack()
ventana.mainloop()
 