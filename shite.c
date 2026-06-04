#include <stdio.h>

#define SIZE 999999

int main(int argc, char *argv[]) {
    if (argc < 2 || argv[1] == NULL) {
        printf("\e[31mError:\n No file to edit!\e[0m\n");
        
        return 1;
    }

    char *path = argv[1];

    char buffer[SIZE];
    int index = 0;

    FILE *read_ptr = fopen(path, "r");
    if (read_ptr != NULL) {
	    int ch;
	    while ((ch = fgetc(read_ptr)) != EOF && index < SIZE -1) {
            buffer[index] = (char)ch;
            index++;
        }
        fclose(read_ptr);
    }

    printf("\033[H\033[2J\e[44mEditing:\e[0m \n \e[34m%s\e[0m\n\n\e[44m  Current\e[K\e[0m\n", path);

    for (int i = 0; i < index; i++) {
        putchar(buffer[i]);
    }

    int inp;
    int st = 0;
    int d = 0;

    while ((inp = getchar()) != EOF) {

        if (index < SIZE - 1) {
            buffer[index] = (char)inp;
            index++;
        } else {
            printf("\n\e[31mError: Buffer full!\e[0m\n");
        }

        if (inp == ':') {
            st = 1;
        } else if (inp == '\\' && st == 1) {
            st = 2;
        } else if (inp == 'q' && st == 2) {
            break;
        } else if (inp == 'b' && st == 2) {
            index -= 2;

            if (index < 0) {
                index = 0;
            }

            index--;

            if (index > 0 && buffer[index -1 ] == '\n') {
                index--;
            }

            st = 0;
            continue;
        } else if (inp == 'w' && st == 2) {
            FILE *fptr = fopen(path, "w");
            
            if (fptr != NULL) {
                for (int i = 0; i < (index - 3); i++) {
                    fputc(buffer[i], fptr);
                }
                fputc('\n', fptr);

                fclose(fptr);
                break;
            }
        } else if (inp == 'd' && st == 2) {
            st = 3;
            d = 0;
            index -= 3;
            continue;
        } else if (st == 3) {
            if (inp >= '0' && inp <= '9') {
                d = (d * 10) + (inp - '0');
                continue;
            } else {
                int length = 0;
                int temp = d;
                
                if (temp == 0) {
                    length = 1;
                }

                while (temp > 0) {
                    length++;
                    temp /= 10;
                }

                int cmd = 1 + length;

                index -= (d + cmd);
                if (index < 0) {
                    index = 0;
                }
                st = 0;

                if (inp == ':') {
                    st = 1;
                }

                buffer[index] = (char)inp;
                index++;
                continue;
            }
        } else {
            st = 0;
        }
    }

    printf("\033[H\033[2J");
    return 0;
}
