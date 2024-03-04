#ifndef _SHADER_H_
#define _SHADER_H_
#include <stdbool.h>

typedef enum {
    VERTEX,
    FRAGMENT,
    PROGRAM
}shader_type_t;

typedef struct {
    unsigned int ID;
}shader_t;

void shader_parse_compile(shader_t *shader, const char* vertexPath, const char* fragmentPath);

void shader_use(shader_t *shader);

void shader_delete(shader_t *shader);

void shader_setBool(shader_t *shader, bool value);

void shader_setInt(shader_t *shader, int value);

void shader_setFloat(shader_t *shader, float value);

#endif
