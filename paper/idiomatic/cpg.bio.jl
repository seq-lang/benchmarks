using BioSequences

m, M = 99999, 0
function cpg(s)
   i, cnt = 1, 0
   mm, MM = 99999, 0
   while i <= length(s)
      cc, l = 0, 0
      while i <= length(s) 
         cc |= if s[i] == DNA_C 1 elseif s[i] == DNA_G 2 else break end
         i += 1
         l += 1
      end
      if cc == 3
         cnt += 1
         mm = min(mm,l)
         MM = max(MM,l)
      end
      i += 1
   end
   global m = min(m,mm)
   global M = max(M,MM)
   cnt
end

function main(arg)
   f = open(arg)
   cnt = 0
   for l in eachline(f)
      cnt += cpg(DNASequence(l))
   end
   println("$cnt $m $M")
end

main(ARGS[1])