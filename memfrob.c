#include <stdio.h>
#include <errno.h>
#include <string.h>

#define EXECUTE_STDIN 1
#define NOEXECUTE_STDIN 2
#define PRINT_HELP 4
#define EXECUTE_STRING 8
#define FROB_FILE 16

int main(int argc, char *argv[])
{
    const char *usage = "Usage: memfrob [options]\nAvailable options are:\n"
                        "  -e str    frobnicate string and prints it to stdout\n"
                        "  -f file   frobnicate a file in place\n"
                        "  -h        print help\n"
                        "  --        stop handling options\n"
                        "   -        stop handling options and execute stdin\n";
    int options = 0;
    char *input = NULL;
    char *filename = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            options |= PRINT_HELP;
        } else if (strcmp(argv[i], "-e") == 0) {
            options |= EXECUTE_STRING;
            i++;
            if (i >= argc || input != NULL) {
                goto err_invalid;
            }
            input = argv[i];
        } else if (strcmp(argv[i], "-f") == 0) {
            options |= FROB_FILE;
            i++;
            if (i >= argc || filename != NULL) {
                goto err_invalid;
            }
            filename = argv[i];
        } else if (strcmp(argv[i], "--") == 0) {
            options |= NOEXECUTE_STDIN;
            break;
        } else if (strcmp(argv[i], "-") == 0) {
            options |= EXECUTE_STDIN;
            break;
        } else {
            goto err_invalid;
        }
    }

    if (options & PRINT_HELP) {
        printf(usage);
    }
    if (options & EXECUTE_STRING) {
        while (*input != '\0') {
            putc(*input ^ 42, stdout);
            input++;
        }
        putc('\n', stdout);
    }
    if (options & FROB_FILE) {
        FILE *f = fopen(filename, "r+");
        if (!f) {
            fprintf(stderr, "%s\n", strerror(errno));
            return 1;
        }
        while (1) {
            long pos = ftell(f);
            int c = fgetc(f);
            if (c == EOF) {
                break;
            }
            fseek(f, pos, SEEK_SET);
            fputc(c ^ 42, f);
        }
        fclose(f);
    }
    if (options & EXECUTE_STDIN || options == 0) {
        while (1) {
            int c = fgetc(stdin);
            if (c == EOF) {
                break;
            }
            putc(c ^ 42, stdout);
        }
    }

    return 0;

err_invalid:
    fprintf(stderr, "Invalid arguments\n");
    fprintf(stderr, usage);
    return 1;
}

