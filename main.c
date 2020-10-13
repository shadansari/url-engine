/*
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

regex_t regex;
int reti;
char msgbuf[100];

void main() {
    // Compile regular expression
    reti = regcomp(&regex, "^a[[:alnum:]]", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, "abc", 0, NULL, 0);
    if (!reti) {
        puts("Match");
    }
    else if (reti == REG_NOMATCH) {
        puts("No match");
    }
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);
}
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>

extern int streamFile(const char *filename);

void usage() {
    printf("usage: url-engine <algorithm(posix|self)> configuration.xml urls.txt\n");
}

int main(int argc, char *argv[]) {
  int opt;
  const char* xml_path;
  //const char* urls_path;

  while ((opt = getopt(argc, argv, "h")) != -1) {
	switch (opt) {
        case 'h': usage(); break;
        case 'a': usage(); break;
        default: usage(); return EXIT_FAILURE;
	}
  }

  if (argc - optind != 2) {
      printf("Invalid number of arguments\n");
      usage();
      return EXIT_FAILURE;
  }

  xml_path = argv[optind];
  //urls_path = argv[optind+1];

  streamFile(xml_path);

  return EXIT_SUCCESS;
}
