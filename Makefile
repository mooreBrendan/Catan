#Environment setup
EXE_NAME=Catan
SFMLPath=D:/sfml

#DEBUG
DEBUG_FLAGS = -DDEBUG

#Compilation flags
SRCS = src/*.cpp
includes = -I include -I $(SFMLPath)/include
libs = -L $(SFMLPath)/lib
links = -l sfml-audio -l sfml-graphics -l sfml-window -l sfml-system
OBJS = $(SRCS:%.cpp=%.o)

#Compile Options
all: compile link
remake: clean all
remake-debug: clean debug link

debug:
	g++ $(includes) -c $(SRCS) $(DEBUG_FLAGS)

compile:
	g++ $(includes) -c $(SRCS)
link:
	g++ -o $(EXE_NAME).exe *.o $(libs) $(links)


clean:
	del .\$(EXE_NAME).exe
	del *.o