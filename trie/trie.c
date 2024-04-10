/*******************************************************************************************
  Implementation of "Trie" in C, particularly for spell-checking and auto-complete.
  An example of a trie data structure. It shows the representation of words:
  half, hello, help, helped, helping, helps, hey, hi, we, west, word, words, and world.
  An uppercase indicates the end of a word.

                      ============
                      ||  root  ||
                      ============
                     /            \
                    h              w                  Level 0
                  / | \          / |
                 a  e  I        E  o                  Level 1
                 |  | \         |  |
                 l  l  Y        s  r                  Level 2
                 |  | \         |  | \
                 F  l  P        T  D  l               Level 3
                    |  | \  \      |  |
                    O  e  i  S     S  D               Level 4
                       |  |
                       D  n                           Level 5
                          |
                          G                           Level 6


  suppose after compilation you got a file a.out
  Now, you can execute it as follows:
  ./a.out ./engmix.txt ./english3.txt ./ukenglish.txt
  Here, "engmix.txt" "english3.txt" "ukenglish.txt" are three text files that contain sets
  of English words. You can you use no file or any number of text files. the filenames are
  passed as the command line arguments. "argc" denotes the number of command line arguments.
  "argv" is an array of pointers to characters. In other words, it is an array of string
  objects. The first argument is always the filename that you are executing. You can check
  this by printing the arguments in this way:
  for (int i = 0; i < argc; i++) {
      printf("argv[%d] = %s\n", i, argv[i]);
  }
  Another way to have command line arguments is as follows:
  int main(int argc, char **argv) {...}

  The function "fopen" opens a file. You can have different modes to open a file depending
  on what operations you are willing to perform. Here, we open a file in read mode. The
  parameter "r" specifies read mode. "FILE" is a structure defined in stdio.h.
  "FILE" is an object type suitable for storing information for a file stream. "fopen"
  returns a pointer to a "FILE". You have already encountered file pointers - "stdin",
  "stderr", and "stdout" are file pointers. You have also used a function "fprintf" that
  prints to a file.
*******************************************************************************************/
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define BUFFER_SIZE   1000  // The size of string buffer
# define ALPHABET_SIZE 26    // The number of symbols in the alphabet

typedef struct trie_t *Trie;

struct trie_t {
    Trie children[ALPHABET_SIZE]; // Pointer to 26 children
    int  isTheEndOfAWord; // This is 1 if this trie indicates the end of a word, and 0 otherwise
};

Trie newTrie() {
    return (Trie) calloc(1, sizeof (struct trie_t)); // Everything is zero filled; no need to initialize
}

int toIndex(const char c) {
    return toupper((unsigned char) c) - 'A'; // e.g., indexes of both 'b' and 'B' are 1
}

void insert(Trie trie, const char word[]) {
    Trie crawler = trie; // a variable to traverse trie
    for (int level = 0; word[level] != '\0'; level++) { // while the end of the word is not found, repeat for each letter
        int index = toIndex(word[level]); // index of the current letter
        if (!crawler->children[index]) { // if the index-th child is empty/NULL
            crawler->children[index] = newTrie(); // make a new entry at the index-th child
        }
        crawler = crawler->children[index]; // traverse to the index-th child
    }
    crawler->isTheEndOfAWord = 1; // mark the last visited one as the end of a word
}

Trie search(Trie trie, const char *word) {
    for (int level = 0; word[level] != '\0'; level++) { // while the end of the word is not found, repeat for each character
        int index = toIndex(word[level]); // index of the current letter
        if (!trie->children[index]) { // if the index-th child is empty
            return NULL; // the word is  not found; return NULL
        }
        trie = trie->children[index]; // traverse to the index-th child
    }
    return trie; // return the last visited one. Note that, trie->isEndOfAWord may not be 1
}

void printTrieHelper(Trie trie, char offset[], int index, int level) {
    offset[level] = 'A' + index; // add the current letter to the offset
    if (trie->isTheEndOfAWord) { // we ended up with a word
        offset[level + 1] = '\0'; // this is required to print the buffer offset
        printf("%s\n", offset); // print the word
    }
    for (int nextIndex = 0; nextIndex < ALPHABET_SIZE; nextIndex++) { // for each child
        if (trie->children[nextIndex]) { // if there exist the nextIndex-th child
            printTrieHelper(trie->children[nextIndex], offset, nextIndex, level + 1); // a recursive call
        }
    }
}

