# Old 16-mer experiment (Julia)
# - Sums up the output of "process" function (here just returns k-mer length) 
#   on each 16-mers (step 2) in the file and outputs sum 
#   and total number of processed k-mers

function process(s)
	length(s)
end

function main(arg)
	f = open(arg)
	t1, t2 = 0, 0
	for l in eachline(f)
		k, stp = 16, 2
	  i = 1
	  while i + k <= length(l)
	    sk = l[i:i + k - 1]
	    t1 += process(sk)
	   	t2 += 1
	    i += stp
	  end
	end
	println("$t1 $t2")
end

main(ARGS[1])