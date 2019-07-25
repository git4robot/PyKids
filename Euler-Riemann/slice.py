

l = list(range(0, 11))

print(l)

print("[::-1]:", l[::-1])
print("[3:8:3]:", l[3:8:3])
print("[8:3:-1]:", l[8:3:-1])
print("[3:8:-1]:", l[3:8:-1])
print("[:8:-1]:", l[:8:-1])
print("[3::-1]:", l[3::-1])
print("[3:8]:", l[3:8])
print("[8:3]:", l[8:3])
print("[:8]:", l[:8])
print("[3:]:", l[3:])
print("[3:-1]:", l[3:-1])
print("[-3:9]:", l[-3:9])
print("[-3:]:", l[-3:])
print("[:-3]:", l[:-3])
print("[-3:-8]:", l[-3:-8])
print("[-8:-3]:", l[-8:-3])
print("-----------------------------------------------------")

filepath = u"F:/Datasets/JamesVoice/5000/p001/002神农尝百草.mp3"
print(filepath)
print("filename:", filepath[-12:])
print("filefolder:", filepath[:-12])
print("title:", filepath[-12:-4])
