#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_MEMBERS 20
#define MAX_TRAUMA_LEN 256
#define MAX_RESPONSE_LEN 101
#define NUM_QUESTIONS 5
#define MAX_COUNSELING_RESPONSES 100

// Millieway members info from Assignment 1 (example)
typedef struct {
    char nickname[20];
    int age;
} Member;

// Trauma info struct
typedef struct {
    char nickname[20];
    int age;
    char traumaDesc[MAX_TRAUMA_LEN];
    int hasTrauma; // flag to check if trauma entered
} TraumaInfo;

// Counseling questions (read-only)
typedef struct {
    int qid;
    char question[128];
} CounselingQuestion;

// Counseling response struct
typedef struct {
    char nickname[20];
    char question[128];
    char response[MAX_RESPONSE_LEN];
} CounselingResponse;

// Global arrays
Member milliewayMembers[MAX_MEMBERS] = {
    {"alice", 20}, {"bob", 21}, {"charlie", 22}, {"diana", 23},
    {"eve", 20}, {"frank", 21}, {"grace", 22}, {"heidi", 23},
    {"ivan", 24}, {"judy", 20}
};
int memberCount = 10;

TraumaInfo traumaList[MAX_MEMBERS];
int traumaCount = 0;

const CounselingQuestion questions[NUM_QUESTIONS] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

CounselingResponse counselingResponses[MAX_COUNSELING_RESPONSES];
int counselingCount = 0;

// Helper function: find member index by nickname (case insensitive)
int findMemberIndex(const char *nickname) {
    for (int i = 0; i < memberCount; i++) {
        if (strcasecmp(milliewayMembers[i].nickname, nickname) == 0)
            return i;
    }
    return -1;
}

// Find trauma index by nickname, -1 if none
int findTraumaIndex(const char *nickname) {
    for (int i = 0; i < traumaCount; i++) {
        if (strcasecmp(traumaList[i].nickname, nickname) == 0)
            return i;
    }
    return -1;
}

// Function to input trauma info
void inputTrauma() {
    char nickname[20];
    char traumaDesc[MAX_TRAUMA_LEN];
    while(1) {
        printf("Enter nickname for trauma input (or 'exit' to return): ");
        scanf("%s", nickname);
        if (strcasecmp(nickname, "exit") == 0) break;

        int memIdx = findMemberIndex(nickname);
        // Using ternary operator to decide if nickname valid
        (memIdx == -1) ? printf("Error: Nickname '%s' not found. Please try again.\n", nickname) : 0;

        if (memIdx != -1) {
            printf("Enter trauma description (max %d chars): ", MAX_TRAUMA_LEN - 1);
            getchar(); // consume newline
            fgets(traumaDesc, MAX_TRAUMA_LEN, stdin);

            // Remove trailing newline
            size_t len = strlen(traumaDesc);
            if (len > 0 && traumaDesc[len - 1] == '\n') traumaDesc[len - 1] = '\0';

            // Check if trauma entry exists, update or add new
            int traumaIdx = findTraumaIndex(nickname);
            if (traumaIdx == -1) {
                // Add new trauma
                strcpy(traumaList[traumaCount].nickname, milliewayMembers[memIdx].nickname);
                traumaList[traumaCount].age = milliewayMembers[memIdx].age;
                strncpy(traumaList[traumaCount].traumaDesc, traumaDesc, MAX_TRAUMA_LEN);
                traumaList[traumaCount].hasTrauma = 1;
                traumaCount++;
            } else {
                // Update trauma description
                strncpy(traumaList[traumaIdx].traumaDesc, traumaDesc, MAX_TRAUMA_LEN);
                traumaList[traumaIdx].hasTrauma = 1;
            }
            printf("Trauma description saved for %s.\n", nickname);
        }
    }
}

// Helper: list members who have trauma entries
void listTraumaMembers() {
    printf("\nMembers with trauma entries:\n");
    for (int i = 0; i < traumaCount; i++) {
        if (traumaList[i].hasTrauma)
            printf("- %s\n", traumaList[i].nickname);
    }
}

// Check if counseling already completed for member
int hasCompletedCounseling(const char *nickname) {
    int count = 0;
    for (int i = 0; i < counselingCount; i++) {
        if (strcasecmp(counselingResponses[i].nickname, nickname) == 0)
            count++;
    }
    return (count >= 3); // all 3 questions answered
}

// Helper: count how many counseling responses for member
int counselingCountForMember(const char *nickname) {
    int count = 0;
    for (int i = 0; i < counselingCount; i++) {
        if (strcasecmp(counselingResponses[i].nickname, nickname) == 0)
            count++;
    }
    return count;
}

// Add counseling response
void addCounselingResponse(const char *nickname, const char *question, const char *response) {
    if (counselingCount < MAX_COUNSELING_RESPONSES) {
        strncpy(counselingResponses[counselingCount].nickname, nickname, 20);
        strncpy(counselingResponses[counselingCount].question, question, 128);
        strncpy(counselingResponses[counselingCount].response, response, MAX_RESPONSE_LEN);
        counselingCount++;
    } else {
        printf("Counseling response storage full!\n");
    }
}

