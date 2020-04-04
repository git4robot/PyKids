"""A module for convert.
Version:1.5.1(For python 3.2+)
"""
def to_redix(num, from_radix):
      """
      num ---------- The number for convert.
      from_radix ---------- The radix for convert to DEC.
      """
      _len = len(str(num))
      _list = list(str(num))
      dec = 0
      for x in range(_len - 1, -1, -1):
            dec = dec + int(_list[_len - x - 1]) * (from_radix ** x)
      return dec

def from_redix(num, to_radix):
      """
      num ---------- The number for convert.
      to_radix ---------- The radix to convert with DEC.
      """
      _list = list()
      a = num
      while a:
            to = a % to_radix
            a = (a - to) // to_radix
            _list.append(str(to))
      _list.reverse()
      ret = "".join(_list)
      return int(ret)

def radix(num, a_radix, b_radix):
      """
      num ---------- The number for convert.
      a_radix ---------- The first radix for convert to the second radix.
      b_radix ---------- The second radix for convert to the first radix.
      """
      dec = to_redix(num, a_radix)
      radix = from_redix(dec, b_radix)
      return radix

if __name__ == "__main__":
      print(to_redix(226, 8))
      print(to_redix(96, 16))
      print(to_redix(10010100, 2))
      print("-----")
      print(from_redix(113, 8))
      print("-----")
      print(radix(226, 8, 16))

