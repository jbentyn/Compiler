SRCS=$(wildcard *.cpp) $(wildcard **/*.cpp)
OBJS=$(SRCS:.cpp=.o)
LEX_OUT_FILE=lexer.cpp
LEX_HEADER_FILE=lexer.h
BISON_OUT_FILE=parser.cpp
BISON_HEADER_FILE=parser.h
BISON_LOG_FILE=parser.output
DEPENDENCIES=deps

comp: $(OBJS)
	g++ -o comp $(OBJS) -lfl -Wall -g -pedantic
	
deps: $(SRCS) $(LEX_OUT_FILE) $(BISON_OUT_FILE)
	g++ -MM $(SRCS) $(LEX_OUT_FILE) $(BISON_OUT_FILE) > deps
	
$(LEX_OUT_FILE): lexer.l $(BISON_OUT_FILE)
	flex -o $(LEX_OUT_FILE) --header-file=$(LEX_HEADER_FILE) $<
	
$(BISON_OUT_FILE): parser.y
	bison -o $(BISON_OUT_FILE) --defines=$(BISON_HEADER_FILE) -v $<
	
-include $(DEPENDENCIES)

.PHONY: clean
clean:
	-rm $(OBJS) $(DEPENDENCIES) $(LEX_OUT_FILE) $(LEX_HEADER_FILE) $(BISON_OUT_FILE) $(BISON_HEADER_FILE) $(BISON_LOG_FILE) comp