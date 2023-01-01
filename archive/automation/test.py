
f = open('test.txt', 'w')

# for i in range(1, 257):
#     f.write('reg [2:0] stage_1_%d;\n' % i)

# j = 1;
# for i in range(0, 1024, 4):
#     f.write('stage_1_%d <= data[%d] + data[%d] + data[%d] + data[%d];\n' % (j, i, i+1, i+2, i+3))
#     j += 1

# for i in range(1, 65):
#     f.write('reg [4:0] stage_2_%d;\n' % i)

# j = 1;
# for i in range(1, 257, 4):
#     f.write('stage_2_%d <= stage_1_%d + stage_1_%d + stage_1_%d + stage_1_%d;\n' % (j, i, i+1, i+2, i+3))
#     j += 1

# for i in range(1, 17):
#     f.write('reg [6:0] stage_3_%d;\n' % i)

# j = 1;
# for i in range(1, 65, 4):
#     f.write('stage_3_%d <= stage_2_%d + stage_2_%d + stage_2_%d + stage_2_%d;\n' % (j, i, i+1, i+2, i+3))
#     j += 1

# for i in range(1, 5):
#     f.write('reg [8:0] stage_4_%d;\n' % i)

# j = 1;
# for i in range(1, 17, 4):
#     f.write('stage_4_%d <= stage_3_%d + stage_3_%d + stage_3_%d + stage_3_%d;\n' % (j, i, i+1, i+2, i+3))
#     j += 1

f.write('reg [11:0] stage_5_%d;\n' % 1)

j = 1;
for i in range(1, 5, 4):
    f.write('stage_5_%d <= stage_4_%d + stage_4_%d + stage_4_%d + stage_4_%d;\n' % (j, i, i+1, i+2, i+3))
    j += 1

f.close()