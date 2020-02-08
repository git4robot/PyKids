from tkinter import *
from tkinter.messagebox import *
tk = Tk()
def radio():
      tk.title('Choose one: (5 + 1 / 3) / (2 + 3 / 5) = ?')
      tk.geometry('500x300')
      var = StringVar()
      l = Label(tk, bg = 'yellow', width = 20, text = 'empty')
      l.pack()
      def print_selection():
            l.config(text = 'You have selected ' + var.get())
      r1 = Radiobutton(tk, text = 'A: 3 / 5', variable = var, value = 'A', command = print_selection)
      r1.pack()
      r2 = Radiobutton(tk, text = 'B: 5 / 10', variable = var, value = 'B', command = print_selection)
      r2.pack()
      r3 = Radiobutton(tk, text = 'C: 39 / 80', variable = var, value = 'C', command = print_selection)
      r3.pack()
      tk.mainloop()
      if str(var.get()) == 'A':
            showwarning(title = 'Wrong', message='错误！')
      elif str(var.get()) == 'B':
            showerror(title = 'Wrong', message='错误！')
      else:
            showinfo(title = 'Correct', message='正确！')
      tk.mainloop()

radio()
