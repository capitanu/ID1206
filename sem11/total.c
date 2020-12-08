#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>


unsigned long count(char *path){

  unsigned long total = 0;

  DIR *dirp = opendir(path);
  char subdir[1024];

  struct dirent *entry;

  struct stat file_st;


  if(dirp == NULL){
    printf("not able to open %s\n", path);
    return 0;
  }
  
  while((entry = readdir(dirp)) != NULL){
    switch(entry->d_type){
    case DT_DIR:
      if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name,"..") == 0)
	break;
      sprintf(subdir, "%s%s", path, entry->d_name);
      total += count(subdir);
      break;
    case DT_REG:
      total++;
      break;
    default:
      break;
    }
  }
  closedir(dirp);
  return total;
}

int main(int argc, char *argv[]){
  if(argc < 2){
    perror("usage: total <dir>\n");
    return -1;
  }
  char *path = argv[1];
  unsigned long total = count(path);
  printf("The directory %s contains %lu files\n", path, total);
}
