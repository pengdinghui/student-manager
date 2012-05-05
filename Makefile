TGT := test
SRCS := manager.c test.c

$(TGT) : $(SRCS:.c=.o)
	$(CC) -o $(TGT) $^

clean :
	$(RM) $(TGT) $(SRCS:.c=.o)

.PHONY : clean
