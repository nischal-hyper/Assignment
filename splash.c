#include <stdio.h>
#include <stdlib.h>

// Function to simulate screen clear (cross-platform)
void clear_screen() {
    // ANSI escape code to clear screen
    printf("\033[2J\033[H");
}

// Function to delay for approximately 3 seconds
void delay_seconds(int seconds) {
    int ms = seconds * 1000000;
    for (int i = 0; i < ms; i++) {
        // simple loop to consume time (platform-independent)
    }
}

// Main function
int main(void) {
    char name[100];
    char date[11]; // "yyyy-mm-dd" + null terminator

    // Prompt for date and name
    printf("[Please enter the current date in the \"yyyy-mm-dd\" format]: ");
    scanf("%10s", date);
    printf("[Please enter your name]: ");
    scanf(" %[^\n]", name); // read name with spaces

    // Success message
    printf("**The input has been processed successfully.**\n");

    // Simulated 3-second delay
    delay_seconds(3);

    // Clear screen
    clear_screen();

    // Splash screen width
    int width = 109;

    // Top border
    for (int i = 0; i < width; i++) {
        printf("+");
    }
    printf("\n");

    // Triangle height = 5
    for (int i = 1; i <= 5; i++) {
        // Left triangle
        for (int j = 0; j < i; j++) {
            printf("*");
        }

        // Line content
        if (i == 1) {
            printf("%*s[Magrathea ver 0.1]%*s", 40, "", 40, "");
        } else if (i == 2) {
            printf("%*sMagrathea, where a shining planet is created in a wasteland with no grass,%*s", 10, "", 5, "");
        } else if (i == 3) {
            printf("%*sa place where unseen potential is discovered and gems are polished by the hands of experts,%*s", 5, "", 5, "");
        } else if (i == 4) {
            printf("%*sWelcome to Magrathea.%*s", 35, "", 30, "");
        } else {
            printf("%*s", width - 10, "");
        }

        // Right triangle
        for (int j = 0; j <= 5 - i; j++) {
            printf("*");
        }

        printf("\n");
    }

    // Bottom border
    for (int i = 0; i < width; i++) {
        printf("+");
    }
    printf("\n");

    // User and date info
    printf("[User]: %s%*s[Execution Time]: %s\n", name, 45 - (int)strlen(name), "", date);

    // Bottom separator
    for (int i = 0; i < width; i++) {
        printf("=");
    }
    printf("\n");

    return 0;
}
