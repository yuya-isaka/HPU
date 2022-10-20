
f = open('test.txt', 'w')

for i in range(11, 1024):
    f.write('else if (permutation == 10\'d%d) begin \n' % i)
    f.write('enc <= enc ^ ({hv[%d:0], hv[DIM:%d]});\n' % (i-1, i))
    f.write('end\n')
f.close()