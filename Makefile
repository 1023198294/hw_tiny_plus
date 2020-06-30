CC = g++
SRC_DIR = cpps
OBJ_DIR = objs
INC_DIR = includes

INCLUDE = -I includes
CFLAGS = -c -g -Iinclude -w $(INCLUDE) -lstdc++ -Wall 
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/lexer.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/parser.o $(OBJ_DIR)/analyze.o $(OBJ_DIR)/symtab.o $(OBJ_DIR)/code.o $(OBJ_DIR)/codegen.o $(OBJ_DIR)/tac.o
EXE = tiny.exe

$(EXE): $(OBJS) 
	$(CC) $(OBJS) -o $(EXE) -g


$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC)  $(CFLAGS) $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/lexer.o: $(SRC_DIR)/lexer.cpp
	$(CC)  $(CFLAGS) $(SRC_DIR)/lexer.cpp -o $(OBJ_DIR)/lexer.o

$(OBJ_DIR)/utils.o: $(SRC_DIR)/utils.cpp
	$(CC)  $(CFLAGS) $(SRC_DIR)/utils.cpp -o $(OBJ_DIR)/utils.o

$(OBJ_DIR)/parser.o: $(SRC_DIR)/parser.cpp
	$(CC)  $(CFLAGS) $(SRC_DIR)/parser.cpp -o $(OBJ_DIR)/parser.o

$(OBJ_DIR)/analyze.o: $(SRC_DIR)/analyze.cpp
	$(CC)  $(CFLAGS) $(SRC_DIR)/analyze.cpp -o $(OBJ_DIR)/analyze.o

$(OBJ_DIR)/symtab.o: $(SRC_DIR)/symtab.cpp
	$(CC)  $(CFLAGS) $(SRC_DIR)/symtab.cpp -o $(OBJ_DIR)/symtab.o

$(OBJ_DIR)/code.o: $(SRC_DIR)/code.cpp
	$(CC)  $(CFLAGS) $(SRC_DIR)/code.cpp -o $(OBJ_DIR)/code.o

$(OBJ_DIR)/codegen.o: $(SRC_DIR)/codegen.cpp
	$(CC)  $(CFLAGS) $(SRC_DIR)/codegen.cpp -o $(OBJ_DIR)/codegen.o

$(OBJ_DIR)/tac.o: $(SRC_DIR)/tac.cpp
	$(CC)  $(CFLAGS) $(SRC_DIR)/tac.cpp -o $(OBJ_DIR)/tac.o

clean:
	del $(OBJS)