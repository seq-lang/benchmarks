# 786

function is_cpg(s)
   if s == 'C' 1 
   elseif s == 'G' 2
   else 0
   end
end

m, M = 99999, 0
function cpg(s)
   i, cnt = 1, 0
   while i <= length(s)
      cc, l = 0, 0
      while i <= length(s) 
         c = is_cpg(s[i])
         if c == 0 break end
         cc |= c
         i += 1
         l += 1
      end
      if cc == 3
         cnt += 1
         global m = min(m,l)
         global M = max(M,l)
      end
      i += 1
   end
   cnt
end

function main(arg)
   f = open(arg)
   cnt = 0
   for l in eachline(f)
      cnt += cpg(l)
   end
   println("$cnt $m $M")
end

main(ARGS[1])