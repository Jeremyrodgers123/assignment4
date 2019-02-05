#run tester 1000 times
#label the output
prevCoverage = "blanktest"
for i in 0..1000 do
    system("./testGenerator ./testGeneratedInput/coordinates#{i}.txt ./testExpectedOut/coordinates#{i}Out.txt");
    system( "./main ./testGeneratedInput/coordinates#{i}.txt ./outputFiles/output#{i}.txt");
    system("xcrun llvm-profdata merge -sparse #{prevCoverage}.profdata default.profraw -o #{i}.profdata");
    #system("diff ./testExpectedOut/coordinates#{i}Out.txt ./outputFiles/output#{i}.txt")
    system( "./test.sh ./testExpectedOut/coordinates#{i}Out.txt ./outputFiles/output#{i}.txt #{i}")
    # puts ""
    system("rm #{prevCoverage}.profdata")
    #puts ""
    prevCoverage = "#{i}"
end

system("xcrun llvm-profdata merge -sparse #{prevCoverage}.profdata -o main.profdata");
system("xcrun llvm-cov show ./main -instr-profile=main.profdata main.cpp");
system("cp main.profdata coverage.txt");
system("cp main.profdata coverage.profdata");
