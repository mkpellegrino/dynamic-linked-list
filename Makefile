FILE_NAME=dll

CPPFLAGS=-arch x86_64 -m64
DEBUG=-g -DDEBUG
OPT=-O3

BIN_DIR=./
LIB_DIR=./
LST_DIR=./

$(FILE_NAME): $(FILE_NAME).cpp
	g++ $(FILE_NAME).cpp $(OPT) $(CPPFLAGS) -o $(BIN_DIR)$(FILE_NAME)
	g++ $(FILE_NAME).cpp $(DEBUG) $(CPPFLAGS) -o $(BIN_DIR)$(FILE_NAME)-debug
	strip -no_uuid -A -u -S -X -N -x $(BIN_DIR)$(FILE_NAME)

clean :
	rm -fR $(LIB_DIR)*.o 
	rm -fR $(BIN_DIR)$(FILE_NAME)
	rm -fR $(BIN_DIR)$(FILE_NAME)-debug
	rm -fR $(BIN_DIR)$(FILE_NAME)-debug.dSYM
