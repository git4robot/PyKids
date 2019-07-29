import find_primes as f_p
start_tm = time()
f_p.find_twins(5000)
f_p.find_reverse(2500)
f_p.find_palindromes(25000)
f_p.find_square_palindromes(10000000)
print("耗时：%f" % (time() - start_tm))
    

    