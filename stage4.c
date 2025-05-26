#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LEN 50
#define CHANCES 3

// Structure for storing voice profile
typedef struct {
    char name[MAX_NAME_LEN];
    char gender; // 'M' or 'F'
    float frequency;
    float amplitude;
    float jitter;
    int GRBAS[5]; // G, R, B, A, S
} VoiceProfile;

// Structure for storing value ranges
typedef struct {
    float freq_min, freq_max;
    float amp_min, amp_max;
    float jitter_min, jitter_max;
} VoiceRange;

const VoiceRange maleRange = {85.0, 180.0, 2.5, 3.6, 0.2, 0.6};
const VoiceRange femaleRange = {165.0, 255.0, 3.5, 4.7, 0.3, 1.0};

// Function to get random float in a range
float getRandomInRange(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

// Function to get random GRBAS value (0-3)
int getRandomGRBAS() {
    return rand() % 4;
}

// Function to generate a random voice profile based on gender
void getMyVoiceFromHeaven(VoiceProfile* vp, VoiceRange range) {
    vp->frequency = getRandomInRange(range.freq_min, range.freq_max);
    vp->amplitude = getRandomInRange(range.amp_min, range.amp_max);
    vp->jitter = getRandomInRange(range.jitter_min, range.jitter_max);

    for (int i = 0; i < 5; i++) {
        vp->GRBAS[i] = getRandomGRBAS();
    }
}

// Generic float guessing game function
int guessFloatValue(const char* label, float target, float min, float max) {
    float guess;
    for (int i = 0; i < CHANCES; i++) {
        printf("%s (%.1f - %.1f): ", label, min, max);
        scanf("%f", &guess);

        if (guess == target) {
            printf("Correct!\n");
            return 1;
        } else if (guess < target) {
            printf("Up!\n");
        } else {
            printf("Down!\n");
        }
    }
    printf("You missed it. The correct value was: %.2f\n", target);
    return 0;
}

// Integer guessing for GRBAS
int guessGRBASValue(const char* label, int target) {
    int guess;
    for (int i = 0; i < CHANCES; i++) {
        printf("%s (0-3): ", label);
        scanf("%d", &guess);

        if (guess == target) {
            printf("Correct!\n");
            return 1;
        } else if (guess < target) {
            printf("Up!\n");
        } else {
            printf("Down!\n");
        }
    }
    printf("Missed! The value was: %d\n", target);
    return 0;
}

// Main vocal feature
void findMyVoice() {
    VoiceProfile user;
    VoiceRange range;
    int correct = 0;

    printf("Enter your nickname: ");
    scanf("%s", user.name);
    printf("Enter your gender (M/F): ");
    scanf(" %c", &user.gender);

    srand((unsigned int)time(NULL));
    range = (user.gender == 'F') ? femaleRange : maleRange;

    getMyVoiceFromHeaven(&user, range);

    printf("\n🎤 Guess your vocal profile! 🎤\n");
    correct += guessFloatValue("Frequency", user.frequency, range.freq_min, range.freq_max);
    correct += guessFloatValue("Amplitude", user.amplitude, range.amp_min, range.amp_max);
    correct += guessFloatValue("Jitter", user.jitter, range.jitter_min, range.jitter_max);

    printf("\n🎵 Now guess your GRBAS tone values:\n");
    const char* labels[] = {"G", "R", "B", "A", "S"};
    for (int i = 0; i < 5; i++) {
        correct += guessGRBASValue(labels[i], user.GRBAS[i]);
    }

    if (correct >= 6) {
        printf("\n✨ Congratulations %s, you found your voice! ✨\n", user.name);
    } else {
        printf("\n😢 Try again to discover your voice, %s.\n", user.name);
    }
}

// Add this to your menu system as needed
typedef void (*MenuFunction)();
void trainingMenu() {
    int choice;
    do {
        printf("\n[II. Training > 4. Vocal Training]\n");
        printf("1. My Voice\n");
        printf("0. Exit\n");
        printf("> Select an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            MenuFunction func = &findMyVoice;
            func();
        }
    } while (choice != 0);

    printf("Exiting Vocal Training...\n");
}

int main() {
    trainingMenu();
    return 0;
}