
.PHONY: caravan

caravan: bin/caravan

clean:
	rm -rf bin lib *.o src/*.o src/io/*.o src/res/*.o

bin/caravan: src/main.o lib/libcaravanio.a lib/libcaravanres.a
	@mkdir -p bin
	$(CC) -Llib  -lcaravanio -lcaravanres $< -o $@

lib/libcaravanio.a: src/io/io.o src/io/unix.o
	@mkdir -p lib
	$(AR) -r $@ $^

lib/libcaravanres.a: src/res/path.o src/res/res.o
	@mkdir -p lib
	$(AR) -r $@ $^

%.o: %.c
	$(CC) -c $? -o $@

%.c: %.h
