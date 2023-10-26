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
   if ((fd = open(argv[1], O_RDWR)) == -1) {
      perror(argv[1]);
      exit(2);
   }

   do {
      printf("Enter item ID to be modified: ");
      if (scanf("%d", &id) == 1) {
         lseek(fd, (long) (id-START_ID)*sizeof(record), SEEK_SET);
         if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0)) {
            printf("ID:%d\t Name:%s\t category:%s\t expired_data:%d\t stock:%d\n",
                    record.id, record.name, record.category, record.expired_data, record.stock);
            printf("Enter New stock: ");
            scanf("%d", &record.stock);
            lseek(fd, (long) -sizeof(record), SEEK_CUR);
            write(fd, (char *) &record, sizeof(record));
         } else printf("Record %d Null\n", id);
      } else printf("Insert Error\n");
      printf("Continue?(Y/N)");
      scanf(" %c",&c);
   } while (c == 'Y');
   close(fd);
   exit(0);
}


