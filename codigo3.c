// ===== codigo 3 =====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_SENSORS 10
#define MAX_ID 64
#define MAX_TYPE 16

const char *bools[] = {"true", "false"};
const char *strings[] = {"ABC", "XYZ", "HELLO", "WORLD", "SENSOR", "TEMP"};

int main(int argc, char *argv[]) {
    if (argc < 5 || (argc - 3) % 2 != 0) {
        printf("Uso: %s <inicio> <fim> <sensor1> <tipo1> [<sensor2> <tipo2> ...]\n", argv[0]);
        return 1;
    }
    long start = atol(argv[1]), end = atol(argv[2]);
    int sensors = (argc - 3) / 2;

    FILE *out = fopen("teste.txt", "w");
    srand(time(NULL));

    for (int i = 0; i < sensors; i++) {
        char *id = argv[3 + i * 2];
        char *type = argv[4 + i * 2];
        for (int j = 0; j < 2000; j++) {
            long ts = start + rand() % (end - start + 1);
            fprintf(out, "%ld %s ", ts, id);
            if (strcmp(type, "int") == 0) fprintf(out, "%d\n", rand() % 100);
            else if (strcmp(type, "bool") == 0) fprintf(out, "%s\n", bools[rand() % 2]);
            else if (strcmp(type, "float") == 0) fprintf(out, "%.2f\n", (rand() % 10000) / 100.0);
            else if (strcmp(type, "string") == 0) fprintf(out, "%s\n", strings[rand() % 6]);
        }
    }
    fclose(out);
    return 0;
}
