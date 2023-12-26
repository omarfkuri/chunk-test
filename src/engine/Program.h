#ifndef PROGRAM_CLASS_H
#define PROGRAM_CLASS_H

#include <GL/glew.h>

class Program {

public:
	Program(const char*, const char*);
	~Program();
	
	GLuint ID;

	void use();
	void unuse();

	void link();
	void unlink();
	
	void newUniform(const char*) const;
	void newUniform(const char*, GLuint&) const;

	void setMat4f(GLuint, const GLfloat*) const;
	void setMat4f(const char*, const GLfloat*) const;
	void setVec2f(GLuint, const GLfloat*) const;
	void setVec2f(const char*, const GLfloat*) const;
	void setVec3f(GLuint, const GLfloat*) const;
	void setVec3f(const char*, const GLfloat*) const;
	void setVec4f(GLuint, const GLfloat*) const;
	void setVec4f(const char*, const GLfloat*) const;
	void setInt(GLuint, int) const;
	void setInt(const char*, int) const;
	void setFloat(GLuint, float) const;
	void setFloat(const char*, float) const;
	
private:
	static GLuint createShader(GLenum type, const char* text);

};

#endif