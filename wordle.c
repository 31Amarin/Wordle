#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define WordCount 20   //define  variables
#define WordLength 5
#define MaxGuesses 6
#define Words_File "words.txt"

int IsValidWord(char *word) {
    FILE *fp = fopen(Words_File, "r"); //opens word.txt file
    if (fp == NULL) {
        printf("Failed to open file '%s'\n", Words_File);
        return 0;
    }

    char line[WordLength+2];  // +2 to wordlegnth to make up for the newline and null terminator
    while (fgets(line, sizeof(line), fp) != NULL) { //while loop reads each line from the words.txt file
        // Remove the newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';
        
        // This compares the input to the lines from the file, ignoring the case of the word
        if (strcasecmp(word, line) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0; //returns false if the input is invalid
}

char ListOfWords[WordCount][WordLength+1] = {      //2D array containing all of the possible answers
    "apple", "guide", "chess", "daisy", "eagle",
    "level", "hairy", "horse", "moody", "juice",
    "merit", "lemon", "mouse", "dried", "stand",
    "greek", "queen", "hound", "smoke", "money"
};

int main() {
    srand(time(NULL));
    char Answer[WordLength+1]; //stores the answer 
    strcpy(Answer, ListOfWords[rand() % WordCount]); //selects a word from the ListOfWords array
    int Guesses = 0;
    char UserGuess[WordLength+1];

    printf("Welcome to the Wordle Game!\n"); //introductions
    printf("Please guess a word with %d letters.\n", WordLength);
    printf("Please make sure all your guesses are in lowercase.\n");
    printf("You have %d guesses to find the word.\n", MaxGuesses);
    printf("A lower case letter means that this letter is in the word but in the wrong place\n");
    printf("A * indicates that the letter has yet to be discovered, good luck! \n");

    while (Guesses < MaxGuesses) {
        printf("Guess %d: ", Guesses+1);
        scanf("%s", UserGuess);

        // Check that the user's guess is a valid word
        if (strlen(UserGuess) != WordLength) {
            printf("Invalid guess: your word should be %d letters long.\n", WordLength);
            continue;
        }
        if (!IsValidWord(UserGuess)) {
            printf("That is not a word. Please enter a real word and make sure no special characters are used.\n");
            continue;
        }

        // Iterates through each letter in the guess and displays correct output 
    int Correct = 0;
    int Misplaced = 0;
    int Matched[WordLength] = {0};  // This allows us to see what letters have been matched to prevent repeats 
    for (int i = 0; i < WordLength; i++) {
        // Check if there are correct letters in the right position
        if (UserGuess[i] == Answer[i]) {
            UserGuess[i] = toupper(UserGuess[i]);
            Correct++;
            Matched[i] = 1;
        }
        // Check for correct letters that are in the wrong position
        else {
            int InAnswer = 0;
            for (int x = 0; x < WordLength; x++) {
                // Check if the letter appears in the answer and hasn't been matched yet
                if (UserGuess[i] == Answer[x] && !Matched[x]) {
                    UserGuess[i] = tolower(UserGuess[i]);
                    Misplaced++;
                    Matched[x] = 1;
                    InAnswer = 1; //InAnswer returns true
                    break;
                }
            }
            // This replaces incorrect letters with a '*'
            if (!InAnswer) {
                UserGuess[i] = '*';
            }
        }
    }

        printf("%s\n", UserGuess);

        // Check if the user has correctly guessed the word
        if (Correct == WordLength) {
            printf("\nCongratulations Player! You found the Answer in just %d guesses!\n", Guesses+1);
            return 0;
        }

        // Increment the number of guesses and display the correct/incorrect letters so far
        Guesses++;
        printf("%d Correct, %d Misplaced.\n", Correct, Misplaced);
    }

    // The user has ran out of guesses
    printf("\nSorry, you ran out of guesses. The answer was '%s'. Thank you for playing, better luck next time!\n", Answer);
    return 0;
}
