f_in = open('triangles.in', 'r')
f_out = open('triangles.out', 'w')

n = int(f_in.read())
f_out.write(str(int((n*(n + 2)*(2 * n + 1)) / 8)))

f_in.close()
f_out.close()