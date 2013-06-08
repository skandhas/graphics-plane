#include "plotter.h"
#include "gl_program.h"

gl_program_t *
gl_program_open(const char * vsrc, const char *fsrc)
{
  int i;  
  GLuint shaders[2];  
  GLchar *srcs[2] ={(GLchar *)vsrc, (GLchar *)fsrc};
  gl_program_t *program;

  assert(vsrc && fsrc);

  program = calloc(1, sizeof(gl_program_t));
  program->id = glCreateProgram();
  program->v_shader = glCreateShader(GL_VERTEX_SHADER);
  program->f_shader = glCreateShader(GL_FRAGMENT_SHADER);
 
  shaders[0] =  program->v_shader;
  shaders[1] =  program->f_shader;
   
  for (i = 0; i < sizeof(shaders); i++) {
    GLint result;
    GLuint shader = shaders[i];

    glShaderSource(shader, 1, &srcs[i], NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS,&result);

    assert(result == GL_TRUE);
    if (result != GL_TRUE) {
      /* Log ...*/
    }
    glAttachShader(program->id, shader);
  }

  return program;
}

int
gl_program_link(gl_program_t * program)
{
  GLint result;

  glLinkProgram(program->id);
  glGetProgramiv(program->id, GL_LINK_STATUS,&result);

  assert(result == GL_TRUE);
  if (result != GL_TRUE) {
    /* Log ...*/
  }

  if (program->v_shader) {
    glDeleteShader(program->v_shader);
    program->v_shader = 0;
  }

  if (program->f_shader) {
    glDeleteShader(program->f_shader);
    program->f_shader = 0;
  }
  
  return result == GL_TRUE ? TRUE : FALSE;
}

void
gl_program_use(gl_program_t * program)
{
  glUseProgram(program->id); 
}

void
gl_shader_close(gl_program_t * program)
{
  if (program) {
    glDeleteProgram(program->id); 
    free(program);
  }
}


