#include <stdio.h>

int main() {
    // Helper to print 4-byte binary format
    unsigned int experience;
    int i;

    printf("[Magrathea] ❤❤ Project Member Introduction ❤❤\n");
    printf("=====================================================================\n");
    
    // Arthur Dent
    printf("Name         | Arthur Dent\t\tGender     | Male\n");
    printf("Major        | Mechanical Engineering\tExperience | ");
    experience = 15;
    for (i = 3; i >= 0; i--) {
        printf("%08b ", (experience >> (i * 8)) & 0xFF);
    }
    printf("(2) years\n");
    printf("Role         | Architect\t\tSkills | C/C++, Java, Spring, Python, Machine Learning/Deep Learning\n");
    printf("---------------------------------------------------------------------\n");
    printf("Introduction | I built my career working on various projects in SNS, fintech, HR, and media in Silicon Valley.\n");
    printf("             | Through successes and failures, I have gained insights I want to share with you.\n");

    printf("=====================================================================\n");

    // Kim Youngjin
    printf("Name         | Kim Youngjin\t\tGender       | Male\n");
    printf("Major        | Computer Engineering\tExperience   | ");
    experience = 2;
    for (i = 3; i >= 0; i--) {
        printf("%08b ", (experience >> (i * 8)) & 0xFF);
    }
    printf("(2) years\n");
    printf("Role         | Developer\t\tSkills | C#, Python, JavaScript, React, Kotlin\n");
    printf("---------------------------------------------------------------------\n");
    printf("Introduction | Recently, I found immense passion for software development through a personal asset management project using the MAUI framework.\n");
    printf("             | Solving real-world problems with my code is incredible! Successfully developing Magrathea has now become one of my bucket list goals.\n");

    printf("=====================================================================\n");

    // Im Woncheol
    printf("Name         | Im Woncheol\t\tGender       | Male\n");
    printf("Major        | Electronic Engineering\tExperience   | ");
    experience = 1;
    for (i = 3; i >= 0; i--) {
        printf("%08b ", (experience >> (i * 8)) & 0xFF);
    }
    printf("(2) years\n");
    printf("Role         | DBA\t\t\tSkills | Java, PHP, MongoDB, MS SQL, MySQL\n");
    printf("---------------------------------------------------------------------\n");
    printf("Introduction | I believe that applications are ultimately about how they handle data.\n");
    printf("             | While studying Big Data courses in university, I developed a deep interest in data platforms.\n");
    printf("             | I think the success of this project depends on data.\n");
    printf("             | Just thinking about the data we’ll manage in Magrathea already excites me!\n");

    printf("=====================================================================\n");

    // Yoo Goeun
    printf("Name         | Yoo Goeun\t\tGender       | Female\n");
    printf("Major        | Management Information Systems\tExperience   | ");
    experience = 1;
    for (i = 3; i >= 0; i--) {
        printf("%08b ", (experience >> (i * 8)) & 0xFF);
    }
    printf("(2) years\n");
    printf("Role         | Cloud Engineer\t\tSkills | Java, PowerShell, Azure, AWS, GCP\n");
    printf("---------------------------------------------------------------------\n");
    printf("Introduction | I worked on a project with Kim Youngjin, where I was responsible for implementing cloud architecture.\n");
    printf("             | During my school years, I became fascinated with cloud computing, particularly Microsoft Azure.\n");
    printf("             | As I delved deeper, I found that understanding other public cloud platforms became much easier.\n");
    printf("             | I am determined to complete Magrathea's cloud architecture with my own hands!\n");

    printf("=====================================================================\n");

    // Seo Hyekyung
    printf("Name         | Seo Hyekyung\t\tGender       | Female\n");
    printf("Major        | Political Science & International Relations\tExperience   | ");
    experience = 0;
    for (i = 3; i >= 0; i--) {
        printf("%08b ", (experience >> (i * 8)) & 0xFF);
    }
    printf("(2) years\n");
    printf("Role         | Developer\t\tSkills | Python, Swift, Kotlin, Node.js, Figma\n");
    printf("---------------------------------------------------------------------\n");
    printf("Introduction | While I have worked on many projects as academic assignments, this is my first real-world project where a company's success is at stake.\n");
    printf("             | I am both excited and nervous about whether I can perform well.\n");
    printf("             | When I first heard about the Magrathea project, something inside me told me that this was a project worth dedicating myself to.\n");
    printf("             | Having already heard of Arthur’s reputation through LinkedIn, I feel honored to be part of this journey.\n");

    printf("=====================================================================\n");

    return 0;
}
