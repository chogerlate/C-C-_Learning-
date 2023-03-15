#include "math.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int main() {
  int arr[MAX]; // array to store our input values that will be feeding to our tree
  int i, n;     // iteration variable and size of our array

  printf("Enter elements of an array separated by space: ");
  for (i = 0; i < MAX && scanf("%d,", &arr[i]) == 1 && getchar() != '\n'; i++); // receive inputs and store them into our array
  n = i + 1; // saving the inputs size

  printf("size = %d\n", n);
  for (int i = 0; i < n; i++) {
    printf("Member: %d\n", arr[i]);
  }
  return 0;
}