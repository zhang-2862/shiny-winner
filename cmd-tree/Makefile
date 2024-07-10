SRCS := $(wildcard *.c)
OUTS := $(patsubst *.c,%,$(SRCS))
CC := gcc
CFLAGS := -Wall -g
.PHONY: clean rebuild all

All: $(OUTS)
% : %.C
	$(CC) $^ -o $@ $(CFLAGS)
clean:
	$(RM) $(OUTS)

rebuild: clean ALL
