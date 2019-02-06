all : quadrilaterals

quadrilaterals : 
	clang++ -std=c++11 main.cpp -o main 

clean : 
	-rm main.o main.profraw main.profdata blanktest.profdata default.profraw input.profdata coincidingInput.profdata colinearInput.profdata intersectingInput.profdata badInput.profdata main 

test : 
	clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping main.cpp -o main
	touch blanktest.profdata
	ruby ./test.rb

itwork:  
	 -fprofile-instr-generate -fcoverage-mapping main.cpp -o main
	-LLVM_PROFILE_FILE="main.profraw" ./main ./inputFiles/input.txt ./outputFiles/output.txt
	xcrun llvm-profdata merge -sparse main.profraw -o main.profdata
	xcrun llvm-cov show ./main -instr-profile=main.profdata

fuzzer: 
	clang++ -std=c++11 -O1 -g -fsanitize=address -fprofile-instr-generate -fcoverage-mapping main.cpp -o main
	clang++ -std=c++11 testGenerator.cpp shapes.cpp -o testGenerator
	touch blanktest.profdata
	ruby randomTesting.rb

tiaFile:
	clang++ -std=c++11 tiaClassifier.cpp -o tia
	clang++ -std=c++11 main.cpp -o main

differential: tiaFile
	ruby differentialTesting.rb