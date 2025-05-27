#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 4
#define MAX_QUESTIONS 10
#define MAX_QUIZ 5

// Structures
struct KoreanQuestion {
    int id;
    char question[100];
    char correctAnswer[50];
};

struct Trainee {
    char name[50];
    char nickname[30];
    char nationality[30];
    int score;
    char passStatus;
};

struct AnswerRecord {
    int questionId;
    char correctness;
};

// Sample data (normally loaded from a file)
struct KoreanQuestion questionBank[MAX_QUESTIONS] = {
    {1, "How do you say 'Hello' in Korean?", "Annyeong"},
    {2, "How do you say 'Thank you' in Korean?", "Gamsahamnida"},
    {3, "What is 'Love' in Korean?", "Sarang"},
    {4, "What is the Korean word for 'Friend'?", "Chingu"},
    {5, "How do you say 'Delicious' in Korean?", "Mashisseoyo"},
    {6, "How do you say 'Yes' in Korean?", "Ne"},
    {7, "How do you say 'No' in Korean?", "Aniyo"},
    {8, "What is the Korean word for 'Water'?", "Mul"},
    {9, "How do you say 'Goodbye' in Korean?", "Annyeonghi gaseyo"},
    {10, "What is 'Music' in Korean?", "Eumak"}
};

struct Trainee trainees[MAX_TRAINEES] = {
    {"Park Ji-yeon", "Jiyeon", "Korea", 0, 'X'},
    {"Alex Smith", "Alex", "USA", 0, 'X'},
    {"Liu Wei", "Wei", "China", 0, 'X'},
    {"Maria Gonzalez", "Maria", "Mexico", 0, 'X'}
};

struct AnswerRecord answerSheet[MAX_QUIZ];

// Function to check answer
int isAnswer(int qid, char* userAns, int index) {
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        if (questionBank[i].id == qid) {
            if (strcmp(questionBank[i].correctAnswer, userAns) == 0) {
                answerSheet[index].correctness = 'O';
                return 1;
            }
        }
    }
    answerSheet[index].correctness = 'X';
    return 0;
}

// Select a non-Korean trainee
int selectRandomTakers() {
    int idx;
    srand(time(NULL));
    do {
        idx = rand() % MAX_TRAINEES;
    } while (strcmp(trainees[idx].nationality, "Korea") == 0);

    printf("Welcome, %s, to the Korean quiz session!\n", trainees[idx].name);
    return idx;
}

// Serve the quiz
void serveRandomQuiz(int traineeIndex) {
    int used[MAX_QUESTIONS] = {0};
    int totalScore = 0;
    int count = 0;
    printf("\nThe quiz will begin in 30 seconds...\n\n");
    // sleep(30); // Uncomment in actual use

    while (count < MAX_QUIZ) {
        int qid = rand() % MAX_QUESTIONS;
        if (used[qid]) continue;
        used[qid] = 1;

        printf("Q%d: %s\nAnswer: ", count + 1, questionBank[qid].question);
        char userAns[100];
        fgets(userAns, sizeof(userAns), stdin);
        userAns[strcspn(userAns, "\n")] = 0;  // Remove newline

        answerSheet[count].questionId = questionBank[qid].id;
        if (isAnswer(questionBank[qid].id, userAns, count)) {
            totalScore += 20;
        }
        count++;
    }

    // Store and display result
    trainees[traineeIndex].score = totalScore;
    trainees[traineeIndex].passStatus = (totalScore >= 80) ? 'O' : 'X';

    printf("\nAnswer Sheet:\n");
    for (int i = 0; i < MAX_QUIZ; i++) {
        printf("QID: %d - %c\n", answerSheet[i].questionId, answerSheet[i].correctness);
    }
    printf("Total Score: %d\n", totalScore);
    printf("Pass Status: %c\n", trainees[traineeIndex].passStatus);
}

// Entry point
void testKoreanLang() {
    int index = selectRandomTakers();
    serveRandomQuiz(index);
}

int main() {
    testKoreanLang();
    return 0;
}
