

NAME := webserv

VERBOSE := TRUE

CXX := c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

CXXFLAGS += -I src

SUBDIRS := libstrutil libutil main

SRC := $(foreach dir, $(SUBDIRS), $(wildcard src/$(dir)/*.cpp))
OBJ := $(SRC:%.cpp=%.o)

%.o: %.cpp
	echo "\033[0;33mGenerating %-38.38s\r" $@
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@echo "\033[0;32mCompiling webserv..."
	$(CXX) $(CXXFLAGS) -o $@ $^

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

run: all
	$(NAME)
