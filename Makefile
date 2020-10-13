all:
	gcc -g -Wall -I/usr/include/libxml2 -o url-engine main.c xml.c -lxml2
test:
	./url-engine configuration.xml urls.txt
