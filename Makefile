all:
	gcc -Wall -I/usr/include/libxml2 -o url-engine main.c xml-reader.c -lxml2
test:
	./url-engine configuration.xml urls.txt
