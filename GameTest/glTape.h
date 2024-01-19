#ifndef GL_TAPE_H
#define GL_TAPE_H

#include <GL/gl.h>

// Geometry shader input types (extension GL_EXT_geometry_shader4)
#define GL_GEOMETRY_INPUT_TYPE_EXT           0x8DDB
#define GL_GEOMETRY_OUTPUT_TYPE_EXT          0x8DDC

// Other constants related to geometry shaders
#define GL_GEOMETRY_VERTICES_OUT_EXT         0x8DDA

// Standard OpenGL constants for shader compilation/linking
#define GL_LINK_STATUS                       0x8B82
#define GL_INFO_LOG_LENGTH                   0x8B84
#define GL_COMPILE_STATUS                    0x8B81

// Shader types (ARB_shader_objects extension)
#define GL_VERTEX_SHADER_ARB                 0x8B31
#define GL_FRAGMENT_SHADER_ARB               0x8B30

// Geometry shader type (EXT_geometry_shader4 extension)
#define GL_GEOMETRY_SHADER_EXT               0x8DD9

// Buffer-related constants
#define GL_ARRAY_BUFFER                 0x8892
#define GL_STATIC_DRAW                  0x88E4
#define GL_ELEMENT_ARRAY_BUFFER         0x8893

typedef char GLcharARB;
typedef char GLchar;
typedef unsigned int GLenum;
typedef unsigned int GLhandleARB;
typedef ptrdiff_t GLsizeiptr;

