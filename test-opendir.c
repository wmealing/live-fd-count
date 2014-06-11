#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>


int
main(int argc, char *argv[])
{

int file_count = 0;
DIR * dirp;
struct dirent * entry;

dirp = opendir(argc > 1 ? argv[1] : "."); /* There should be error handling after this */
while ((entry = readdir(dirp)) != NULL) {
    if (entry->d_type == DT_REG) { /* If the entry is a regular file */
         file_count++;
    }
}
closedir(dirp);


   exit(EXIT_SUCCESS);

}
