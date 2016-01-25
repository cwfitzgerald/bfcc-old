in_str = raw_input("Enter text to convert\n> ")
in_int = map(ord, in_str)
avg = sum(in_int)/len(in_int)

output = ""

output = "".join("+" for _ in xrange(avg))
output += "[-"
output += "".join([">+" if in_int[x]>(avg/2) else ">" for x in xrange(len(in_int))])
output += "".join(["<" for _ in xrange(len(in_int))])
output += "]"

last = 0

for i in in_int:
	output += ">"
	if i > avg/2:
		output += "".join("+" if (i-avg > 0) else "-" for _ in xrange(abs(avg-i)))
	else:
		output += "".join("+" for _ in xrange(abs(i)))
	last = i
	
print output