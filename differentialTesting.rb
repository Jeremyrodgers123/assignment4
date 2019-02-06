counter = 0;
for i in 0..10000 do
    system("./testGenerator ./testGeneratedInput/coordinates#{i}.txt ./testExpectedOut/coordinates#{i}Out.txt");
    system( "./main ./testGeneratedInput/coordinates#{i}.txt ./outputFiles/output#{i}.txt");
    system( "./tia ./testGeneratedInput/coordinates#{i}.txt ./tiaOut/tOut#{i}.txt");
    
    status = system("diff ./outputFiles/output#{i}.txt ./tiaOut/tOut#{i}.txt")
    if !status
        puts "Check Test #{i}"
        counter += 1;
    end
    #system( "./test.sh ./testExpectedOut/coordinates#{i}Out.txt ./outputFiles/output#{i}.txt #{i}")
end
puts "#{counter} errors found"
puts "***FIN***"

