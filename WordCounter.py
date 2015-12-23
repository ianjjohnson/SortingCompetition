f = open('Million.txt', 'r')
out = open('1000.txt', 'w')

num = 0

for line in f:
    for word in line.split():
        if(num < 1000):
            out.write(word + " ")
        num+=1


print(num)
