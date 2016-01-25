from random import choice

letters = "abcdefghij"

for i in xrange(1000):
	print "".join([choice(letters), choice(letters)])

for i in xrange(1000):
	print ""

print " \nq"