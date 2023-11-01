#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <stdbool.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, char*);

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    char option[3] = "-l";

    if (argc == 1) {
        dir = ".";
    } else if (argc == 2) {
        dir = ".";
        strcpy(option, argv[1]);
    } else {
        option[0] = argv[1][0];
        dir = argv[2];
    }

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0) {
            perror(path);
        } else {
            printStat(path, d->d_name, &st, option);
        }
    }

    closedir(dp);
    exit(0);
}

void printStat(char *pathname, char *file, struct stat *st, char *option) {
    if (strcmp(option, "-l") == 0) {
        printf("%5lld", st->st_blocks);
        printf("%c%s ", type(st->st_mode), perm(st->st_mode));
        printf("%3hu ", st->st_nlink);
        printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
        printf("%9lld ", st->st_size);
        printf("%.12s ", ctime(&st->st_mtime) + 4);
        printf("%s\n", file);
    } else if (strcmp(option, "-p") == 0) {
        if (S_ISDIR(st->st_mode)) {
            if (file[0] != '.') {  // Exclude hidden directories
                printf("%s/\n", file);
            }
        }
    } else if (strcmp(option, "-i") == 0) {
        printf("%5lld ", st->st_ino);
        printf("%s\n", file);
    } else if (strcmp(option, "-Q") == 0) {
        printf("\"%s\"\n", file); 
    
}
}

char type(mode_t mode) {
    if (S_ISREG(mode))
        return('-');
    if (S_ISDIR(mode))
        return('d');
    if (S_ISCHR(mode))
        return('c');
    if (S_ISBLK(mode))
        return('b');
    if (S_ISLNK(mode))
        return('l');
    if (S_ISFIFO(mode))
        return('p');
    if (S_ISSOCK(mode))
        return('s');
    return('?');
}

char *perm(mode_t mode) {
    static char perms[10];
    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> i * 3))
            perms[i * 3] = 'r';
        if (mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';
        if (mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }
    return (perms);
}

