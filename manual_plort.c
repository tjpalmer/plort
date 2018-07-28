#include <stdbool.h>
#include <GLES3/gl3.h>
#include <SDL.h>

void plort_build_scene(void);
void plort_init_gles3(void);
void plort_link_program(GLuint program);
void plort_paint(SDL_Window *window);
GLuint plort_create_shader(GLenum type, char const *source);

extern char *plort_fragment_source;
extern char *plort_vertex_source;
extern float plort_positions[9];
extern GLuint plort_position_buffer;

#define PLORT_ATTRIB_POSITION 0

int main(int argc, char **argv) {
    printf("Hello, world!\n");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to init sdl: %s\n", SDL_GetError());
    }
    plort_init_gles3();
    SDL_Window *window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    void *context = SDL_GL_CreateContext(window);
    if (!context) {
        printf("no context for us\n");
    }
    plort_build_scene();
    plort_paint(window);
    SDL_Event event;
    bool done = false;
    bool dirty = true;
    while (!done) {
        if (dirty) {
            plort_paint(window);
            dirty = false;
        }
        if (SDL_WaitEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: {
                done = true;
                break;
            }
            case SDL_WINDOWEVENT: {
                switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED: {
                    dirty = true;
                    break;
                }
                }
                break;
            }
            }
        }
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("Goodbye, world!\n");
    return 0;
}

void plort_init_gles3(void) {
    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES)) {
        printf("failed to set gles\n");
    }
    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3)) {
        printf("failed to set gles 3\n");
    }
}

void plort_build_scene(void) {
    GLuint program = glCreateProgram();
    if (!program) {
        printf("no program for us\n");
    }
    GLuint fragment_shader = plort_create_shader(GL_FRAGMENT_SHADER, plort_fragment_source);
    GLuint vertex_shader = plort_create_shader(GL_VERTEX_SHADER, plort_vertex_source);
    if (!(fragment_shader && vertex_shader)) {
        printf("no shaders for us\n");
    }
    glBindAttribLocation(program, PLORT_ATTRIB_POSITION, "position");
    glAttachShader(program, fragment_shader);
    glAttachShader(program, vertex_shader);
    plort_link_program(program);
    glUseProgram(program);
    glEnableVertexAttribArray(PLORT_ATTRIB_POSITION);
    glGenBuffers(1, &plort_position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, plort_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plort_positions), plort_positions, GL_STATIC_DRAW);
}

void plort_paint(SDL_Window *window) {
    int size_x = 0;
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, plort_position_buffer);
    glVertexAttribPointer(PLORT_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    SDL_GL_SwapWindow(window);
}

GLuint plort_create_shader(GLenum type, char const *source) {
    GLuint shader = glCreateShader(type);
    if (!shader) {
        return 0;
    }
    GLint sizes = strlen(source);
    glShaderSource(shader, 1, &source, &sizes);
    glCompileShader(shader);
    GLint is_compiled = {0};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    if (!is_compiled) {
        return 0;
    }
    return shader;
}

char *plort_fragment_source = 
    "void main() {\n"
    "    gl_FragColor = vec4(1, 1, 0, 1);\n"
    "}\n";

char *plort_vertex_source = 
    "attribute vec3 position;\n"
    "\n"
    "void main(void) {\n"
    "    gl_Position = vec4(position, 1.0);\n"
    "}\n";

void plort_link_program(GLuint program) {
    glLinkProgram(program);
    GLint is_linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
    if (!is_linked) {
        printf("no link for us\n");
    }
}

GLuint plort_position_buffer;

float plort_positions[9] = {
    -0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.5f,-0.5f, 0.0f,
};
