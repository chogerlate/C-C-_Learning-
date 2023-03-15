#include "string.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR_LENGTH 500

int main(void) {
  char searchByTitle[60]; // string variable for temperary storing our input
                          // value
                        
  printf("Enter title (leave blank to include all titles): ");

  // main idea of this file
  fgets(searchByTitle, MAX_CHAR_LENGTH,stdin);  // using fgets instead of normal scanf
  fflush(stdin); // flushing the remaining remnant out of input field

  printf("%d", atoi(searchByTitle) + 10); // print our input
  return 0;
}