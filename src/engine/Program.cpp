#include "Program.h"

#include <cstdlib>
#include <iostream>
#include <string>

Program::Program(const char* vs_source, const char* fs_source) {
  GLint program_ok;
  GLuint vertex_shader = 0u;
  GLuint fragment_shader = 0u;
  GLsizei log_length;
  char info_log[8192];

  vertex_shader = createShader(GL_VERTEX_SHADER, vs_source);
  if (vertex_shader != 0u) {
    fragment_shader = createShader(GL_FRAGMENT_SHADER, fs_source);
    if (fragment_shader != 0u) {
      ID = glCreateProgram();
      if (ID != 0u) {
        glAttachShader(ID, vertex_shader);
        glAttachShader(ID, fragment_shader);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &program_ok);

        if (program_ok != GL_TRUE) {
          glGetProgramInfoLog(ID, 8192, &log_length, info_log);
          std::cerr << info_log << std::endl;
          glDeleteProgram(ID);
          glDeleteShader(fragment_shader);
          glDeleteShader(vertex_shader);
          throw "Failed to link shader program\n";
        }
      }
    }
    else {
      glDeleteShader(vertex_shader);
      throw "Unable to load fragment shader\n";
    }
  }
  else throw "Unable to load vertex shader\n";
}

Program::~Program() {
  glDeleteProgram(ID);

}

GLuint Program::createShader(GLenum type, const char* text) {
  GLuint shader;
  GLint shader_ok;
  GLsizei log_length;
  char info_log[8192];

  shader = glCreateShader(type);
  if (shader != 0) {
    glShaderSource(shader, 1, (const GLchar**)&text, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (shader_ok != GL_TRUE) {
      glGetShaderInfoLog(shader, 8192, &log_length,info_log);
      fprintf(stderr, "ERROR: \n%s\n\n", info_log);
      glDeleteShader(shader);
      shader = 0;
      throw "ERROR: Failed to compile shader type " + std::to_string(type);
    }
  }
  return shader;
}

void Program::link() {
  glLinkProgram(ID);
}

void Program::use() {
  glUseProgram(ID);
}

void Program::unlink() {
  glLinkProgram(0);
}

void Program::unuse() {
  glUseProgram(0);
}

void Program::newUniform(const char* name)  const{
  glGetUniformLocation(ID, name);
}

void Program::newUniform(const char* name, GLuint& u) const {
  u = glGetUniformLocation(ID, name);
}

void Program::setMat4f(GLuint id, const GLfloat* ptr) const {
  glUniformMatrix4fv(id, 1, GL_FALSE, ptr);
}

void Program::setMat4f(const char* id, const GLfloat* ptr) const {
  glUniformMatrix4fv(glGetUniformLocation(ID, id), 1, GL_FALSE, ptr);
}

void Program::setVec2f(GLuint id, const GLfloat* ptr) const {
  glUniform2fv(id, 1, ptr);
}

void Program::setVec2f(const char* id, const GLfloat* ptr) const {
  glUniform2fv(glGetUniformLocation(ID, id), 1, ptr);
}

void Program::setVec3f(GLuint id, const GLfloat* ptr) const {
  glUniform3fv(id, 1, ptr);
}

void Program::setVec3f(const char* id, const GLfloat* ptr) const {
  glUniform3fv(glGetUniformLocation(ID, id), 1, ptr);
}

void Program::setVec4f(GLuint id, const GLfloat* ptr) const {
  glUniform4fv(id, 1, ptr);
}

void Program::setVec4f(const char* id, const GLfloat* ptr) const {
  glUniform4fv(glGetUniformLocation(ID, id), 1, ptr);
}

void Program::setInt(GLuint id, int num) const {
  glUniform1i(id, num);
}

void Program::setInt(const char* id, int num) const {
  glUniform1i(glGetUniformLocation(ID, id), num);
}

void Program::setFloat(GLuint id, float num) const {
  glUniform1f(id, num);
}

void Program::setFloat(const char* id, float num) const {
  glUniform1f(glGetUniformLocation(ID, id), num);
}