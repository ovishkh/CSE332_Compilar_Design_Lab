#include <stdio.h>

int main() {
    char name[100];
    fgets(name, sizeof(name), stdin);

    if ((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')) {
        char initial = name[0];
        if (initial >= 'a' && initial <= 'z') {
            initial = initial - 'a' + 'A';
        }
        printf("%c ", initial);
    }

    for (int i = 0; name[i] != '\0'; i++) {
        if (name[i] == ' ' && ((name[i+1] >= 'a' && name[i+1] <= 'z') || (name[i+1] >= 'A' && name[i+1] <= 'Z'))) {
            char initial = name[i+1];
            if (initial >= 'a' && initial <= 'z') {
                initial = initial - 'a' + 'A';
            }
            printf("%c ", initial);
        }
    }
    printf("\n");
    return 0;
}