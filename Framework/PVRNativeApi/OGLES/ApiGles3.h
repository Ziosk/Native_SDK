/*!
\brief Contains function pointer declarations for all OpenGL ES 3 functions (minus ES 2 functions).
\file PVRNativeApi/OGLES/ApiGles3.h
\author PowerVR by Imagination, Developer Technology Team
\copyright Copyright (c) Imagination Technologies Limited.
*/
//!\cond NO_DOXYGEN

#pragma once
#include "PVRNativeApi/OGLES/ApiGles2.h"

typedef void (PVR_APIENTRY* PROC_ES3_glReadBuffer)(GLenum src);
typedef void (PVR_APIENTRY* PROC_ES3_glDrawRangeElements)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices);
typedef void (PVR_APIENTRY* PROC_ES3_glTexImage3D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels);
typedef void (PVR_APIENTRY* PROC_ES3_glTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);
typedef void (PVR_APIENTRY* PROC_ES3_glCopyTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (PVR_APIENTRY* PROC_ES3_glCompressedTexImage3D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data);
typedef void (PVR_APIENTRY* PROC_ES3_glCompressedTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data);
typedef void (PVR_APIENTRY* PROC_ES3_glGenQueries)(GLsizei n, GLuint* ids);
typedef void (PVR_APIENTRY* PROC_ES3_glDeleteQueries)(GLsizei n, const GLuint* ids);
typedef GLboolean(PVR_APIENTRY* PROC_ES3_glIsQuery)(GLuint id);
typedef void (PVR_APIENTRY* PROC_ES3_glBeginQuery)(GLenum target, GLuint id);
typedef void (PVR_APIENTRY* PROC_ES3_glEndQuery)(GLenum target);
typedef void (PVR_APIENTRY* PROC_ES3_glGetQueryiv)(GLenum target, GLenum pname, GLint* params);
typedef void (PVR_APIENTRY* PROC_ES3_glGetQueryObjectuiv)(GLuint id, GLenum pname, GLuint* params);
typedef GLboolean(PVR_APIENTRY* PROC_ES3_glUnmapBuffer)(GLenum target);
typedef void (PVR_APIENTRY* PROC_ES3_glGetBufferPointerv)(GLenum target, GLenum pname, void** params);
typedef void (PVR_APIENTRY* PROC_ES3_glDrawBuffers)(GLsizei n, const GLenum* bufs);
typedef void (PVR_APIENTRY* PROC_ES3_glUniformMatrix2x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (PVR_APIENTRY* PROC_ES3_glUniformMatrix3x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (PVR_APIENTRY* PROC_ES3_glUniformMatrix2x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (PVR_APIENTRY* PROC_ES3_glUniformMatrix4x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (PVR_APIENTRY* PROC_ES3_glUniformMatrix3x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (PVR_APIENTRY* PROC_ES3_glUniformMatrix4x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (PVR_APIENTRY* PROC_ES3_glBlitFramebuffer)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (PVR_APIENTRY* PROC_ES3_glRenderbufferStorageMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (PVR_APIENTRY* PROC_ES3_glFramebufferTextureLayer)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void* (PVR_APIENTRY* PROC_ES3_glMapBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (PVR_APIENTRY* PROC_ES3_glFlushMappedBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (PVR_APIENTRY* PROC_ES3_glBindVertexArray)(GLuint array);
typedef void (PVR_APIENTRY* PROC_ES3_glDeleteVertexArrays)(GLsizei n, const GLuint* arrays);
typedef void (PVR_APIENTRY* PROC_ES3_glGenVertexArrays)(GLsizei n, GLuint* arrays);
typedef GLboolean(PVR_APIENTRY* PROC_ES3_glIsVertexArray)(GLuint array);
typedef void (PVR_APIENTRY* PROC_ES3_glGetIntegeri_v)(GLenum target, GLuint index, GLint* data);
typedef void (PVR_APIENTRY* PROC_ES3_glBeginTransformFeedback)(GLenum primitiveMode);
typedef void (PVR_APIENTRY* PROC_ES3_glEndTransformFeedback)(void);
typedef void (PVR_APIENTRY* PROC_ES3_glBindBufferRange)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (PVR_APIENTRY* PROC_ES3_glBindBufferBase)(GLenum target, GLuint index, GLuint buffer);
typedef void (PVR_APIENTRY* PROC_ES3_glTransformFeedbackVaryings)(GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode);
typedef void (PVR_APIENTRY* PROC_ES3_glGetTransformFeedbackVarying)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name);
typedef void (PVR_APIENTRY* PROC_ES3_glVertexAttribIPointer)(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
typedef void (PVR_APIENTRY* PROC_ES3_glGetVertexAttribIiv)(GLuint index, GLenum pname, GLint* params);
typedef void (PVR_APIENTRY* PROC_ES3_glGetVertexAttribIuiv)(GLuint index, GLenum pname, GLuint* params);
typedef void (PVR_APIENTRY* PROC_ES3_glVertexAttribI4i)(GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (PVR_APIENTRY* PROC_ES3_glVertexAttribI4ui)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (PVR_APIENTRY* PROC_ES3_glVertexAttribI4iv)(GLuint index, const GLint* v);
typedef void (PVR_APIENTRY* PROC_ES3_glVertexAttribI4uiv)(GLuint index, const GLuint* v);
typedef void (PVR_APIENTRY* PROC_ES3_glGetUniformuiv)(GLuint program, GLint location, GLuint* params);
typedef GLint(PVR_APIENTRY* PROC_ES3_glGetFragDataLocation)(GLuint program, const GLchar* name);
typedef void (PVR_APIENTRY* PROC_ES3_glUniform1ui)(GLint location, GLuint v0);
typedef void (PVR_APIENTRY* PROC_ES3_glUniform2ui)(GLint location, GLuint v0, GLuint v1);
typedef void (PVR_APIENTRY* PROC_ES3_glUniform3ui)(GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (PVR_APIENTRY* PROC_ES3_glUniform4ui)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (PVR_APIENTRY* PROC_ES3_glUniform1uiv)(GLint location, GLsizei count, const GLuint* value);
typedef void (PVR_APIENTRY* PROC_ES3_glUniform2uiv)(GLint location, GLsizei count, const GLuint* value);
typedef void (PVR_APIENTRY* PROC_ES3_glUniform3uiv)(GLint location, GLsizei count, const GLuint* value);
typedef void (PVR_APIENTRY* PROC_ES3_glUniform4uiv)(GLint location, GLsizei count, const GLuint* value);
typedef void (PVR_APIENTRY* PROC_ES3_glClearBufferiv)(GLenum buffer, GLint drawbuffer, const GLint* value);
typedef void (PVR_APIENTRY* PROC_ES3_glClearBufferuiv)(GLenum buffer, GLint drawbuffer, const GLuint* value);
typedef void (PVR_APIENTRY* PROC_ES3_glClearBufferfv)(GLenum buffer, GLint drawbuffer, const GLfloat* value);
typedef void (PVR_APIENTRY* PROC_ES3_glClearBufferfi)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef const GLubyte* (PVR_APIENTRY* PROC_ES3_glGetStringi)(GLenum name, GLuint index);
typedef void (PVR_APIENTRY* PROC_ES3_glCopyBufferSubData)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (PVR_APIENTRY* PROC_ES3_glGetUniformIndices)(GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices);
typedef void (PVR_APIENTRY* PROC_ES3_glGetActiveUniformsiv)(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params);
typedef GLuint(PVR_APIENTRY* PROC_ES3_glGetUniformBlockIndex)(GLuint program, const GLchar* uniformBlockName);
typedef void (PVR_APIENTRY* PROC_ES3_glGetActiveUniformBlockiv)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params);
typedef void (PVR_APIENTRY* PROC_ES3_glGetActiveUniformBlockName)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName);
typedef void (PVR_APIENTRY* PROC_ES3_glUniformBlockBinding)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
typedef void (PVR_APIENTRY* PROC_ES3_glDrawArraysInstanced)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
typedef void (PVR_APIENTRY* PROC_ES3_glDrawElementsInstanced)(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount);
typedef GLsync(PVR_APIENTRY* PROC_ES3_glFenceSync)(GLenum condition, GLbitfield flags);
typedef GLboolean(PVR_APIENTRY* PROC_ES3_glIsSync)(GLsync sync);
typedef void (PVR_APIENTRY* PROC_ES3_glDeleteSync)(GLsync sync);
typedef GLenum(PVR_APIENTRY* PROC_ES3_glClientWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (PVR_APIENTRY* PROC_ES3_glWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (PVR_APIENTRY* PROC_ES3_glGetInteger64v)(GLenum pname, GLint64* data);
typedef void (PVR_APIENTRY* PROC_ES3_glGetSynciv)(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values);
typedef void (PVR_APIENTRY* PROC_ES3_glGetInteger64i_v)(GLenum target, GLuint index, GLint64* data);
typedef void (PVR_APIENTRY* PROC_ES3_glGetBufferParameteri64v)(GLenum target, GLenum pname, GLint64* params);
typedef void (PVR_APIENTRY* PROC_ES3_glGenSamplers)(GLsizei count, GLuint* samplers);
typedef void (PVR_APIENTRY* PROC_ES3_glDeleteSamplers)(GLsizei count, const GLuint* samplers);
typedef GLboolean(PVR_APIENTRY* PROC_ES3_glIsSampler)(GLuint sampler);
typedef void (PVR_APIENTRY* PROC_ES3_glBindSampler)(GLuint unit, GLuint sampler);
typedef void (PVR_APIENTRY* PROC_ES3_glSamplerParameteri)(GLuint sampler, GLenum pname, GLint param);
typedef void (PVR_APIENTRY* PROC_ES3_glSamplerParameteriv)(GLuint sampler, GLenum pname, const GLint* param);
typedef void (PVR_APIENTRY* PROC_ES3_glSamplerParameterf)(GLuint sampler, GLenum pname, GLfloat param);
typedef void (PVR_APIENTRY* PROC_ES3_glSamplerParameterfv)(GLuint sampler, GLenum pname, const GLfloat* param);
typedef void (PVR_APIENTRY* PROC_ES3_glGetSamplerParameteriv)(GLuint sampler, GLenum pname, GLint* params);
typedef void (PVR_APIENTRY* PROC_ES3_glGetSamplerParameterfv)(GLuint sampler, GLenum pname, GLfloat* params);
typedef void (PVR_APIENTRY* PROC_ES3_glVertexAttribDivisor)(GLuint index, GLuint divisor);
typedef void (PVR_APIENTRY* PROC_ES3_glBindTransformFeedback)(GLenum target, GLuint id);
typedef void (PVR_APIENTRY* PROC_ES3_glDeleteTransformFeedbacks)(GLsizei n, const GLuint* ids);
typedef void (PVR_APIENTRY* PROC_ES3_glGenTransformFeedbacks)(GLsizei n, GLuint* ids);
typedef GLboolean(PVR_APIENTRY* PROC_ES3_glIsTransformFeedback)(GLuint id);
typedef void (PVR_APIENTRY* PROC_ES3_glPauseTransformFeedback)(void);
typedef void (PVR_APIENTRY* PROC_ES3_glResumeTransformFeedback)(void);
typedef void (PVR_APIENTRY* PROC_ES3_glGetProgramBinary)(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary);
typedef void (PVR_APIENTRY* PROC_ES3_glProgramBinary)(GLuint program, GLenum binaryFormat, const void* binary, GLsizei length);
typedef void (PVR_APIENTRY* PROC_ES3_glProgramParameteri)(GLuint program, GLenum pname, GLint value);
typedef void (PVR_APIENTRY* PROC_ES3_glInvalidateFramebuffer)(GLenum target, GLsizei numAttachments, const GLenum* attachments);
typedef void (PVR_APIENTRY* PROC_ES3_glInvalidateSubFramebuffer)(GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (PVR_APIENTRY* PROC_ES3_glTexStorage2D)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (PVR_APIENTRY* PROC_ES3_glTexStorage3D)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (PVR_APIENTRY* PROC_ES3_glGetInternalformativ)(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params);
//!\endcond