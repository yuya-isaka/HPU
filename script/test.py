
f = open('test.txt', 'w')

for i in range(0, 1024):
    f.write('else if (inst[3:0] == 4\'d%d) begin \n' % i)
    f.write('reg1 <= {data[%d:0], data[DIM:%d]};\n' % (i-1, i))
    f.write('end\n')
f.close()