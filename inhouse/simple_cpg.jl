# Old CpG experiment (Julia)
# - Counts the number of non-overlapping [CG]+ regions 

function is_cpg(s)
   s == 'C' || s == 'G' 
end

function cpg(s)
   i, cnt = 1, 0
   while i <= length(s)
      if is_cpg(s[i]) 
         j = i + 1
         while j <= length(s) && is_cpg(s[j])
            j += 1
         end
         cnt += 1
         i = j + 1
      else
         i += 1
      end
   end
   cnt
end

function main(arg)
   f = open(arg)
   cnt = 0
   for l in eachline(f)
      cnt += cpg(l)
   end
   println("$cnt")
end

main(ARGS[1])