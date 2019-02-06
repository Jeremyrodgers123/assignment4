
for i in 0..10 do
    system( "./main ./testGeneratedInput/coordinates#{i}.txt ./outputFiles/output#{i}.txt");
    system( "./tia ./testGeneratedInput/coordinates#{i}.txt ./tiaOut/tOut#{i}.txt");
    
    status = system("diff ./outputFiles/output#{i}.txt ./tiaOut/tOut#{i}.txt")
    if !status
        puts "Check Test #{i}"
    end
    #system( "./test.sh ./testExpectedOut/coordinates#{i}Out.txt ./outputFiles/output#{i}.txt #{i}")
end

puts "***FIN***"

