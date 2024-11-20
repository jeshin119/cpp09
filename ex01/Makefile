NAME := RPN
CXX := c++
RM := rm -f
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
DBG = -g -fsanitize=address
SRCS := main.cpp\
			RPN.cpp
HEADERS := RPN.hpp
TESTFILE := test.sh

OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

d : $(SRCS) $(HEADERS)
	$(CXX) $(DBG) $(SRCS) 

test : $(NAME) $(TESTFILE)
	bash $(TESTFILE)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS) input.txt out

fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)

.PHONY: all clean fclean re