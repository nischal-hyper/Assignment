/* stage1.c - Magrathea Trainee Training Program Menu System */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAIN_MENU_COUNT 3
#define TRAINING_MENU_COUNT 8

/* Menu strings stored as 1D arrays of strings */
const char *main_menu[MAIN_MENU_COUNT] = {
    "1. Audition Management",
    "2. Training",
    "3. Debut"
};

const char *training_menu[TRAINING_MENU_COUNT] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

/* Stores the result of each training stage: 'P' = Passed, 'F' = Failed, ' ' = Not attempted */
char training_results[TRAINING_MENU_COUNT] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

/* Function Prototypes */
void audition_management(void);
void training_menu_function(void);
void debut(void);
void print_main_menu(void);
void print_training_menu(void);
int is_stage_available(int stage);
int all_preceding_stages_passed(int stage);

int main(void)
{
    char input[10];
    int quit_flag = 0;

    while (!quit_flag)
    {
        print_main_menu();
        printf("Select a menu (or 0, Q, q to quit): ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        /* Remove newline */
        if (input[strlen(input) - 1] == '\n')
            input[strlen(input) - 1] = '\0';

        if (strlen(input) == 0 || strcmp(input, "0") == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0)
        {
            quit_flag = 1;
            break;
        }

        if (strcmp(input, "1") == 0)
        {
            audition_management();
        }
        else if (strcmp(input, "2") == 0)
        {
            training_menu_function();
        }
        else if (strcmp(input, "3") == 0)
        {
            debut();
        }
        else
        {
            printf("Invalid input. Please select a valid option.\n");
        }
    }

    printf("Exiting program.\n");
    return 0;
}

/* Print Main Menu */
void print_main_menu(void)
{
    printf("\n=== Magrathea Main Menu ===\n");
    for (int i = 0; i < MAIN_MENU_COUNT; i++)
    {
        printf("%s\n", main_menu[i]);
    }
}

/* Audition Management Stub */
void audition_management(void)
{
    printf("\n-- Audition Management --\n");
    printf("Feature not implemented yet.\n");
}

/* Debut Stub */
void debut(void)
{
    printf("\n-- Debut --\n");
    printf("Feature not implemented yet.\n");
}

/* Training Menu Implementation */
void training_menu_function(void)
{
    char input[10];
    int quit_training = 0;

    while (!quit_training)
    {
        print_training_menu();
        printf("Select training stage (or 0, Q, q to return): ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        /* Remove newline */
        if (input[strlen(input) - 1] == '\n')
            input[strlen(input) - 1] = '\0';

        if (strlen(input) == 0 || strcmp(input, "0") == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0)
        {
            quit_training = 1;
            break;
        }

        /* Convert input to integer */
        int stage = atoi(input);
        if (stage < 1 || stage > TRAINING_MENU_COUNT)
        {
            printf("Invalid stage number. Please select 1 to 8.\n");
            continue;
        }

        /* Check if stage is already passed */
        if (training_results[stage - 1] == 'P')
        {
            printf("Stage %d already passed and cannot be re-selected.\n", stage);
            continue;
        }

        /* Check stage availability rules */
        if (!is_stage_available(stage))
        {
            printf("Stage %d is not accessible yet. Complete previous stages first.\n", stage);
            continue;
        }

        /* Ask if user wants to enter evaluation result */
        printf("Would you like to enter the evaluation result? (Y/N): ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        if (input[strlen(input) - 1] == '\n')
            input[strlen(input) - 1] = '\0';

        if (strlen(input) == 0)
            continue;

        char yn = toupper(input[0]);

        if (yn == 'Y')
        {
            /* Ask if passed */
            printf("Did you complete the training and pass the certification? (Y/N): ");
            if (fgets(input, sizeof(input), stdin) == NULL)
                break;

            if (input[strlen(input) - 1] == '\n')
                input[strlen(input) - 1] = '\0';

            if (strlen(input) == 0)
                continue;

            char pass = toupper(input[0]);
            if (pass == 'Y')
            {
                training_results[stage - 1] = 'P';
                printf("Stage %d marked as PASSED.\n", stage);
            }
            else
            {
                training_results[stage - 1] = 'F';
                printf("Stage %d marked as FAILED.\n", stage);
            }
        }
        else if (yn == 'N')
        {
            printf("Returning to training menu.\n");
        }
        else
        {
            printf("Invalid input, returning to training menu.\n");
        }
    }
}

/* Print Training Menu with status */
void print_training_menu(void)
{
    printf("\n-- Training Menu --\n");
    for (int i = 0; i < TRAINING_MENU_COUNT; i++)
    {
        printf("%s", training_menu[i]);
        if (training_results[i] == 'P')
            printf(" [PASSED]");
        else if (training_results[i] == 'F')
            printf(" [FAILED]");
        printf("\n");
    }
}

/* Check if stage is accessible given the rules */
int is_stage_available(int stage)
{
    /* Stages 1 and 2 must be passed in sequence before stages 3-8 */
    if (stage == 1)
    {
        /* Always available */
        return 1;
    }
    else if (stage == 2)
    {
        /* Stage 1 must be passed */
        return (training_results[0] == 'P') ? 1 : 0;
    }
    else
    {
        /* Stages 3-8 require both stages 1 and 2 passed */
        if (training_results[0] != 'P' || training_results[1] != 'P')
            return 0;
        else
            return 1;
    }
}

