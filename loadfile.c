#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

/** @brief Load (mmap) file to memory
 *      https://nextmovesoftware.com/blog/2012/10/17/lazy-file-reading-with-mmap/
 *
 *  @param fname the character to print
 *  @return On success, a pointer to the mapped area is returned. On error, NULL is returned
 */
unsigned char *loadfile(const char *fname)
{
	unsigned char *result;
	unsigned int len;
	struct stat buf;

	int fd = open(fname,O_RDONLY);
	if (fd < 0) {
        fprintf(stderr,"Error: Unable to read dictionary file %s\n",fname);
        return (unsigned char*)0;
	}

	if (fstat(fd,&buf) < 0) {
        fprintf(stderr,"Error: Unable to determine file size\n");
        return (unsigned char*)0;
	}

	len = (unsigned int)buf.st_size;
	result = (unsigned char*)mmap(0,len,PROT_READ,MAP_FILE|MAP_PRIVATE,fd,0);
	if (result == MAP_FAILED)
        return (unsigned char*)0;

	return result;
}

/** @brief
 *
 * 		https://stackoverflow.com/a/20300544
 *
 *  @param
 *  @return
 */
char *sgets(char *s, int n, const unsigned char **strp){

    if(**strp == '\0')return NULL;
    int i;
    for(i=0;i<n-1;++i, ++(*strp)){
        s[i] = **strp;
        if(**strp == '\0')
            break;
        if(**strp == '\n'){
            s[i+1]='\0';
            ++(*strp);
            break;
        }
    }
    if(i==n-1)
        s[i] = '\0';
    return s;
}
