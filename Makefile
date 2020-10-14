all:
	gcc -g -Wall -I/usr/include/libxml2 -o url-engine main.c conf.c url.c posix_match.c loadfile.c -lxml2

.PHONY: test
test:
	./url-engine test/configuration.xml test/urls.txt
	-./url-engine self test/configuration.xml test/urls.txt
	./url-engine posix test/configuration.xml test/urls.txt

clean:
	rm url-engine