typedef GLuint(*PFNGLCREATEPROGRAMPROC) (void);
typedef void (*PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (*PFNGLDELETESHADERPROC) (GLuint shader);
typedef void (*PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (*PFNGLPROGRAMPARAMETERIEXTPROC) (GLuint program, GLenum pname, GLint value);
typedef void (*PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (*PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint* params);
typedef void (*PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
typedef void (*PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (*PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
typedef void (*PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
typedef void (*PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (*PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (*PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void (*PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
typedef void (*PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
typedef void (*PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (*PFNGLUNIFORM1UIEXTPROC) (GLint location, GLuint v0);
typedef void (*PFNGLUNIFORM2UIEXTPROC) (GLint location, GLuint v0, GLuint v1);
typedef void (*PFNGLUNIFORM3UIEXTPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (*PFNGLUNIFORM4UIEXTPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (*PFNGLUNIFORM1FVPROC) (GLint location, GLsizei count, const GLfloat* value);
typedef void (*PFNGLUNIFORM2FVPROC) (GLint location, GLsizei count, const GLfloat* value);
typedef void (*PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat* value);
typedef void (*PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat* value);
typedef void (*PFNGLUNIFORM1IVPROC) (GLint location, GLsizei count, const GLint* value);
typedef void (*PFNGLUNIFORM2IVPROC) (GLint location, GLsizei count, const GLint* value);
typedef void (*PFNGLUNIFORM3IVPROC) (GLint location, GLsizei count, const GLint* value);
typedef void (*PFNGLUNIFORM4IVPROC) (GLint location, GLsizei count, const GLint* value);
typedef void (*PFNGLUNIFORM1UIVEXTPROC) (GLint location, GLsizei count, const GLuint* value);
typedef void (*PFNGLUNIFORM2UIVEXTPROC) (GLint location, GLsizei count, const GLuint* value);
typedef void (*PFNGLUNIFORM3UIVEXTPROC) (GLint location, GLsizei count, const GLuint* value);
typedef void (*PFNGLUNIFORM4UIVEXTPROC) (GLint location, GLsizei count, const GLuint* value);
typedef void (*PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (*PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (*PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef GLint(*PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar* name);
typedef void (*PFNGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat* params);
typedef void (*PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint* params);
typedef void (*PFNGLGETUNIFORMUIVEXTPROC) (GLuint program, GLint location, GLuint* params);
typedef void (*PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const GLchar* name);
typedef void (*PFNGLVERTEXATTRIB1FPROC) (GLuint index, GLfloat x);
typedef void (*PFNGLVERTEXATTRIB2FPROC) (GLuint index, GLfloat x, GLfloat y);
typedef void (*PFNGLVERTEXATTRIB3FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (*PFNGLVERTEXATTRIB4FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (*PFNGLVERTEXATTRIB1DPROC) (GLuint index, GLdouble x);
typedef void (*PFNGLVERTEXATTRIB2DPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (*PFNGLVERTEXATTRIB3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (*PFNGLVERTEXATTRIB4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (*PFNGLVERTEXATTRIB1SPROC) (GLuint index, GLshort x);
typedef void (*PFNGLVERTEXATTRIB2SPROC) (GLuint index, GLshort x, GLshort y);
typedef void (*PFNGLVERTEXATTRIB3SPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (*PFNGLVERTEXATTRIB4SPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (*PFNGLVERTEXATTRIB4NUBPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (*PFNGLVERTEXATTRIBI1IEXTPROC) (GLuint index, GLint x);
typedef void (*PFNGLVERTEXATTRIBI2IEXTPROC) (GLuint index, GLint x, GLint y);
typedef void (*PFNGLVERTEXATTRIBI3IEXTPROC) (GLuint index, GLint x, GLint y, GLint z);
typedef void (*PFNGLVERTEXATTRIBI4IEXTPROC) (GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (*PFNGLVERTEXATTRIBI1UIEXTPROC) (GLuint index, GLuint x);
typedef void (*PFNGLVERTEXATTRIBI2UIEXTPROC) (GLuint index, GLuint x, GLuint y);
typedef void (*PFNGLVERTEXATTRIBI3UIEXTPROC) (GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (*PFNGLVERTEXATTRIBI4UIEXTPROC) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (*PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint* param);
typedef void (*PFNGLDELETEOBJECTARBPROC) (GLhandleARB obj);
typedef void (*PFNGLGETINFOLOGARBPROC) (GLhandleARB obj, GLsizei maxLength, GLsizei* length, GLcharARB* infoLog);
typedef void (*PFNGLSHADERSOURCEARBPROC) (GLhandleARB shaderObj, GLsizei count, const GLcharARB** string, const GLint* length);
typedef void (*PFNGLCOMPILESHADERARBPROC) (GLhandleARB shaderObj);
typedef void (*PFNGLGETOBJECTPARAMETERIVARBPROC) (GLhandleARB obj, GLenum pname, GLint* params);
typedef GLint(*PFNGLGETATTRIBLOCATIONARBPROC) (GLhandleARB programObj, const GLcharARB* name);
typedef GLhandleARB(*PFNGLCREATESHADEROBJECTARBPROC) (GLenum shaderType);

// Non glsad
typedef void (*PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint* arrays);
typedef void (*PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (*PFNGLGENBUFFERSPROC) (GLsizei n, GLuint* buffers);
typedef void (*PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (*PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (*PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void (*PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);

// Declare the global function pointers
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLPROGRAMPARAMETERIEXTPROC glProgramParameteriEXT;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLUNIFORM2FPROC glUniform2f;
extern PFNGLUNIFORM3FPROC glUniform3f;
extern PFNGLUNIFORM4FPROC glUniform4f;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM2IPROC glUniform2i;
extern PFNGLUNIFORM3IPROC glUniform3i;
extern PFNGLUNIFORM4IPROC glUniform4i;
extern PFNGLUNIFORM1UIEXTPROC glUniform1uiEXT;
extern PFNGLUNIFORM2UIEXTPROC glUniform2uiEXT;
extern PFNGLUNIFORM3UIEXTPROC glUniform3uiEXT;
extern PFNGLUNIFORM4UIEXTPROC glUniform4uiEXT;
extern PFNGLUNIFORM1FVPROC glUniform1fv;
extern PFNGLUNIFORM2FVPROC glUniform2fv;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLUNIFORM1IVPROC glUniform1iv;
extern PFNGLUNIFORM2IVPROC glUniform2iv;
extern PFNGLUNIFORM3IVPROC glUniform3iv;
extern PFNGLUNIFORM4IVPROC glUniform4iv;
extern PFNGLUNIFORM1UIVEXTPROC glUniform1uivEXT;
extern PFNGLUNIFORM2UIVEXTPROC glUniform2uivEXT;
extern PFNGLUNIFORM3UIVEXTPROC glUniform3uivEXT;
extern PFNGLUNIFORM4UIVEXTPROC glUniform4uivEXT;
extern PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLGETUNIFORMFVPROC glGetUniformfv;
extern PFNGLGETUNIFORMIVPROC glGetUniformiv;
extern PFNGLGETUNIFORMUIVEXTPROC glGetUniformuivEXT;
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
extern PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
extern PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;
extern PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;
extern PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;
extern PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d;
extern PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d;
extern PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d;
extern PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d;
extern PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s;
extern PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s;
extern PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s;
extern PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s;
extern PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub;
extern PFNGLVERTEXATTRIBI1IEXTPROC glVertexAttribI1iEXT;
extern PFNGLVERTEXATTRIBI2IEXTPROC glVertexAttribI2iEXT;
extern PFNGLVERTEXATTRIBI3IEXTPROC glVertexAttribI3iEXT;
extern PFNGLVERTEXATTRIBI4IEXTPROC glVertexAttribI4iEXT;
extern PFNGLVERTEXATTRIBI1UIEXTPROC glVertexAttribI1uiEXT;
extern PFNGLVERTEXATTRIBI2UIEXTPROC glVertexAttribI2uiEXT;
extern PFNGLVERTEXATTRIBI3UIEXTPROC glVertexAttribI3uiEXT;
extern PFNGLVERTEXATTRIBI4UIEXTPROC glVertexAttribI4uiEXT;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
extern PFNGLGETINFOLOGARBPROC glGetInfoLogARB;
extern PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
extern PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
extern PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
extern PFNGLGETATTRIBLOCATIONARBPROC glGetAttribLocationARB;
extern PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;

// Non glsad
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

void LoadOpenGLFunctions(); // Function to load all the defined OpenGL functions

#endif // GL_TAPE_H