void printTrie(const Trie trie) {
    char offset[BUFFER_SIZE];
    for (int nextIndex = 0; nextIndex < ALPHABET_SIZE; nextIndex++) { //for each child
        if (trie->children[nextIndex]) { // if there exist the nextIndex-th child
            printTrieHelper(trie->children[nextIndex], offset, nextIndex, 0); //use printTrieHelper to print the subtree
        }
    }
}

void toUpperString(char *string) {
    while (*string) {
        *string = toupper((unsigned char)*string);
        string++;
    }
}

void printAutoComplete(const Trie trie, char word[]) {
    if (trie == NULL) {
        printf("[No auto-complete options!]\n");
        return;
    }
    toUpperString(word);
    int level = strlen(word);
    int index = toIndex(word[level - 1]);
    printTrieHelper(trie, word, index, level - 1);
}

int isAValidWord(const char *word) {
    while (*word != '\0') {
        if (!((*word >= 'A' && *word <= 'Z') || (*word >= 'a' && *word <= 'z'))) {
            return 0;
        }
        word++;
    }
    return 1;
}

int main(const int argc, const char *argv[]) { // argc denotes the number of command line arguments. argv denotes an array of pointers. argv[i] points (refers) to the ith command line argument (a string).
    Trie trie = newTrie();
    if (argc == 1) { // No command line arguments have been provided. argv[0] is the name of the file being executed. This is passed by default.
        printf("No dictionary files are provided as command line arguments...\n"
               "Initializing default dictionary...\n"
               "Default dictionary contains:\n"
        );
        char dictionary[13][10] = {"half", "hello", "help", "helped", "helping",
            "helps", "hey", "hi", "we", "west", "word", "words", "world"
        }; // content of the default dictionary with 13 entries
        for (int i = 0; i < 13; i++) { // using a magic number 13; it is not recommended to use magic numbers
            insert(trie, dictionary[i]);
        }
        printTrie(trie);
    } else {
        int grandTotal = 0;
        for (int i = 1; i < argc; i++) { // argc denotes the number of argument
            printf("Processing file: %s...\n", argv[i]); // argv[i] contains the ith file name that needs to be processed.
            FILE *file = fopen(argv[i], "r"); // opens a file in read mode
            if (file == NULL) {
                fprintf(stderr, "Failed to open %s. Skipping the file.\n", argv[i]);
                continue;
            }
            char word[BUFFER_SIZE]; // allocates memory for a buffer where words will be stored
            word[BUFFER_SIZE - 1] = '\0';
            int valid = 0, invalid = 0; // initialize counters to count the number of words processed
            while (!feof(file)) { // while the end of file is not encountered
                fscanf(file, "%s", word); // scan a word from the file
                if (word[BUFFER_SIZE - 1] != '\0') { // checks for buffer overflow
                    fprintf(stderr, "Buffer Overflow!\n");
                    return -1;
                }
                if (isAValidWord(word)) {
                    insert(trie, word);  // insert the word in the trie data structure
                    valid++; // increment the word counter
                } else {
                    invalid++;
                }
            }
            printf("%d valid words inserted.\n", valid); // print the number of valid words ignored
            printf("%d invalid words ignored.\n", invalid); // print the number of invalid words ignored
            printf("%d words processed.\n\n", valid + invalid); // print the number of words processed
            grandTotal += valid + invalid;
            fclose(file); // close the file
            file = NULL;  // better not to have a dangling pointer
        }
        printf("Total %d words processed.\n", grandTotal); // print the total number of words processed
    }
    while (1) {
        char word[BUFFER_SIZE];
        word[BUFFER_SIZE - 1] = '\0';
        fflush(stdin);
        printf("Enter a word to check (enter ? to terminate): ");
        scanf("%s", word);
        if (word[BUFFER_SIZE - 1] != '\0') { // checks for buffer overflow
            fprintf(stderr, "Buffer Overflow!\n");
            return -1;
        }
        if (strcmp("?", word) == 0) {
            return 0;
        } else if (!isAValidWord(word)) {
            printf("%s is a not a valid word.\n");
            continue;
        }
        Trie found = search(trie, word);
        if (found && found->isTheEndOfAWord) {
            printf("%s is a correct word.\n");
            fflush(stdin);
            printf("Do you want to show auto-complete options (enter ? to show)?\n");
            char show;
            scanf("%c", &show);
            if (show == '?') {
                printAutoComplete(found, word);
            }
        } else {
            printf("%s is not a correct word.\nAuto-complete options:\n");
            printAutoComplete(found, word);
        }
    }
}