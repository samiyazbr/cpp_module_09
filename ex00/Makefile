NAME		=	btc

SRCS		=	main.cpp BitcoinExchange.cpp

OBJS		=	$(SRCS:%.cpp=%.o)

CXX			=	c++

CXXFLAGS		=	-std=c++98 -Wall -Wextra -Werror

RM			=	rm -rf

%.o : %.cpp
			$(CXX) $(CXXFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CXX) $(FLAGS) $(OBJS) -o $(NAME)

clean:
			@$(RM) $(OBJS)
			@echo "Deleted CPP 08 object files"

fclean:		clean
			@$(RM) $(NAME)
			@echo "Deleted CPP 08 executable"

re:			fclean all

.PHONY:		all clean fclean re

