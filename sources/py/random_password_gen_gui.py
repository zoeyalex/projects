import tkinter as tk
import string
import random

def pass_chars():
    return string.ascii_letters + string.digits + string.punctuation


def generate_pass(length):
    return "".join(random.choices(pass_chars(), k=length))


class Application(tk.Frame):

    def __init__(self, window):
        super().__init__(window)

        style = {"background": "slateblue4", "foreground": "khaki1"}

        self.greet = tk.Label(window, text=(
            "Welcome to the random password generator!"
            "\nPlease enter your desired password's length: "
        ))
        self.greet.place(relx=0.5, rely=0.3, anchor=tk.CENTER)
        self.greet.configure(font=("Consolas", 9, "bold"), **style)

        self.entry = tk.Entry(window)
        self.entry.place(height=20, width=20, relx=0.5, rely=0.5, anchor=tk.CENTER)

        self.button = tk.Button(window, text="generate", command=self.generate)
        self.button.place(height=20, width=55, relx=0.5, rely=0.65, anchor=tk.CENTER)
        self.button.configure(font=("Consolas", 7, "bold"), **style)


        self.text = tk.StringVar()
        self.text.set("")

        self.output = tk.Label(window, textvariable=self.text)
        self.output.place(height=20, width=400, relx=0.5, rely=0.8, anchor=tk.CENTER)
        self.output.configure(font=("Consolas", 9, "bold"), **style)

        self.photo = tk.PhotoImage(file=r"C:\Users\zoey\Desktop\cancel.png")

        self.exit = tk.Button(window, image=self.photo, command=window.destroy)
        self.exit.configure(background="slateblue4")
        self.exit.place(height=20, width=20, relx=0.95, rely=0.1, anchor=tk.CENTER)

        #self.pack(fill="both", expand=True) #  geometry manager that organizes widgets in blocks


    def generate(self):
        try:
            length = int(self.entry.get())
        except ValueError:
            self.text.set("please enter a base-10 number")
        else:
            self.text.set(generate_pass(length))


def main():
    window = tk.Tk() # create root window
    window.title("Random Password Generator")
    window.geometry("400x200")
    window.geometry("+600+200")
    window.configure(background="slateblue4")
    window.overrideredirect(True) # title bar presence
    Application(window) # app
    window.mainloop() # execute tkinter


if __name__ == "__main__":
    main()