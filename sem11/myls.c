#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>


int main(int argc, char *argv[]){
  if(argc < 2){
    perror("usage: myls <dir>\n");
    return -1;
  }

  char *path = argv[1];
  DIR *dirp = opendir(path);

  struct dirent *entry;  
  struct stat file_st;


  while((entry = readdir(dirp)) != NULL){
    fstatat(dirfd(dirp), entry->d_name, &file_st, 0);

    switch(entry->d_type) {
    case DT_BLK:
      printf("b:");
      break;
    case DT_CHR:
      printf("c:");
      break;
    case DT_DIR:
      printf("d:");
      break;
    case DT_FIFO:
      printf("p:");
      break;
    case DT_LNK:
      printf("l:");
      break;
    case DT_REG:
      printf("f:");
      break;
    case DT_SOCK:
      printf("s:");
      break;
    case DT_UNKNOWN:
      printf("u:");
      break;
    }
    printf("\tinode: %lu", entry->d_ino);
    printf("\tdev: 0x%lx", file_st.st_dev);
    printf("\tinode: %lu", file_st.st_ino);
    printf("\tsize: %lu", file_st.st_size);
    printf("\tname: %s\n", entry->d_name);
  }
  
}
