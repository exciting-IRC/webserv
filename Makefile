NAME := webserv

MAKEFLAGS += -s

CXX := c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

CXXFLAGS += -I src

SUBDIRS := libstrutil libutil liblogger main

SRC := $(foreach dir, $(SUBDIRS), $(wildcard src/$(dir)/*.cpp))
OBJ := $(SRC:%.cpp=%.o)

include color.mk

%.o: %.cpp
	echo "$(YEL)$@$(END)"
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	echo "$(GRN)Linking...$(END)"
	$(CXX) $(CXXFLAGS) -o $@ $^

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

run: all
	./$(NAME)
