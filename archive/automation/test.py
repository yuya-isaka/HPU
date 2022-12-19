
f = open('test.txt', 'w')

for i in range(0, 64):
    f.write('else if ( item_a_tmp == 6\'d%d ) begin \n' % i)
    f.write('rand_num[ %d:%d ] <= rand_num_tmp;\n' % (31+32*i, 32*i))
    f.write('end\n')
f.close()