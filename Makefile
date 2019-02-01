all : quadrilaterals

quadrilaterals : 
	clang++ -std=c++11 main.cpp -o main 

clean : 
	-rm main.o assignment04 main.profraw main.profdata main 

Coverage : 
	clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping main.cpp -o main
	-LLVM_PROFILE_FILE="main.profraw" ./main input.txt output.txt
	xcrun llvm-profdata merge -sparse main.profraw -o main.profdata
	xcrun llvm-cov show ./main -instr-profile=main.profdata

test : 
	ruby ./test.rb