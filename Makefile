IO_SRCS=$(addprefix src/io/, io.c unix.c)
RES_SRCS=$(addprefix src/res/, path.c res.c)

CARAVAN_SRCS=src/main.c

ALL_SRCS=$(CARAVAN_SRCS) $(IO_SRCS) $(RES_SRCS)

.PHONY: caravan

caravan: bin/caravan

clean:
	rm -rf bin lib *.o $(ALL_SRCS:%.c=%.o)

bin/caravan: $(CARAVAN_SRCS) lib/libcaravanio.a lib/libcaravanres.a
	@mkdir -p bin
	$(CC) -Llib  -lcaravanio -lcaravanres $< -o $@

lib/libcaravanio.a: $(IO_SRCS:%.c=%.o)
	@mkdir -p lib
	$(AR) -r $@ $^

lib/libcaravanres.a: $(RES_SRCS:%.c=%.o)
	@mkdir -p lib
	$(AR) -r $@ $^

%.o: %.c
	$(CC) -c $? -o $@

%.c: %.h
