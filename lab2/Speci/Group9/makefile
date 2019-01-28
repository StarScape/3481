CC = g++
H = Headers
HDRS = $(H)/Register.h $(H)/ProcessorStateWord.h $(H)/FpStatusWord.h\
			 $(H)/IntRegisterFile.h $(H)/FpRegisterFile.h $(H)/Memory.h \
			 $(H)/Cpu.h $(H)/Instruction.h $(H)/Group12a.h

all: Group9.o Halt.o

Group9.o: Group9.C $(HDRS)

Halt.o: Halt.C $(HDRS)

clean:
	rm -f *.o
