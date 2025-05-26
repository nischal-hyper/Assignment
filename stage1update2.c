#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 10
#define MAX_NAME_LENGTH 50
#define NUM_TESTS 7
#define DAYS_IN_WEEK 6
#define MAX_EXERCISE_LENGTH 50

const char *test_names[NUM_TESTS] = {
    "1-Mile Running Test",
    "Speed Sprint",
    "Push-ups",
    "Squats",
    "Arm Strength (Push-ups)",
    "Swimming",
    "Weightlifting"
};

const char *exercise_types[5][3] = {
    {"Running", "Cycling", "Fast Walking"}, // Cardio
    {"Push-ups", "Squats", ""},              // Full-body Strength
    {"Leg Press", "Leg Curl", ""},           // Lower-body Strength
    {"Pull-ups", "Chin-ups", ""},            // Upper-body Strength
    {"Plank", "Crunches", ""}                // Core Strength
};

const char *week_days[DAYS_IN_WEEK] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

typedef struct {
    char name[MAX_NAME_LENGTH];
    char nickname[MAX_NAME_LENGTH];
} Member;

char member_routine[MAX_MEMBERS][DAYS_IN_WEEK][2][MAX_EXERCISE_LENGTH];

Member milliways_members[MAX_MEMBERS] = {
    {"Goeun", "G"},
    {"Woncheol", "W"},
    {"Youngjin", "YJ"},
    {"Hyekyung", "HK"},
    {"Arthur", "A"}
};

float health_scores[MAX_MEMBERS][NUM_TESTS];
char health_nicknames[MAX_MEMBERS][MAX_NAME_LENGTH];
int member_count = 5; // update if adding/removing members

void parseFitnessData(char *input, float scores[]) {
    char *token = strtok(input, ",");
    int i = 0;
    while (token != NULL && i < NUM_TESTS) {
        scores[i++] = atof(token);
        token = strtok(NULL, ",");
    }
}

void setHealth() {
    printf("--- Enter Fitness Data ---\n");
    for (int i = 0; i < member_count; i++) {
        char input[256];
        printf("%s (%s), enter 7 test scores (comma-separated):\n", milliways_members[i].name, milliways_members[i].nickname);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        parseFitnessData(input, health_scores[i]);
        strcpy(health_nicknames[i], milliways_members[i].nickname);
    }
    printf("Fitness data recorded.\n\n");
}

void displayMemberHealth(int index) {
    printf("\n--- Fitness Data for %s (%s) ---\n", milliways_members[index].name, milliways_members[index].nickname);
    for (int j = 0; j < NUM_TESTS; j++) {
        printf("%s: %.2f\n", test_names[j], health_scores[index][j]);
    }
    printf("\n");
}

void listMembers() {
    printf("\n--- Milliways Members ---\n");
    for (int i = 0; i < member_count; i++) {
        printf("%s (%s)\n", milliways_members[i].name, milliways_members[i].nickname);
    }
    printf("\n");
}

void setExerciseRoutine() {
    printf("\n--- Set Basic Workout Routine ---\n");
    listMembers();

    for (int i = 0; i < member_count; i++) {
        printf("\nEnter workout routine for %s (%s):\n", milliways_members[i].name, milliways_members[i].nickname);
        int core_used = 0;
        for (int d = 0; d < DAYS_IN_WEEK; d++) {
            char cardio[MAX_EXERCISE_LENGTH];
            char strength[MAX_EXERCISE_LENGTH];

            printf("%s - Enter one cardio exercise (Running, Cycling, Fast Walking): ", week_days[d]);
            fgets(cardio, sizeof(cardio), stdin);
            cardio[strcspn(cardio, "\n")] = 0;

            printf("%s - Enter one strength/core exercise (Push-ups, Squats, Leg Press, Leg Curl, Pull-ups, Chin-ups, Plank, Crunches): ", week_days[d]);
            fgets(strength, sizeof(strength), stdin);
            strength[strcspn(strength, "\n")] = 0;

            if ((strcmp(strength, "Plank") == 0 || strcmp(strength, "Crunches") == 0)) {
                if (core_used) {
                    printf("Core exercises can only be used once per week. Please re-enter.\n");
                    d--;
                    continue;
                } else {
                    core_used = 1;
                }
            }

            strcpy(member_routine[i][d][0], cardio);
            strcpy(member_routine[i][d][1], strength);
        }
    }
    printf("\nWorkout routines recorded.\n");
}

void getExerciseRoutine() {
    printf("\n--- View Basic Workout Routine ---\n");
    listMembers();

    char name[MAX_NAME_LENGTH];
    printf("Enter member name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < member_count; i++) {
        if (strcmp(name, milliways_members[i].name) == 0) {
            printf("\nWorkout routine for %s (%s):\n", milliways_members[i].name, milliways_members[i].nickname);
            for (int d = 0; d < DAYS_IN_WEEK; d++) {
                printf("%s: Cardio - %s, Strength/Core - %s\n", week_days[d], member_routine[i][d][0], member_routine[i][d][1]);
            }
            found = 1;
            break;
        }
    }
    if (!found) printf("Member not found.\n");
}

void getHealth() {
    int option;
    printf("\n--- View Fitness Data ---\n");
    printf("1. View all\n");
    printf("2. View by member nickname\n");
    printf("3. View one test for a member\n");
    printf("Enter your option: ");
    scanf("%d", &option);
    getchar(); // consume newline

    if (option == 1) {
        for (int i = 0; i < member_count; i++) {
            displayMemberHealth(i);
        }
    } else if (option == 2) {
        char nickname[MAX_NAME_LENGTH];
        printf("Enter member nickname (e.g., G, W, YJ, HK, A): ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = 0;
        int found = 0;
        for (int i = 0; i < member_count; i++) {
            if (strcmp(nickname, milliways_members[i].nickname) == 0) {
                displayMemberHealth(i);
                found = 1;
                break;
            }
        }
        if (!found) printf("Member not found.\n");
    } else if (option == 3) {
        char nickname[MAX_NAME_LENGTH];
        printf("Enter member nickname (e.g., G, W, YJ, HK, A): ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = 0;

        int found = 0;
        for (int i = 0; i < member_count; i++) {
            if (strcmp(nickname, milliways_members[i].nickname) == 0) {
                int test_index;
                printf("Enter test number (1-7): ");
                scanf("%d", &test_index);
                getchar();
                if (test_index < 1 || test_index > NUM_TESTS) {
                    printf("Invalid test number.\n");
                } else {
                    printf("%s (%s) - %s: %.2f\n",
                           milliways_members[i].name,
                           milliways_members[i].nickname,
                           test_names[test_index - 1],
                           health_scores[i][test_index - 1]);
                }
                found = 1;
                break;
            }
        }
        if (!found) printf("Member not found.\n");
    } else {
        printf("Invalid option.\n");
    }
}

void showMenu() {
    int choice;
    do {
        printf("\n=== Milliways Training Menu ===\n");
        printf("1. Set Fitness Data\n");
        printf("2. Get Fitness Data\n");
        printf("3. Set Basic Workout Routine\n");
        printf("4. View Basic Workout Routine\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: setHealth(); break;
            case 2: getHealth(); break;
            case 3: setExerciseRoutine(); break;
            case 4: getExerciseRoutine(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

int main() {
    showMenu();
    return 0;
}
