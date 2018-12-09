#
# -std=gnu99 включать для поддержки вкусных няшек
# и выключать для совместимости с ANSI C
gbal: main.o
	gcc -o gbal main.o 
main.o: main.c
	gcc -c main.c
clean:
	rm -f gbal main.o
install:
	cp trbot /usr/local/bin/bgal
uninstall: 
	rm -f /usr/local/bin/gbal