// Select 3 random unique questions indices
void selectRandomQuestions(int selectedIndices[3]) {
    int picked[NUM_QUESTIONS] = {0};
    int count = 0;
    while(count < 3) {
        int r = rand() % NUM_QUESTIONS;
        if (!picked[r]) {
            picked[r] = 1;
            selectedIndices[count++] = r;
        }
    }
}

// Counseling session function, with pause/resume capability
void counselingSession(const char *nickname) {
    int selectedQuestions[3];
    int answeredCount = counselingCountForMember(nickname);
    int qIndex;

    // Select 3 random questions if no prior answers
    if (answeredCount == 0) {
        selectRandomQuestions(selectedQuestions);
    } else {
        // For resume, find which questions are answered and which remain
        // Simplified: reselect questions, but skip those already answered
        selectRandomQuestions(selectedQuestions);
    }

    char response[MAX_RESPONSE_LEN];
    int start = answeredCount; // start from next unanswered question

    printf("\nCounseling session started for %s\n", nickname);
    printf("You can type 'pause' anytime to pause and exit.\n");

    for (int i = start; i < 3; i++) {
        qIndex = selectedQuestions[i];
        while (1) {
            printf("Q%d: %s\n> ", questions[qIndex].qid, questions[qIndex].question);
            fgets(response, MAX_RESPONSE_LEN, stdin);

            // Remove trailing newline
            size_t len = strlen(response);
            if (len > 0 && response[len - 1] == '\n') response[len - 1] = '\0';

            if (strcasecmp(response, "pause") == 0) {
                printf("Session paused. You can resume later.\n");
                return;
            }
            if (strlen(response) == 0 || strlen(response) > 100) {
                printf("Response must be 1-100 characters. Please try again.\n");
            } else {
                // Save response
                addCounselingResponse(nickname, questions[qIndex].question, response);
                break;
            }
        }
    }
    printf("Counseling session completed for %s.\n", nickname);
}

// View counseling results for a member
void viewCounselingResults(const char *nickname) {
    int traumaIdx = findTraumaIndex(nickname);
    if (traumaIdx == -1) {
        printf("No trauma info found for %s.\n", nickname);
        return;
    }

    printf("\nCounseling results for %s\n", nickname);
    printf("Age: %d\n", traumaList[traumaIdx].age);
    printf("Trauma: %s\n", traumaList[traumaIdx].traumaDesc);

    printf("Counseling Q&A:\n");
    for (int i = 0; i < counselingCount; i++) {
        if (strcasecmp(counselingResponses[i].nickname, nickname) == 0) {
            printf("Q: %s\n", counselingResponses[i].question);
            printf("A: %s\n\n", counselingResponses[i].response);
        }
    }
}

// Trauma management submenu
void overcomeTrauma() {
    char choice[10];
    while (1) {
        printf("\n=== Trauma Management Menu ===\n");
        printf("1. Input Trauma Data\n");
        printf("2. Counseling Session\n");
        printf("3. View Counseling Results\n");
        printf("4. Exit Trauma Management\n");
        printf("Select an option: ");
        scanf("%s", choice);
        getchar(); // consume newline

        if (strcasecmp(choice, "1") == 0 || strcasecmp(choice, "input") == 0) {
            inputTrauma();
        } else if (strcasecmp(choice, "2") == 0 || strcasecmp(choice, "counsel") == 0) {
            if (traumaCount == 0) {
                printf("No trauma data available. Please input trauma data first.\n");
                continue;
            }
            // List members with trauma
            listTraumaMembers();
            printf("Select a nickname for counseling session (or type 'exit'): ");
            char sel[20];
            scanf("%s", sel);
            getchar();
            if (strcasecmp(sel, "exit") == 0) continue;

            // Check trauma entry and start session
            int tIdx = findTraumaIndex(sel);
            if (tIdx == -1 || !traumaList[tIdx].hasTrauma) {
                printf("Invalid nickname or no trauma data found. Try again.\n");
                continue;
            }

            counselingSession(sel);
        } else if (strcasecmp(choice, "3") == 0 || strcasecmp(choice, "view") == 0) {
            printf("Members who completed counseling:\n");
            for (int i = 0; i < traumaCount; i++) {
                if (hasCompletedCounseling(traumaList[i].nickname)) {
                    printf("- %s\n", traumaList[i].nickname);
                }
            }
            printf("Enter nickname to view results (or 'exit'): ");
            char sel[20];
            scanf("%s", sel);
            getchar();
            if (strcasecmp(sel, "exit") == 0) continue;
            viewCounselingResults(sel);
        } else if (strcasecmp(choice, "4") == 0 || strcasecmp(choice, "exit") == 0) {
            break;
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }
}

int main() {
    srand((unsigned int)time(NULL));

    // For testing: call trauma management menu directly
    overcomeTrauma();

    return 0;
}