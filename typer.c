#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 20
#define MAX_WORDS 100

void read_words(char words[MAX_WORDS][MAX_WORD_LENGTH], int *num_words);
void shuffle_words(char words[MAX_WORDS][MAX_WORD_LENGTH], int num_words);
void play_game(char words[MAX_WORDS][MAX_WORD_LENGTH], int num_words);

int main() {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int num_words = 0;

    read_words(words, &num_words);
    shuffle_words(words, num_words);
    play_game(words, num_words);

    return 0;
}

void read_words(char words[MAX_WORDS][MAX_WORD_LENGTH], int *num_words) {
    FILE *fp;
    char filename[] = "words.txt";
    char word[MAX_WORD_LENGTH];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    while (fgets(word, MAX_WORD_LENGTH, fp) != NULL) {
        word[strcspn(word, "\n")] = '\0'; // remove newline character
        strcpy(words[*num_words], word);
        (*num_words)++;
    }

    fclose(fp);
}

void shuffle_words(char words[MAX_WORDS][MAX_WORD_LENGTH], int num_words) {
    srand(time(NULL));
    for (int i = 0; i < num_words; i++) {
        int j = rand() % num_words;
        char temp[MAX_WORD_LENGTH];
        strcpy(temp, words[i]);
        strcpy(words[i], words[j]);
        strcpy(words[j], temp);
    }
}

void play_game(char words[MAX_WORDS][MAX_WORD_LENGTH], int num_words) {
    char input[MAX_WORD_LENGTH];
    int correct = 0;

    printf("Type the following words:\n");

    for (int i = 0; i < num_words; i++) {
        printf("%s ", words[i]);
        scanf("%s", input);
        if (strcmp(words[i], input) == 0) {
            correct++;
        }
    }

    printf("You typed %d out of %d words correctly.\n", correct, num_words);
}
