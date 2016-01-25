def loops(num, dev):
	x = 0
	while (num%dev):
		num = (256-(dev-num%dev))
		x += 1
	return x

def solve(num, dev):
	loop = loops(num,dev)
	ogloop = loop
	if (loop%2):
		loop -= 1

	diff = loop/2 + (num/dev) + 1

	print "Diff: %i" % diff

	out = ogloop * (256/dev) + diff

	return out

print solve(50,7)
print solve(76,7)
print solve(48,3)
print solve(49,3)
print solve(53,3)