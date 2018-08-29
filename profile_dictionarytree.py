import dictionary_tree
from time import time

d = dictionary_tree.DictionaryTree()

cnt = 0
with open('words_alpha.txt') as fp:
    t1 = time()
    for line in fp:
        d.insert(line[:-1])
        cnt += 1
    t2 = time()
print("insert words:", cnt, "cost time:", t2 - t1, 's')

cnt = 0
with open('words_alpha.txt') as fp:
    t3 = time()
    for line in fp:
        cnt += int(d.find(line[:-1]))
    t4 = time()

print("find words:", cnt, "cost time:", t4 - t3, 's')