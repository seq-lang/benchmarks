using BioSequences
using Match

function process(s)
   length(s)
end

function is_sym(k)
   return k == reverse_complement(k)
end

function main(arg)
   f = open(arg)
   t1, t2, t3 = 0, 0, 0
   for l in eachline(f)
      s = DNASequence(l)
      k, stp = 16, 1
      i = 1
      for (_, codon) in each(DNAKmer{k}, s, stp) 
         t1 += process(codon)
         t2 += 1
         t3 += is_sym(codon)
      end
   end
   println("THIS IS NOT THE SAME AS SEQ OUTPUT: BioSequences API does no handle k-mers with N (as is faster than it should be)!")
   println("$t1 $t2 $t3")
end

main(ARGS[1])