# 786

function revcomp(c)
	if c == 'A' 
		'T'
	elseif c == 'C' 
		'G'
	elseif c == 'G' 
		'C'
	elseif c == 'T' 
		'A'
	else 
		c 
	end
end

function rcc(s)
	b = collect(s)
	for i in 1:length(s) 
		b[i] = revcomp(s[length(s) - i + 1])
	end
	println(String(b))
	length(s)
end

function main(arg) 
	f = open(arg)
	total = 0
	for l in eachline(f)
	   total += rcc(l)
	end
	println("$total")
end

main(ARGS[1])