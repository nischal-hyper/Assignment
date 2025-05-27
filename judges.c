#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_LEN 512
#define FIELD_COUNT 7

char judges_array[MAX_JUDGES][MAX_LEN];

void parse_and_display_judge(const char *entry, int index) {
    char copy[MAX_LEN];
    strcpy(copy, entry);

    char *fields[FIELD_COUNT];
    int count = 0;

    char *token = strtok(copy, ",");
    while (token != NULL && count < FIELD_COUNT) {
        // Remove leading/trailing spaces
        while (*token == ' ') token++;
        fields[count++] = token;
        token = strtok(NULL, ",");
    }

    if (count != FIELD_COUNT) {
        printf("Error: Could not parse judge %d properly.\n", index + 1);
        return;
    }

    printf("[Judge %d]\n", index + 1);
    printf("Name: %s\n", strchr(fields[0], ':') ? strchr(fields[0], ':') + 1 : fields[0]);
    printf("Gender: %s\n", strchr(fields[1], ':') ? strchr(fields[1], ':') + 1 : fields[1]);
    printf("Affiliation: %s\n", strchr(fields[2], ':') ? strchr(fields[2], ':') + 1 : fields[2]);
    printf("Title: %s\n", strchr(fields[3], ':') ? strchr(fields[3], ':') + 1 : fields[3]);
    printf("Expertise: %s\n", strchr(fields[4], ':') ? strchr(fields[4], ':') + 1 : fields[4]);
    printf("Email: %s\n", strchr(fields[5], ':') ? strchr(fields[5], ':') + 1 : fields[5]);
    printf("Phone: %s\n", strchr(fields[6], ':') ? strchr(fields[6], ':') + 1 : fields[6]);
    printf("-----------------------------------\n");
}

int main(void) {
    char project[100];
    int total_judges = 0;
    int selected_members = 0;
    char input[MAX_LEN];

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");

    printf("Participating Project: ");
    fgets(project, sizeof(project), stdin);
    project[strcspn(project, "\n")] = '\0'; // remove newline

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    getchar(); // consume leftover newline

    if (total_judges > MAX_JUDGES) {
        printf("Error: Too many judges (max %d).\n", MAX_JUDGES);
        return 1;
    }

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar(); // consume newline

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    int entered = 0;
    while (1) {
        if (entered >= total_judges) break;

        printf("Judge %d: ", entered + 1);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // remove newline

        // Copy string to temp for parsing
        char temp[MAX_LEN];
        strcpy(temp, input);
        int commas = 0;
        for (int i = 0; temp[i]; i++) {
            if (temp[i] == ',') commas++;
        }

        if (commas != FIELD_COUNT - 1) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue;
        }

        strcpy(judges_array[entered], input);
        entered++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("\"Should we check the judge information?\" (Y/N): ");

    char choice = getchar();
    getchar(); // consume leftover newline

    if (choice == 'N') {
        printf("Exiting program.\n");
        return 0;
    }

    if (choice == 'Y') {
        printf("\n[%s] Should we check the judge information? %c\n", project, choice);
        printf("####################################\n");
        printf("#        Display Judge Data        #\n");
        printf("####################################\n");

        for (int i = 0; i < total_judges; i++) {
            parse_and_display_judge(judges_array[i], i);
        }
    }

    return 0;
}
