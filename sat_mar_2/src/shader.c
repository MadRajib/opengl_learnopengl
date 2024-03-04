#include "shader.h"

static void checkCompileErrors(unsigned int shader, shader_type_t type) {
    int success;
    char infoLog[1024];
    if (type != PROGRAM) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::shader_compilation_error of type: %s\n", infoLog);
        }
    } else {
        glGetShaderiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::program_linking_error of type: %s\n", infoLog);
        }
        
    }
}

void shader_parse_compile(shader_t *shader, const char* vertexPath, const char* fragmentPath) {
    errno = 0;
    FILE* file = fopen(vertexPath, "r");
    if(!file) {
        fprintf(stderr, "enable to open the file error :%d\n", errno);
        exit(-1);
    }

    fseek(file, 0, SEEK_END);
    unsigned int size =  ftell(file) + 1;
    rewind(file);

    char vertShader[size];
    size = fread(vertShader, sizeof(char), size, file);
    vertShader[size] = '\0';
    fclose(file);

    const char* vShaderCode = (const char *)vertShader;
    errno = 0;
    file = fopen(fragmentPath, "r");
    if(!file) {
        fprintf(stderr, "enable to open the file error :%d\n", errno);
        exit(-1);
    }

    fseek(file, 0, SEEK_END);
    size =  ftell(file) + 1;
    rewind(file);

    char fragShader[size + 1];
    size = fread(fragShader, sizeof(char), size, file);
    fragShader[size] = '\0';
    fclose(file);
    const char* fShaderCode = (const char *)fragShader;
    
    // 2. compile shaders
    unsigned int vert, frag;
    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vShaderCode, NULL);
    glCompileShader(vert);
    checkCompileErrors(vert, VERTEX);

    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fShaderCode, NULL);
    glCompileShader(frag);
    checkCompileErrors(frag, FRAGMENT);

    shader->ID = glCreateProgram();
    glAttachShader(shader->ID, vert);
    glAttachShader(shader->ID, frag);
    glLinkProgram(shader->ID); 
    checkCompileErrors(shader->ID, PROGRAM);
    
    glDeleteShader(vert);
    glDeleteShader(frag);
}

void shader_use(shader_t *shader) {
    glUseProgram(shader->ID);
}

void shader_delete(shader_t *shader) {
    glDeleteProgram(shader->ID);
}

void shader_setBool(shader_t *shader, bool value) {
    glUniform1i(glGetUniformLocation(shader->ID,""), (int)value);
}

void shader_setInt(shader_t *shader, int value) {
    glUniform1i(glGetUniformLocation(shader->ID,""), value);
}
void shader_setFloat(shader_t *shader, float value) {
    glUniform1i(glGetUniformLocation(shader->ID,""), value);
}
