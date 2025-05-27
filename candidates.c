#include <stdio.h>
#include <stdlib.h>

#define NUM_CANDIDATES 6

char *candidate01[11];
char *candidate02[11];
char *candidate03[11];
char *candidate04[11];
char *candidate05[11];
char *candidate06[11];

char **member_info[NUM_CANDIDATES] = {
    candidate01, candidate02, candidate03,
    candidate04, candidate05, candidate06
};

// Function to calculate age from birth year
int calculate_age(const char *dob) {
    int year;
    sscanf(dob, "%4d", &year);
    return 2025 - year; // Fixed current year to 2025
}

// Function to interpret TOPIK level
const char* get_topik_description(const char *level) {
    if (level[0] == '0')
        return "Native";
    return level;
}

// Read a line of input into buffer
void read_input(char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // remove newline
}

int main(void) {
    char *labels[11] = {
        "Name", "Date of Birth (YYYY/MM/DD format)", "Gender (F for Female, M for Male)",
        "Email", "Nationality", "BMI", "Primary Skill", "Secondary Skill",
        "Korean Proficiency Level (TOPIK)", "MBTI", "Introduction"
    };

    char group_name[100];
    char temp[256];
    int i = 0;

    // Group name input using getchar
    printf("Enter audition group name: ");
    int c, idx = 0;
    while ((c = getchar()) != '\n' && idx < sizeof(group_name) - 1) {
        group_name[idx++] = (char)c;
    }
    group_name[idx] = '\0';

    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Entry\n", group_name);
    printf("####################################\n");

    while (i < NUM_CANDIDATES) {
        printf("Entering information for candidate %d.\n", i + 1);
        printf("---------------------------------\n");

        for (int j = 0; j < 11; j++) {
            printf("%d. %s: ", j + 1, labels[j]);
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0'; // Remove newline
            member_info[i][j] = (char *)malloc(sizeof(char) * (strlen(temp) + 1));
            if (member_info[i][j] != NULL) {
                strcpy(member_info[i][j], temp);
            }
        }
        printf("=================================\n");
        i++;
    }

    // Display section
    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Review\n", group_name);
    printf("####################################\n");
    printf("=============================================================================================\n");
    printf("Name                | Age | DOB       | Gender | Email                 | Nationality | BMI  | Primary Skill | Secondary Skill | TOPIK  | MBTI |\n");
    printf("=============================================================================================\n");

    for (i = 0; i < NUM_CANDIDATES; i++) {
        char dob_compact[9];
        int year, month, day;
        sscanf(member_info[i][1], "%d/%d/%d", &year, &month, &day);
        sprintf(dob_compact, "%04d%02d%02d", year, month, day);
        int age = calculate_age(dob_compact);

        printf("%-18s | %3d | %-8s | %-6s | %-21s | %-11s | %-4s | %-13s | %-15s | %-6s | %-4s |\n",
               member_info[i][0], age, dob_compact, member_info[i][2],
               member_info[i][3], member_info[i][4], member_info[i][5],
               member_info[i][6], member_info[i][7],
               get_topik_description(member_info[i][8]), member_info[i][9]);

        printf("-------------------------------------------------------------------------------------\n");
        printf("%s\n", member_info[i][10]);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    // Free allocated memory
    for (i = 0; i < NUM_CANDIDATES; i++) {
        for (int j = 0; j < 11; j++) {
            free(member_info[i][j]);
        }
    }

    return 0;
}
