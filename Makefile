
CXX=clang
LINKER=g++
CFLAGS=-Wall
OBJ=obj

INCLUDE=
LIBPATH=

OUTPUT=bin/synth

ALLFLAGS=$(CFLAGS) $(INCLUDE) $(LIBPATH)
#----------
all: $(OUTPUT)
$(OBJ)/APlay.o: APlay.cpp
	$(CXX) APlay.cpp $(ALLFLAGS) -c -o $(OBJ)/APlay.o

$(OBJ)/LFOPart.o: LFOPart.cpp
	$(CXX) LFOPart.cpp $(ALLFLAGS) -c -o $(OBJ)/LFOPart.o

$(OBJ)/main.o: main.cpp
	$(CXX) main.cpp $(ALLFLAGS) -c -o $(OBJ)/main.o

$(OBJ)/OscPart.o: OscPart.cpp
	$(CXX) OscPart.cpp $(ALLFLAGS) -c -o $(OBJ)/OscPart.o

$(OBJ)/Part.o: Part.cpp
	$(CXX) Part.cpp $(ALLFLAGS) -c -o $(OBJ)/Part.o

$(OBJ)/PartSetting.o: PartSetting.cpp
	$(CXX) PartSetting.cpp $(ALLFLAGS) -c -o $(OBJ)/PartSetting.o

$(OBJ)/SynthManager.o: SynthManager.cpp
	$(CXX) SynthManager.cpp $(ALLFLAGS) -c -o $(OBJ)/SynthManager.o

$(OBJ)/Wire.o: Wire.cpp
	$(CXX) Wire.cpp $(ALLFLAGS) -c -o $(OBJ)/Wire.o

$(OUTPUT): $(OBJ)/APlay.o $(OBJ)/LFOPart.o $(OBJ)/main.o $(OBJ)/OscPart.o $(OBJ)/Part.o $(OBJ)/PartSetting.o $(OBJ)/SynthManager.o $(OBJ)/Wire.o
	$(LINKER) $(ALLFLAGS) $(OBJ)/APlay.o $(OBJ)/LFOPart.o $(OBJ)/main.o $(OBJ)/OscPart.o $(OBJ)/Part.o $(OBJ)/PartSetting.o $(OBJ)/SynthManager.o $(OBJ)/Wire.o -o $(OUTPUT)

clean: 
	rm -f $(OBJ)/*
	rm -f $(OUTPUT)

