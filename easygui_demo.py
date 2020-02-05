"""A module that can regester and login.
Version: 2.0.0 - Chinese (For python 3.0+)"""
from easygui import *
__all__ = ["choice"]

def regester():
      """For regester"""
      global fieldValues
      msg = "请填写一下信息(用户名5位，手机号码11位，纯数字密码5位）"
      title = "注册"
      fieldNames = ["用户名", "手机号码", "密码"]
      fieldValues = []
      fieldValues = multenterbox(msg,title,fieldNames)
      print("您填写的资料如下:  %s"  % str(fieldValues))
      a = msgbox(msg="注册成功！",title="注册",ok_button="关闭")
      file = open("password.txt", "w")  #"password.txt" Can edit location
      file.write(str(fieldValues))
      file.close()

def login():
      """For login"""
      msg = "请输入信息"
      title = "登录"
      file = open("password.txt", "r")  #"password.txt" Can edit location
      out = file.readline()
      while True:
            value = []
            value = multpasswordbox(msg,title,("用户名","密码"))
            mm = out[26] + out[27] + out[28] + out[29] + out[30]
            yhm = out[2] + out[3] + out[4] + out[5] + out[6]
            if value[0] == yhm:
                  if value[1] == mm:
                        break
            print("密码错误")
      a = msgbox(msg="登录成功！",title="登录",ok_button="关闭")

def choice():
      """This function can run"""
      if ccbox("请选择",choices=("注册", "登录")):
            regester()
      else:
            login()

     
if __name__ == "__main__":
      choice()

      
