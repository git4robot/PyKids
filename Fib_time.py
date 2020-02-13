from time import *
from numpy import *
def Fib_1(n):
      a = time()
      def fib_1(n):
            assert n >= 0, "n > 0"
            if n <= 1:
                return n
            return fib_1(n - 1) + fib_1(n - 2)
      for i in range(1, n + 1):
          print(fib_1(i), end = " ")
      b = time() - a
      print()
      print("耗时：", b)
      del a, b

def Fib_2(n):
      a = time()
      def fib_2(n):
            a, b = 0, 1
            for i in range(n + 1):
                a, b = b, a + b
            return a
      print("1", end = " ")
      for i in range(1, n):
            print(fib_2(i), end = " ")
      b = time() - a
      print()
      print("耗时：", b)
      del a, b

def Fib_3(n):
      a = time()
      def fib_3(n):
            a, b = 0, 1
            while n > 0:
                  a, b = b, a + b
                  n -= 1
                  yield a
      for i in fib_3(n):
            print(i, end = " ")
      b = time() - a
      print()
      print("耗时：", b)
      del a, b

def Fib_4(n):
      a = time()
      def fib_4(n):
            for i in range(n):
                  fib = pow((matrix([[1, 1], [1, 0]], dtype = "int64")), i) * matrix([[1], [0]])
                  print(int(fib[0][0]), end = " ")
      fib_4(n)
      b = time() - a
      print()
      print("耗时：", b)
      del a, b

def Fib_5(n):
      a = time()
      def fib_5(n):
            Matrix = matrix("1 1;1 0", dtype = "int64")
            return linalg.matrix_power(Matrix, n)
      result_list = []
      for i in range(0, n):
            result_list.append(array(fib_5(i))[0][0])
            print(result_list[i], end = " ")
      b = time() - a
      print()
      print("耗时：", b)
      del a, b

def demo():
      Fib_1(25)
      print()
      Fib_2(25)
      print()
      Fib_3(25)
      print()
      Fib_4(25)
      print()
      Fib_5(25)

if __name__ == "__main__":
      demo()
