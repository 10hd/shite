#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || argv[1] == NULL) {
        printf("\e[31mError:\n No file to edit!\e[0m\n");
        
        return 1;
    }

    char *path = argv[1];

    printf("\033[H\033[2J\e[44mEditing:\e[0m \n \e[34m%s\e[0m\n\n\e[44m  Current\e[K\e[0m\n", path);

    int inp;
    int st = 0;

    FILE *fptr;

    char buffer[123456];
    int index = 0;

    while (1) {
        inp = getchar();

        if (index < 123455) {
            buffer[index] = inp;
            index++;
        }

        if (inp == ':') {
            st = 1;
        } else if (inp == '\\' && st == 1) {
            st = 2;
        } else if (inp == 'q' && st == 2) {
            break;
        } else if (inp == 'b' && st == 2) {
            index -= 3;

            if (index > 0 && buffer[index -1 ] == '\n') {
                index--;
            }
        } else if (inp == 'w' && st == 2) {
            fptr = fopen(path, "w");
            
            if (fptr != NULL) {
                for (int i = 0; i < (index - 3); i++) {
                    fputc(buffer[i], fptr);
                }
                fputc('\n', fptr);

                fclose(fptr);
                break;
            }
        } else {
            st = 0;
        }
    }

    printf("\033[H\033[2J");
    return 0;
}