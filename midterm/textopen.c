#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE  *fp;
	int c;
	if(argc < 2)
		fp = stdin;
	else fp = fopen(argv[1],"r");

	c = getc(fp);
	while (fgets(line, sizeof(2), fp) != NULL){
		putc(c, fp);
		c = getc(fp);
	}
	fclose(fp);
	return 0;
}
