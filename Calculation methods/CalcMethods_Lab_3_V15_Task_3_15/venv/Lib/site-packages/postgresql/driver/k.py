g = 'GlobalData'
def lfact(y):
	g = 'LocalData'
	return lambda p: g + p + y
import dis
dis.dis(lfact('Last'))
