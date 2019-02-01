puts "Hello world";
inputFiles = ["input","coincidingInput", "colinearInput", "intersectingInput","badInput"];
outputFiles = ["output", "coincidingOutput", "colinearOutput", "intersectingOutput", "badOutput"]
expectedOutputFiles = ["./expected/expectedOutput", "./expected/expectedCoincidingOutput", "./expected/expectedColinearOutput", "./expected/expectedIntersectingOutput", "./expected/expectedBadOutput"]

system "touch ./coverage/blanktest.profdata";
lastTest = "blank";

for i in 0..inputFiles.length-1 do
    currentTest = inputFiles[i];
    system( "./main ./inputFiles/#{ inputFiles[i]}.txt ./outputFiles/#{ outputFiles[i] }.txt");
    puts"outputFile: #{outputFiles[i]}"
    #    system("LLVM_PROFILE_FILE=main.profraw ./main")
    #    system("xcrun llvm-profdata merge -sparse ./coverage/#{lastTest}.profdata ./default.profraw -o ./coverage/#{currentTest}.profdata");
    system( "./test.sh #{expectedOutputFiles[i] }.txt ./outputFiles/#{ outputFiles[i] }.txt ")
    lastTest = currentTest;
end

