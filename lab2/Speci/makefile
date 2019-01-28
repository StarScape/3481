CC = g++
H = Headers
HDRS = $(H)/Register.h $(H)/ProcessorStateWord.h $(H)/FpStatusWord.h\
		$(H)/IntRegisterFile.h $(H)/FpRegisterFile.h $(H)/Memory.h\
		$(H)/Cpu.h $(H)/Instruction.h $(H)/Loader.h
HDR_OS = Register.o ProcessorStateWord.o FpStatusWord.o\
		IntRegisterFile.o FpRegisterFile.o Memory.o\
		Cpu.o Loader.o

build:
	(cd Group12a; make)
	(cd Group9; make)
	make speci

speci: speci.C $(HDR_OS)
	$(CC) speci.C $(HDR_OS) -o speci	

Register.o: Register.C $(H)/Register.h
ProcessorStateWord.o: ProcessorStateWord.C $(H)/ProcessorStateWord.h
FpStatusWord.o: FpStatusWord.C $(H)/FpStatusWord.h
IntRegisterFile.o: IntRegisterFile.C $(H)/IntRegisterFile.h
FpRegisterFile.o: FpRegisterFile.C $(H)/FpRegisterFile.h
Memory.o: Memory.C $(H)/Memory.h
Cpu.o: Cpu.C $(H)/Cpu.h
Instruction.o: Instruction.C $(H)/Instruction.h
Load.o: Loader.C $(H)/Loader.h

clean:
	(cd Group12a; make clean)
	(cd Group9; make clean)
	rm -f *.o
