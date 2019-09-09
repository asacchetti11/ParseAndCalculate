parseAndCalc: stack.cc parseAndCalc.cc
	g++ -o parseAndCalc stack.cc parseAndCalc.cc

clean:
	rm -rf parseAndCalc