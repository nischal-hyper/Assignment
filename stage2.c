#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 100
#define MAX_MENTORS 8
#define MAX_NAME_LEN 50
#define MAX_NICKNAME_LEN 20

// Trainee structure with nickname and ability
typedef struct {
    char nickname[MAX_NICKNAME_LEN];
    int nicknameSum;
    int ability;
} Trainee;

// Mentor structure with ID, name, and mentee count
typedef struct {
    int id; // 1 to 8
    char name[MAX_NAME_LEN];
    int menteeCount; // For bonus 1:1 check
} Mentor;

// Global trainee and mentor arrays
Trainee trainees[MAX_TRAINEES];
int traineeCount = 0;

Mentor mentors[MAX_MENTORS];
int mentorCount = 0;

// Convert nickname to integer by summing ASCII codes
int parseIntMember(const char *nickname) {
    int sum = 0;
    while (*nickname) {
        sum += (int)(*nickname);
        nickname++;
    }
    return sum;
}

// Generate random ability between 100 and 1000
int getRandomAbility() {
    return 100 + rand() % 901; // 100 to 1000 inclusive
}

// Initialize trainee list with nicknames and abilities
void initializeTrainees(const char nicknames[][MAX_NICKNAME_LEN], int count) {
    traineeCount = count;
    for (int i = 0; i < count; i++) {
        strncpy(trainees[i].nickname, nicknames[i], MAX_NICKNAME_LEN);
        trainees[i].nickname[MAX_NICKNAME_LEN-1] = '\0'; // safety null-termination
        trainees[i].nicknameSum = parseIntMember(trainees[i].nickname);
        trainees[i].ability = getRandomAbility();
    }
}

// Input up to 8 mentors
void inputMentors() {
    printf("Enter number of mentors (max 8): ");
    scanf("%d", &mentorCount);
    if (mentorCount > MAX_MENTORS) mentorCount = MAX_MENTORS;

    for (int i = 0; i < mentorCount; i++) {
        mentors[i].id = i + 1;
        mentors[i].menteeCount = 0;
        printf("Enter name for mentor %d: ", mentors[i].id);
        scanf("%s", mentors[i].name);
    }
}

// Matching function (trainee modulo 8 matches mentor ID remainder)
void matchMentoring() {
    // Clear mentee counts first
    for (int i = 0; i < mentorCount; i++) {
        mentors[i].menteeCount = 0;
    }

    // Bonus: 1:1 matching enforcement
    // We'll assign trainees to mentors by trainee nicknameSum % mentorCount
    // but if mentor already has mentee, we try next mentor until found.
    for (int i = 0; i < traineeCount; i++) {
        int baseMentorIndex = trainees[i].nicknameSum % mentorCount;
        int assigned = 0;
        int tryCount = 0;
        int mentorIndex = baseMentorIndex;

        while (tryCount < mentorCount) {
            if (mentors[mentorIndex].menteeCount == 0) {
                mentors[mentorIndex].menteeCount = 1;
                // Store mentor ID for output (we print later)
                // We can temporarily store mentor ID in trainees[i].ability (or add another field)
                // Better to create an array to store matched mentor index per trainee
                assigned = 1;
                break;
            }
            mentorIndex = (mentorIndex + 1) % mentorCount;
            tryCount++;
        }

        // If all mentors busy, assign base mentor anyway (break 1:1 rule)
        if (!assigned) {
            mentors[baseMentorIndex].menteeCount++;
            mentorIndex = baseMentorIndex;
        }

        // Store mentor ID index with trainee (use parallel array or extend struct)
        // For simplicity create parallel array:
        // But let's add a mentorID field in Trainee struct for matching
        // (For now, create static array)
    }
}

// We add this array globally to track mentor IDs assigned to trainees
int traineeMentorIDs[MAX_TRAINEES];

// New improved matchMentoring with 1:1:
void matchMentoringWithOneToOne() {
    for (int i = 0; i < mentorCount; i++) {
        mentors[i].menteeCount = 0;
    }

    for (int i = 0; i < traineeCount; i++) {
        int baseMentorIndex = trainees[i].nicknameSum % mentorCount;
        int assigned = 0;
        int tryCount = 0;
        int mentorIndex = baseMentorIndex;

        while (tryCount < mentorCount) {
            if (mentors[mentorIndex].menteeCount == 0) {
                mentors[mentorIndex].menteeCount = 1;
                traineeMentorIDs[i] = mentors[mentorIndex].id;
                assigned = 1;
                break;
            }
            mentorIndex = (mentorIndex + 1) % mentorCount;
            tryCount++;
        }
        if (!assigned) {
            // No mentor free, assign base mentor anyway (violates 1:1)
            mentors[baseMentorIndex].menteeCount++;
            traineeMentorIDs[i] = mentors[baseMentorIndex].id;
        }
    }
}

// Output trainee and mentor assignment
void printMentoringResults() {
    printf("\nTrainee Mentoring Assignments:\n");
    printf("%-20s %-10s %-15s %-10s\n", "Trainee", "TraineeID", "MentorID", "MentorName");
    for (int i = 0; i < traineeCount; i++) {
        int mentorID = traineeMentorIDs[i];
        char *mentorName = NULL;
        // Find mentor name
        for (int j = 0; j < mentorCount; j++) {
            if (mentors[j].id == mentorID) {
                mentorName = mentors[j].name;
                break;
            }
        }
        printf("%-20s %-10d %-15d %-10s\n",
               trainees[i].nickname,
               trainees[i].nicknameSum,
               mentorID,
               mentorName ? mentorName : "Unknown");
    }
}

// Example nicknames for testing
const char testTrainees[][MAX_NICKNAME_LEN] = {
    "alice", "bob", "charlie", "diana",
    "eve", "frank", "grace", "heidi",
    "ivan", "judy"
};

int main() {
    srand((unsigned int)time(NULL));

    initializeTrainees(testTrainees, 10);
    inputMentors();
    matchMentoringWithOneToOne();
    printMentoringResults();

    return 0;
}
