#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Utility to strip trailing punctuation (e.g., "Ph.D." → "Ph.D")
void stripTrailingPunctuation(char *word) {
    int len = strlen(word);
    while (len > 0 && ispunct(word[len-1])) {
        word[len-1] = '\0';
        len--;
    }
}

// Part A: Extract initials from a name
void extractInitials(char *name, char *initials) {
    int j = 0;
    int newWord = 1;

    for (int i = 0; name[i] != '\0'; i++) {
        if (isalpha(name[i]) && newWord) {
            initials[j++] = toupper(name[i]);
            newWord = 0;
        } else if (isspace(name[i])) {
            newWord = 1;
        }
    }
    initials[j] = '\0';
}

// Part B: Remove titles and extract initials
void removeTitlesAndExtract(char *name, char *result) {
    char temp[200] = "";
    char nameCopy[200];
    strcpy(nameCopy, name);

    char *titles[] = {
        "dr", "mr", "mrs", "ms", "prof",
        "phd", "md", "bsc", "msc", "ba", "ma",
        "jr", "sr", NULL
    };

    char *token = strtok(nameCopy, " ");
    int first = 1;

    while (token != NULL) {
        char clean[100];
        strcpy(clean, token);

        stripTrailingPunctuation(clean);

        for (int i = 0; clean[i]; i++)
            clean[i] = tolower(clean[i]);

        int isTitle = 0;
        for (int i = 0; titles[i] != NULL; i++) {
            if (strcmp(clean, titles[i]) == 0) {
                isTitle = 1;
                break;
            }
        }

        if (!isTitle) {
            if (!first) strcat(temp, " ");
            strcat(temp, token);
            first = 0;
        }

        token = strtok(NULL, " ");
    }

    extractInitials(temp, result);
}

// Part C: Generate username variants
void generateUsernames(char *name) {
    char nameCopy[200];
    strcpy(nameCopy, name);

    char *token = strtok(nameCopy, " ");
    char firstName[50] = "";
    char lastName[50] = "";

    int count = 0;

    while (token != NULL) {
        if (count == 0)
            strcpy(firstName, token); 

        strcpy(lastName, token); 
        count++;

        token = strtok(NULL, " ");
    }

    if (count < 2) {
        printf("Invalid name format\n");
        return;
    }

    // Lowercase transform
    for (int i = 0; firstName[i]; i++) firstName[i] = tolower(firstName[i]);
    for (int i = 0; lastName[i]; i++) lastName[i] = tolower(lastName[i]);

    printf("Possible usernames: ");
    printf("%c%s, ", firstName[0], lastName);   // first_initial + lastname
    printf("%s%c, ", firstName, lastName[0]);   // firstname + last_initial
    printf("%c_%s\n", firstName[0], lastName);  // first_initial_lastname
}

int main() {
    char initials[50];

    printf("=== Part A: Extract Initials ===\n");

    // Test case 1
    char name1[] = "Mushfiqur Rahman";
    extractInitials(name1, initials);
    printf("Input: \"%s\"\n", name1);
    printf("Output: \"%s\"\n\n", initials);

    // Test case 2
    char name2[] = "Global Variable Counter";
    extractInitials(name2, initials);
    printf("Input: \"%s\"\n", name2);
    printf("Output: \"%s\"\n\n", initials);

    printf("=== Part B: Handle Complex Names ===\n");

    char name3[] = "Dr. John David Smith Ph.D.";
    removeTitlesAndExtract(name3, initials);
    printf("Input: \"%s\"\n", name3);
    printf("Output: \"%s\"\n\n", initials);

    printf("=== Part C: Generate Username Variants ===\n");

    char name4[] = "Rahman Mushfiqur";
    printf("Input: \"%s\"\n", name4);
    generateUsernames(name4);

    return 0;
}
