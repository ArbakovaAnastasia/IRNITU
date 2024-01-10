print('1. Все нечетные элементы сортируются по возрастанию.')
print('2. Все четные элементы сортируются по убыванию.')
print('3. Нули не меняют своих позиций.')
massive = [[1, 6, 1, 0, 5, 2], [8, 1, 6, 1, 4, 2], [8, 0, 3, 5, 2, 2], [8, 3, 7, 7, 0, 2]]
print('Матрица:')
for i in range(0, len(massive)):
    for i2 in range(0, len(massive[i])):
        print(massive[i][i2], end='  ')
    print()
chet = []
nechet = []
for i in range(0, len(massive)):
    for j in range(0, len(massive[i])):
        if massive[i][j] % 2 == 0 and massive[i][j] != 0:
            chet.append(massive[i][j])
        elif massive[i][j] % 2 == 1:
            nechet.append(massive[i][j])
chet.sort(reverse=True)
nechet.sort()
q=0
p=0
print('Полученная матрица:')
for i in range(0, len(massive)):
    for j in range(0, len(massive[i])):
        if massive[i][j] % 2 == 0 and massive[i][j] != 0:
            print(chet[q], end='  ')
            q=q+1
        elif massive[i][j] % 2 == 1:
            print(nechet[p], end='  ')
            p=p+1
        else:
            print(massive[i][j], end='  ')
    print()