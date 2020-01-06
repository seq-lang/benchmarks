using BioSequences

function rcc(s)
   b = reverse_complement(s)
	println(String(b))
	length(b)
end

function main(arg) 
	f = open(arg)
	total = 0
	for l in eachline(f)
	   total += rcc(DNASequence(l))
	end
	println("$total")
end

main(ARGS[1])