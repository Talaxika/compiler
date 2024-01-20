#include "include/io.h"

char* slo_read_file(const char* filename)
{
    FILE* fp = NULL;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "rb");
    if (NULL == fp) {
        printf("Could not open file %s to read\n", filename);
        return NULL;
    }
    char* buffer = (char*) calloc(1, sizeof(char));
    buffer[0] = '\0';

    while ((read = getline(&line, &len, fp)) != -1)
    {
        buffer = (char*) realloc(buffer, (strlen(buffer) + strlen(line) + 1) * sizeof(char));
        strcat(buffer, line);
    }
    fclose(fp);
    if(NULL != line) {
        free(line);
        line = NULL;
    }

    return buffer;
}