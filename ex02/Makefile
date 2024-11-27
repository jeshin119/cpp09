NAME := PmergeMe
CXX := c++
RM := rm -f
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
DBG = -g -fsanitize=address
SRCS := main.cpp\
			PmergeMe.cpp
HEADERS := PmergeMe.hpp

OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

d : $(SRCS) $(HEADERS)
	$(CXX) $(DBG) $(SRCS) 

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS) input.txt out

fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)

.PHONY: all clean fclean re