#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "store.h"

int main(int argc, char *argv[])
{
   int fd, id;
	char c; 
   struct store record;
   if (argc < 2) {
      fprintf(stderr, "How to use : %s file\n", argv[0]);
      exit(1);
   }
   if ((fd = open(argv[1], O_RDONLY)) == -1) {
      perror(argv[1]);
      exit(2);
   }
   do {
      printf("Enter stock to search:");
      if (scanf("%d", ) == 0) {
         lseek(fd, (id-START_ID)*sizeof(record), SEEK_SET);
          if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0))
       printf("id:%d\t name:%s\t category:%s\t epired_data:%d\t stock:%d\n", record.id, record.name, record.category, record.expired_data, record.stock);
         else printf("Record %d Null\n", id);
      } else printf("Input Error");
      printf("Continue?(Y/N)");
      scanf(" %c", &c);
   } while (c=='Y');
   close(fd);
   exit(0);
}


