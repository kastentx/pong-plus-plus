# file name may be changed without affecting whole file
# THESE ARE VARIABLES, they are called by putting a 
# dollar sign before, and surrounding them in parentheses
# e.g. g++ $(TARGET) calls g++ on target.

TARGET 		= PongPlusPlus #Name of file output
RM 			= rm -f	#Name of remove command to be used
CXX 		= g++
CXXFLAGS 	= -g -std=c++11

# All is the standard command that will be run when
# make is typed by itself. For example "$make" will 
# run this on the command line
all: 	
		$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

# You can set different names to run different commands
# this will make it so that if you type "$make run"
# it will run this command
run: 	
		./$(TARGET) 
# Notice that the command and
# name of command are on different
# lines. This is important.

# This cleans everything taht ends in .o and the 
# executable, we don't want to be messy now do we?
clean: 
		$(RM) *.o $(TARGET)

