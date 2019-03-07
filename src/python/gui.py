import tkinter as tk


master = tk.Tk()

#w = tk.Canvas(master, width=40, height=60)
#w.grid(row=0,column=0)

button = tk.Button(master, text='Stop', width=25, command=master.destroy)
button.grid(row=1, column=0, columnspan=2)

var1 = tk.IntVar()
tk.Checkbutton(master, text='male', variable=var1).grid(row=0,column=0)
var2 = tk.IntVar()
tk.Checkbutton(master, text='female', variable=var2).grid(row=0,column=1)

master.mainloop()
