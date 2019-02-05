inputFiles = ["input","coincidingInput", "colinearInput", "intersectingInput","badInput", "outBoundsInput"];
outputFiles = ["output", "coincidingOutput", "colinearOutput", "intersectingOutput", "badOutput", "outOfBoundsOutput"]
expectedOutputFiles = ["expectedOutput", "expectedCoincidingOutput", "expectedColinearOutput", "expectedIntersectingOutput", "expectedBadOutput", "expectedOutOfBoundsOutput"]


prevCoverage = "blanktest"
for i in 0..inputFiles.length-1 do
    system( "./main ./inputFiles/#{ inputFiles[i]}.txt ./outputFiles/#{ outputFiles[i] }.txt");
    puts"outputFile: #{outputFiles[i]}"
    system("xcrun llvm-profdata merge -sparse #{prevCoverage}.profdata default.profraw -o #{inputFiles[i]}.profdata");
#    system("xcrun llvm-profdata merge -sparse ./coverage/#{lastTest}.profdata ./default.profraw -o ./coverage/#{currentTest}.profdata");
    system( "./test.sh ./expected/#{expectedOutputFiles[i] }.txt ./outputFiles/#{ outputFiles[i] }.txt ")
    system("rm #{prevCoverage}.profdata")
    prevCoverage = "#{inputFiles[i]}"
end
system("xcrun llvm-profdata merge -sparse #{prevCoverage}.profdata -o main.profdata");
system("xcrun llvm-cov show ./main -instr-profile=main.profdata main.cpp");

#make fuzzer -builds /tester

