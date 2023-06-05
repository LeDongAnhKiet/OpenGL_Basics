#include "FrameBufferObject.h"

FBO::FBO()
{
	glGenFramebuffers(1, &ID);
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void FBO::Bind() { glBindFramebuffer(GL_FRAMEBUFFER, ID); }

void FBO::Bind(FBO &fbo, int rong, int cao)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo.ID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO::ID);
	glBlitFramebuffer(0, 0, rong, cao, 0, 0, rong, cao, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}
void FBO::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void FBO::Xoa() { glDeleteFramebuffers(1, &ID); }

RBO::RBO(int rong, int cao)
{
	glGenRenderbuffers(1, &ID);
	glBindRenderbuffer(GL_RENDERBUFFER, ID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, rong, cao);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ID);
}

RBO::RBO(int rong, int cao, GLuint mau)
{
	glGenRenderbuffers(1, &ID);
	glBindRenderbuffer(GL_RENDERBUFFER, ID);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, mau, GL_DEPTH24_STENCIL8, rong, cao);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ID);
}

void RBO::Bind() { glBindRenderbuffer(GL_RENDERBUFFER, ID); }

void RBO::Unbind() { glBindRenderbuffer(GL_RENDERBUFFER, 0); }

void RBO::Xoa() { glDeleteRenderbuffers(1, &ID); }