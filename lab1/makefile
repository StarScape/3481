CXX=g++
CXXFLAGS = -Wall -g -std=c++11
OBJS = main.o Tools.o

# use this make target to build your own main.cpp for testing
tooltest:	$(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o tooltest		

# use this make target to build with my test program--can be compared with efb-output file		
efbtest:	efbmain.o Tools.o
		$(CXX) $(CXXFLAGS) efbmain.o Tools.o -o efbtest
		
main.o:		Tools.h
Tools.o:	Tools.h
efbmain.o:

clean:
			rm -f main.o Tools.o tooltest efbtest
        
#The following target runs a test on a specified function passed as a command line parameter to make
# e.g.  make test FUNCTION=getBits
#The student output is created in the file ./Test/<function>-student and the
#output of diff is written to the file 
.PHONY:	test
test:	
		(unset noclobber);\
		(./efbtest -t $(FUNCTION) > ./Test/$(FUNCTION)-student);(diff './Test/$(FUNCTION)-student' './Test/$(FUNCTION)-gold' > ./Test/$(FUNCTION).errors);\
		(set noclobber)
		

testall:
		(unset noclobber);\
		(./efbtest > './Test/testall-student');\
		(diff './Test/testall-student' './Test/efb-output' > './Test/testall.errors');\
		(set noclobber)
