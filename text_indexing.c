/*H**********************************************************************
* FILENAME :        text_indexing.c
*
* DESCRIPTION :
*       Indexes text from file or user input 
*
* NOTES :
*       Compile: gcc -o textidx text_indexing.c
*       Run Ex: ./textidx
*       Run Ex: ./textidx < data1.txt
*
*       Copyright 2017, Jacob Wilkins.  All rights reserved.
* 
* AUTHOR :    Jacob Wilkins        START DATE :    18 Sep 17
*
*H*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char** argv) {
  char text[1000] = {0};
  char s1[101] = {0};
  char s2[101] = {0};
  int firstLetters[1000];
  int counter = 1;
  int iterations = 0;
  int i, j, k, temp, minIndex, left, right;
  bool found;
  printf("Enter text: ");
  scanf("%[^\n]s", &text);

  // Finds the first letter of each word in the input
  firstLetters[0] = 0;
  for(i = 1; i < 1000; i++) {
    if (text[i] == ' ') {
      firstLetters[counter] = i + 1;
      counter++;
    }    
  }

  printf("\nWords and indexes (the printed words are 'cleaned'):");
  printf("\n i   |index[i]|  word");
  printf("\n-----|--------|------------------");

  // Prints each word with it's index in the order it's read from the input
  for (i = 0; i < counter; i++) {
    sscanf(&text[firstLetters[i]], "%s", s1);
    
    // Removes any character that isn't in the alphabet
    for (k = 0; s1[k] != '\0'; ++k) {
      while (!((s1[k] >= 'a' && s1[k] <= 'z') || (s1[k] >= 'A' && s1[k] <= 'Z') || (s1[k] >= '0' && s1[k] <= '9') || s1[k] == '\0')) {
        for (j = k; s1[j] != '\0'; ++j) {
          s1[j] = s1[j+1];
        }
        s1[j] = '\0';
      }
    }

    // Turns all remaining characters to lowercase
    for (k = 0; k < 101; k++) {
      s1[k] = tolower(s1[k]);
    }

    printf("\n%4d |%7d |  %s", i, firstLetters[i], s1);
  }

  // Sorts the words in alphabetical order using insertion sort
  for (i = 0; i < counter-1; i++) {
    minIndex = i; // minIndex is the index of the smallest remaining item
    for (j = i+1; j < counter; j++) {
      if (tolower(text[firstLetters[j]]) < tolower(text[firstLetters[minIndex]])) {
        minIndex = j;
      }
    }
    // swaps firstLetters[minIndex] and firstLetters[i]
    temp = firstLetters[minIndex];
    firstLetters[minIndex] = firstLetters[i];
    firstLetters[i] = temp; 
  }

  printf("\n\nThe sorted data (the printed words are 'cleaned'):");
  printf("\n i   |index[i]|  word");
  printf("\n-----|--------|------------------");

  //Prints each word with it's index sorted alphabetically
  for (i = 0; i < counter; i++) {
    sscanf(&text[firstLetters[i]], "%s", s1);

    // Removes any character that isn't in the alphabet
    for (k = 0; s1[k] != '\0'; ++k) {
      while (!((s1[k] >= 'a' && s1[k] <= 'z') || (s1[k] >= 'A' && s1[k] <= 'Z') || (s1[k] >= '0' && s1[k] <= '9') || s1[k] == '\0')) {
        for (j = k; s1[j] != '\0'; ++j) {
          s1[j] = s1[j+1];
        }
        s1[j] = '\0';
      }
    }

    // Turns all remaining characters to lowercase
    for (k = 0; k < 101; k++) {
      s1[k] = tolower(s1[k]);
    }

    printf("\n%4d |%7d |  %s", i, firstLetters[i], s1);
  }

  printf("\n\nBinary search. ---- Enter words to search for. Stop with -1\n");

  while (true) {
    scanf("%s", &s2);
    if ((s2[0] == '-') && (s2[1] == '1')) {
      return 0;
    }

    printf("(original: %s)", s2);
  
    // Removes any character that isn't in the alphabet
    for (i = 0; s2[i] != '\0'; ++i) {
      while (!((s2[i] >= 'a' && s2[i] <= 'z') || (s2[i] >= 'A' && s2[i] <= 'Z') || (s2[i] >= '0' && s2[1] <= '9') || s2[i] == '\0')) {
        for (j = i; s2[j] != '\0'; ++j) {
          s2[j] = s2[j+1];
        }
        s2[j] = '\0';
      }
    }

    // Turns all remaining characters to lowercase
    for (i = 0; i < 101; i++) {
      s2[i] = tolower(s2[i]);
    }

    // Locates the word in the sorted list using binary search
    iterations = 0;
    left = 0;
    right = counter;
    found = false;
    while (left <= right) {
      i = (left + right) / 2;
      if (s2[0] == tolower(text[firstLetters[i]])) {
        iterations++;
        sscanf(&text[firstLetters[i]], "%s", s1);

    // Removes any character that isn't in the alphabet
    for (k = 0; s1[k] != '\0'; ++k) {
      while (!((s1[k] >= 'a' && s1[k] <= 'z') || (s1[k] >= 'A' && s1[k] <= 'Z') || (s1[k] >= '0' && s1[k] <= '9') || s1[k] == '\0')) {
        for (j = k; s1[j] != '\0'; ++j) {
          s1[j] = s1[j+1];
        }
        s1[j] = '\0';
      }
    }

    // Turns all remaining characters to lowercase
    for (k = 0; k < 101; k++) {
      s1[k] = tolower(s1[k]);
    }

        if (strcmp(s1, s2) == 0) {
          found = true;
          break;
        }
      }
      if (s2[0] < tolower(text[firstLetters[i]])) {
        iterations++;
        right = i - 1;
      }
      else {
        iterations++;
        left = i + 1;
      }
    }

    // Determines if the word is found
    if (found == true) {
      printf("\ncleaned: %s - found (%d iterations)\n", s2, iterations);
    }
    else {
      printf("\ncleaned: %s - not found (%d iterations)\n", s2, iterations);
    }
  }
  return 0;
}
