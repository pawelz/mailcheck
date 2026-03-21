#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
  printf("Usage: mailcheck [flags] <Maildir path relative to ~> <maildir> [<maildir> <maildir> ...]\n");
  printf("Flags: -d, --debug, -h, --help\n");
}

// Counts regular files in the directory 'path'.
int count_files(char *path) {
  int count = 0;
  DIR *dirp;
  struct dirent *entry;
  dirp = opendir(path);
  if (dirp == NULL) {
    fprintf(stderr, "Cannot open directry '%s': %s", path, strerror(errno));
    exit(1);
  }
  while ((entry = readdir(dirp)) != NULL) {
    if (entry->d_type == DT_REG) {
      count++;
    }
  }
  return count;
}

int main(int argc, char **argv) {
  // Command line arguments parsing.
  int debug = 0;
  char **true_argv = calloc(sizeof(char*), argc);
  int true_argc = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strcmp(argv[i], "-d")*strcmp(argv[i], "--debug") == 0) {
        debug = 1;
      } else if (strcmp(argv[i], "-h")*strcmp(argv[i], "--help") == 0 ) {
        help();
        return 0;
      } else {
        fprintf(stderr, "Unrecognized flag '%s'.\n", argv[i]);
        help();
        return 1;
      }
      continue;
    }
    true_argv[true_argc++] = argv[i];
  }
  true_argv[true_argc] = 0x0;

  if(true_argc < 2) {
    help();
    return 1;
  }
  // End of command line argument parsing.
  // The true_argc and true_argv represent the arguments excluding the binary name
  // and the flags.

  char *path = malloc(4096);
  char *end = path;
  int length = 0;

  char *homedir = getenv("HOME");
  length = strlen(homedir);
  if (length > 1024) {
    fprintf(stderr, "Home directory path length %d is longer than max supported 1024 bytes.\n", length);
    return 1;
  }
  strcpy(end, homedir);
  end += length;
  *(end++) = '/';

  char *basepath = true_argv[0];
  length = strlen(basepath);
  if (length > 1024) {
    fprintf(stderr, "Maildir path length %d is longer than max supported 1024 bytes.\n", length);
    return 1;
  }
  strcpy(end, basepath);
  end += length;
  *(end++) = '/';

  for (int i=1; i<true_argc; i++) {
    char *maildir = true_argv[i];
    length = strlen(maildir);
    if (length > 1024) {
      fprintf(stderr, "Maildir path length %d is longer than max supported 1024 bytes.\n", length);
      return 1;
    }
    strcpy(end, maildir);
    strcat(end, "/new");
    if (debug) {
      printf("Path: %s\n", path);
    }
    int count = count_files(path);
    printf("%s: %d new messages\n", maildir, count);
  }
}
