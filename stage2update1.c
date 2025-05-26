#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    char keyword[8];  // "specter" + '\0'
    char message[512];
} EasterEgg;

EasterEgg arthurEgg = {
    "specter",
    "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. The past Arthur was a ghost of dogmatism and stubbornness."
};

// Convert a character to its 8-bit binary representation string
void charToBinary(unsigned char c, char *binStr) {
    int i;
    for (i = 7; i >= 0; i--) {
        binStr[7 - i] = ((c >> i) & 1) ? '1' : '0';
    }
    binStr[8] = '\0';
}

// Print keyword characters as 8-bit binary, reversed order
void displayReversedBinaryKeyword(const char *keyword) {
    char binaries[7][9];
    int i;
    for (i = 0; i < 7; i++) {
        charToBinary((unsigned char)keyword[i], binaries[i]);
    }

    printf("Binary values of keyword in reverse order:\n");
    for (i = 6; i >= 0; i--) {
        printf("%s\n", binaries[i]);
    }
}

// Validate that user input chars correspond to reversed keyword chars
int isRightChar(const char *keyword, const char *userInput) {
    int len = 7;
    int i;
    for (i = 0; i < len; i++) {
        if (userInput[i] != keyword[len - 1 - i])
            return 0;
    }
    return 1;
}

// Case-insensitive string comparison for Easter egg keyword match
int isEasterEgg(const char *input, const char *keyword) {
    int i;
    for (i = 0; keyword[i] && input[i]; i++) {
        if (tolower((unsigned char)input[i]) != tolower((unsigned char)keyword[i]))
            return 0;
    }
    return (input[i] == '\0' && keyword[i] == '\0');
}

// Easter egg interaction
void find_easter_egg() {
    char inputChars[16];
    char combinedWord[16];
    printf("<<Arthur's Easter Egg>>\n");
    displayReversedBinaryKeyword(arthurEgg.keyword);

    while (1) {
        printf("Enter the corresponding 7 characters in order: ");
        if (!fgets(inputChars, sizeof(inputChars), stdin)) {
            // EOF or error
            return;
        }
        // Remove newline
        inputChars[strcspn(inputChars, "\n")] = 0;

        if (strlen(inputChars) != 7) {
            printf("Please enter exactly 7 characters.\n");
            continue;
        }

        if (isRightChar(arthurEgg.keyword, inputChars)) {
            printf("Correct! Now combine these characters into the keyword word: ");
            if (!fgets(combinedWord, sizeof(combinedWord), stdin)) {
                return;
            }
            combinedWord[strcspn(combinedWord, "\n")] = 0;

            if (isEasterEgg(combinedWord, arthurEgg.keyword)) {
                printf("##Easter Egg Discovered!$$\n");
                printf("%s\n", arthurEgg.message);
                break;
            } else {
                printf("Incorrect keyword. Returning to menu.\n");
                break;
            }
        } else {
            printf("Incorrect characters entered. Try again.\n");
        }
    }
}

// Bonus: Shuffle keyword, convert to binary, reverse bits, print odd-even indexes
void shuffle_keyword_binary() {
    char keyword[8];
    char temp;
    char binaries[7][9];
    int i, j;

    strcpy(keyword, arthurEgg.keyword);

    // Simple shuffle: swap adjacent pairs (0<->1, 2<->3, ...)
    for (i = 0; i < 6; i += 2) {
        temp = keyword[i];
        keyword[i] = keyword[i+1];
        keyword[i+1] = temp;
    }

    // Convert each char to binary
    for (i = 0; i < 7; i++) {
        charToBinary((unsigned char)keyword[i], binaries[i]);
    }

    // Reverse bits in each binary string (e.g. "10110011" -> "11001101")
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 4; j++) {
            temp = binaries[i][j];
            binaries[i][j] = binaries[i][7 - j];
            binaries[i][7 - j] = temp;
        }
    }

    // Print odd indexed letters first (indexes 1,3,5)
    printf("Odd indexed letters binary:\n");
    for (i = 1; i < 7; i += 2) {
        printf("%s\n", binaries[i]);
    }

    // Print even indexed letters next (indexes 0,2,4,6)
    printf("Even indexed letters binary:\n");
    for (i = 0; i < 7; i += 2) {
        printf("%s\n", binaries[i]);
    }
}

// Example Self-Management and Teamwork menu stub with Arthur Easter egg trigger
void selfManagementAndTeamworkMenu() {
    char nickname[64];

    while (1) {
        printf("Enter nickname (or 'exit' to go back): ");
        if (!fgets(nickname, sizeof(nickname), stdin)) {
            break;
        }
        nickname[strcspn(nickname, "\n")] = 0; // trim newline

        if (strcasecmp(nickname, "exit") == 0) {
            break;
        }

        if (strcasecmp(nickname, "Arthur") == 0) {
            find_easter_egg();
            continue;
        }

        // ... your existing menu handling here ...

        printf("You entered: %s (No Easter egg triggered)\n", nickname);
    }
}

// Example main to test Easter egg
int main() {
    printf("== Self-Management and Teamwork Menu ==\n");
    selfManagementAndTeamworkMenu();

    printf("\n-- Bonus: Shuffled Keyword Binary --\n");
    shuffle_keyword_binary();

    return 0;
}
