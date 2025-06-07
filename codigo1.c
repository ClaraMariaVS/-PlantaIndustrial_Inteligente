// ===== codigo 1 =====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 256
#define MAX_SENSORS 100
#define MAX_ID 64
#define MAX_VAL 64

typedef struct {
    long timestamp;
    char value[MAX_VAL];
} Reading;

int compare(const void *a, const void *b) {
    Reading *ra = (Reading *)a;
    Reading *rb = (Reading *)b;
    return (ra->timestamp - rb->timestamp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    Reading *sensor_data[MAX_SENSORS];
    int sensor_count[MAX_SENSORS] = {0};
    char sensor_ids[MAX_SENSORS][MAX_ID];
    int sensor_total = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), in)) {
        long ts;
        char id[MAX_ID], val[MAX_VAL];
        sscanf(line, "%ld %s %s", &ts, id, val);

        int idx = -1;
        for (int i = 0; i < sensor_total; i++) {
            if (strcmp(sensor_ids[i], id) == 0) {
                idx = i;
                break;
            }
        }
        if (idx == -1) {
            idx = sensor_total++;
            strcpy(sensor_ids[idx], id);
            sensor_data[idx] = malloc(sizeof(Reading) * 10000);
        }
        int count = sensor_count[idx];
        sensor_data[idx][count].timestamp = ts;
        strcpy(sensor_data[idx][count].value, val);
        sensor_count[idx]++;
    }
    fclose(in);

    for (int i = 0; i < sensor_total; i++) {
        qsort(sensor_data[i], sensor_count[i], sizeof(Reading), compare);
        char filename[MAX_ID + 4];
        sprintf(filename, "%s.dat", sensor_ids[i]);
        FILE *out = fopen(filename, "w");
        for (int j = 0; j < sensor_count[i]; j++) {
            fprintf(out, "%ld %s\n", sensor_data[i][j].timestamp, sensor_data[i][j].value);
        }
        fclose(out);
        free(sensor_data[i]);
    }
    return 0;
}
