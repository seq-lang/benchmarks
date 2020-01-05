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

function process(s)
	length(s)
end

function sym(s, k)
	for j in 1:div(k, 2)
		if s[j] != revcomp(s[k - j + 1])
			return 0
		end
	end
	1
end

function main(arg)
	f = open(arg)
	t1, t2, t3 = 0, 0, 0
	for l in eachline(f)
		k, stp = 16, 1
	  i = 1
	  while i + k - 1 <= length(l)
	    sk = l[i:i+k-1]
	    t1 += process(sk)
	   	t2 += 1
	   	t3 += sym(sk, k)
	    i += stp
	  end
	end
	println("$t1 $t2 $t3")
end

main(ARGS[1])