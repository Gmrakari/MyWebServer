
target = test

CC = g++

CFLAG += -Wall 
CFLAG += -lpthread

include = -I.threadpool.h

src = $(wildcard ./*cpp)

obj = $(patsubst ./%.cpp, ./%.o, $(src))

$(target) : $(obj)
	$(CC) $^ -o $@

%.o : %.cpp
	$(CC) -c $(include) $(CFLAG) $< -o $@

.PHONY:clean
clean:
	rm $(target) -f
