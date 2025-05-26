#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CANDIDATES 6
#define NUM_CATEGORIES 5
#define MAX_NAME_LEN 30

// Candidate data
char candidate_names[NUM_CANDIDATES][MAX_NAME_LEN] = {
    "Jiyeon Park", "Ethan Smith", "Helena Silva",
    "Liam Wilson", "Olivia Brown", "Noah Lee"
};
int candidate_ids[NUM_CANDIDATES] = {
    100001, 100002, 100003, 100004, 100005, 100006
};

// Scoring sheet [ID, Music, Dance, Vocal, Visual, Expression, Total]
int scoring_sheets[NUM_CANDIDATES][7];

// Function to validate score input
int get_valid_score(const char* category) {
    int score;
    while (1) {
        printf("%s (10-100): ", category);
        scanf("%d", &score);
        if (score >= 10 && score <= 100) break;
        printf("Invalid input. Please enter a score between 10 and 100.\n");
    }
    return score;
}

// Function to display all scores
void review_input() {
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Submission completed.\n");
    printf("Please review your input!\n");
    printf("------------------------------------\n");
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("%s: Total %d\n", candidate_names[i], scoring_sheets[i][6]);
    }
}

// Function to calculate total score
void calculate_total_scores() {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        scoring_sheets[i][6] = 0;
        for (int j = 1; j <= NUM_CATEGORIES; j++) {
            scoring_sheets[i][6] += scoring_sheets[i][j];
        }
    }
}

// Function to modify scores
void modify_scores() {
    char name[MAX_NAME_LEN];
    int id, found;

    while (1) {
        printf("Enter candidate name to modify (or type 'exit' to finish): ");
        getchar(); // flush newline
        fgets(name, MAX_NAME_LEN, stdin);
        name[strcspn(name, "\n")] = 0;

        if (strcmp(name, "exit") == 0) break;

        printf("Enter candidate 6-digit ID: ");
        scanf("%d", &id);

        found = 0;
        for (int i = 0; i < NUM_CANDIDATES; i++) {
            if (strcmp(candidate_names[i], name) == 0 && candidate_ids[i] == id) {
                found = 1;
                printf("Modifying scores for %s (ID: %d)\n", name, id);
                scoring_sheets[i][1] = get_valid_score("Music Proficiency");
                scoring_sheets[i][2] = get_valid_score("Dance");
                scoring_sheets[i][3] = get_valid_score("Vocal");
                scoring_sheets[i][4] = get_valid_score("Visual");
                scoring_sheets[i][5] = get_valid_score("Expression");
                scoring_sheets[i][6] = scoring_sheets[i][1] + scoring_sheets[i][2] +
                                      scoring_sheets[i][3] + scoring_sheets[i][4] +
                                      scoring_sheets[i][5];
                break;
            }
        }

        if (!found) {
            printf("Candidate not found. Please check the name and ID.\n");
        }
    }
}

// Function to select top 4 candidates
void select_top_candidates() {
    int i, j, max_idx;
    int temp_score;
    char temp_name[MAX_NAME_LEN];
    int temp_id;

    // Simple selection sort
    for (i = 0; i < NUM_CANDIDATES - 1; i++) {
        max_idx = i;
        for (j = i + 1; j < NUM_CANDIDATES; j++) {
            if (scoring_sheets[j][6] > scoring_sheets[max_idx][6])
                max_idx = j;
        }
        if (max_idx != i) {
            // Swap scores
            for (int k = 0; k < 7; k++) {
                temp_score = scoring_sheets[i][k];
                scoring_sheets[i][k] = scoring_sheets[max_idx][k];
                scoring_sheets[max_idx][k] = temp_score;
            }
            // Swap names and IDs
            strcpy(temp_name, candidate_names[i]);
            strcpy(candidate_names[i], candidate_names[max_idx]);
            strcpy(candidate_names[max_idx], temp_name);

            temp_id = candidate_ids[i];
            candidate_ids[i] = candidate_ids[max_idx];
            candidate_ids[max_idx] = temp_id;
        }
    }

    printf("=======================================\n");
    printf("Compiling final selection results...\n");
    printf("=======================================\n");
    printf("###########################################\n");
    printf("# Congratulations! Welcome to Milliways!  #\n");
    printf("###########################################\n");

    for (i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, candidate_names[i]);
    }
}

int main() {
    char judge_name[30], expertise[30];
    char submit;
    int i;

    while (1) {
        printf("####################################\n");
        printf("#     Audition Evaluation Entry    #\n");
        printf("####################################\n");
        printf("> Judge Name: ");
        fgets(judge_name, sizeof(judge_name), stdin);
        judge_name[strcspn(judge_name, "\n")] = 0;

        printf("> Expertise: ");
        fgets(expertise, sizeof(expertise), stdin);
        expertise[strcspn(expertise, "\n")] = 0;

        printf("++++++++++++++++++++++++++++++++++++\n");

        for (i = 0; i < NUM_CANDIDATES; i++) {
            printf("Candidate: %s\n", candidate_names[i]);
            scoring_sheets[i][0] = candidate_ids[i]; // ID
            scoring_sheets[i][1] = get_valid_score("Music Proficiency");
            scoring_sheets[i][2] = get_valid_score("Dance");
            scoring_sheets[i][3] = get_valid_score("Vocal");
            scoring_sheets[i][4] = get_valid_score("Visual");
            scoring_sheets[i][5] = get_valid_score("Expression");
            printf("------------------------------------\n");
        }

        calculate_total_scores();
        review_input();

        printf("Would you like to submit? (Y/N): ");
        getchar(); // flush newline
        scanf("%c", &submit);
        if (submit == 'Y' || submit == 'y') {
            printf("***Final submission completed.***\n");
            break;
        } else {
            modify_scores();
            printf("No more modifications needed. Exiting.\n");
            break;
        }
    }

    select_top_candidates();
    return 0;
}
