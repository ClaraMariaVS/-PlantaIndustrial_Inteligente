// ===== codigo 2 =====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VAL 64

typedef struct {
    long timestamp;
    char value[MAX_VAL];
} Reading;

Reading binary_search(Reading *data, int size, long target) {
    int low = 0, high = size - 1;
    Reading closest = data[0];
    long min_diff = labs(target - data[0].timestamp);

    while (low <= high) {
        int mid = (low + high) / 2;
        long diff = labs(target - data[mid].timestamp);
        if (diff < min_diff) {
            min_diff = diff;
            closest = data[mid];
        }
        if (data[mid].timestamp < target) low = mid + 1;
        else if (data[mid].timestamp > target) high = mid - 1;
        else break;
    }
    return closest;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <sensor> <timestamp>\n", argv[0]);
        return 1;
    }
    char filename[128];
    sprintf(filename, "%s.dat", argv[1]);

    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Arquivo não encontrado");
        return 1;
    }

    Reading *data = malloc(sizeof(Reading) * 10000);
    int count = 0;
    while (fscanf(f, "%ld %s", &data[count].timestamp, data[count].value) == 2) count++;
    fclose(f);

    long target = atol(argv[2]);
    Reading result = binary_search(data, count, target);
    printf("%ld %s\n", result.timestamp, result.value);
    free(data);
    return 0;
}
