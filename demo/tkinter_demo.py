from tkinter import *
from tkinter.messagebox import *
from pickle import *
def choice():
      window = Tk()
      window.title('Website')
      window.geometry('400x300')
      canvas = Canvas(window, width = 400, height = 300)
      canvas.pack(side='top')
      Label(window, text = 'Welcome',font = ('Arial', 16)).pack()
      Label(window, text = 'User name:', font = ('Arial', 14)).place(x = 10, y = 170)
      Label(window, text = 'Password:', font = ('Arial', 14)).place(x = 10, y = 210)
      var_usr_name = StringVar()
      var_usr_name.set('example@python.com')
      entry_usr_name = Entry(window, textvariable = var_usr_name, font = ('Arial', 14))
      entry_usr_name.place(x=120,y=175)
      var_usr_pwd = StringVar()
      entry_usr_pwd = Entry(window, textvariable = var_usr_pwd, font = ('Arial', 14), show = '*')
      entry_usr_pwd.place(x = 120,y = 215)
      def usr_login():
          usr_name = var_usr_name.get()
          usr_pwd = var_usr_pwd.get()
          try:
              with open('usrs_info.pickle', 'rb') as usr_file:
                  usrs_info = load(usr_file)
          except FileNotFoundError:
              with open('usrs_info.pickle', 'wb') as usr_file:
                  usrs_info = {'admin': 'admin'}
                  dump(usrs_info, usr_file)
                  usr_file.close()
          if usr_name in usrs_info:
              if usr_pwd == usrs_info[usr_name]:
                  showinfo(title = 'Welcome', message = 'How are you? ' + usr_name)        
              else:
                  showerror(message = 'Error, your password is wrong, try again.')
          else:
              is_sign_up = askyesno('Welcome！', 'You have not sign up yet. Sign up now?')
              if is_sign_up:
                  usr_sign_up()
                  
      def usr_sign_up():
          def sign_to_Website():
              np = new_pwd.get()
              npf = new_pwd_confirm.get()
              nn = new_name.get()
              with open('usrs_info.pickle', 'rb') as usr_file:
                  exist_usr_info = pickle.load(usr_file)
              if np != npf:
                  showerror('Error', 'Password and confirm password must be the same!')
              elif nn in exist_usr_info:
                  showwarning('Error', 'The user has already signed up!')
              else:
                  sssexist_usr_info[nn] = np
                  with open('usrs_info.pickle', 'wb') as usr_file:
                        pickle.dump(exist_usr_info, usr_file)
                  showinfo('Welcome', 'You have successfully signed up!')
                  window_sign_up.destroy()
          window_sign_up = Toplevel(window)
          window_sign_up.geometry('300x200')
          window_sign_up.title('Sign up window')
          new_name = StringVar()
          new_name.set('example@python.com')
          Label(window_sign_up, text = 'User name: ').place(x = 10, y = 10)
          entry_new_name = Entry(window_sign_up, textvariable = new_name)
          entry_new_name.place(x = 130, y = 10)
          new_pwd = StringVar()
          Label(window_sign_up, text = 'Password: ').place(x = 10, y = 50)
          entry_usr_pwd = Entry(window_sign_up, textvariable = new_pwd, show = '*')
          entry_usr_pwd.place(x = 130, y = 50)
          new_pwd_confirm = StringVar()
          Label(window_sign_up, text = 'Confirm password: ').place(x = 10, y = 90)
          entry_usr_pwd_confirm = Entry(window_sign_up, textvariable = new_pwd_confirm, show = '*')
          entry_usr_pwd_confirm.place(x = 130, y = 90)
          btn_comfirm_sign_up = Button(window_sign_up, text = 'Sign up', command = sign_to_Website)
          btn_comfirm_sign_up.place(x = 180, y = 120)
      btn_login = Button(window, text = 'Login', command = usr_login)
      btn_login.place(x = 120, y = 240)
      btn_sign_up = Button(window, text = 'Sign up', command = usr_sign_up)
      btn_sign_up.place(x = 200, y = 240)
      window.mainloop()

choice()
