#OBJS specifies which files to compile as part of the project
OBJS = ./src/main.cpp ./src/ball.cpp
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = target/ParticleSim

#This is the target that compiles our executable
all : $(OBJS)
	clang++ -O3 $(OBJS) -w -lSDL2 -o $(OBJ_NAME)