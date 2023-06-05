#include "Texture.h"

HinhAnh::HinhAnh(const char* img, const char* txType, GLuint slot)
{
	type = txType;
	int rong, cao, nCol;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(img, &rong, &cao, &nCol, 0);

	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
	// kiểm tra đúng loại màu cho hình ảnh để chạy
	switch (nCol)
	{
	case 4:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rong, cao, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
		break;
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rong, cao, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
		break;
	case 1:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rong, cao, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
		break;
	default:
		throw std::invalid_argument("Loại hình ảnh ko hợp lệ");
		break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

HinhAnh::HinhAnh(int rong, int cao)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, rong, cao, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// tránh tràn ra khỏi cạnh rìa
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ID, 0);
}

HinhAnh::HinhAnh(int rong, int cao, GLuint mau)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, ID);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, mau, GL_RGB, rong, cao, GL_TRUE);

	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// tránh tràn ra khỏi cạnh rìa
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, ID, 0);
}

HinhAnh::HinhAnh(const char* img[])
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (GLuint i = 0; i < 6; i++)
	{
		int rong, cao, nChannel;
		unsigned char* data = stbi_load(img[i], &rong, &cao, &nChannel, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
				rong, cao, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		} else std::cout << "Tải ko thành công hình " << img[i] << "\n";
		stbi_image_free(data);
	}
}

void HinhAnh::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint txUni = glGetUniformLocation(shader.ID, uniform);
	shader.KichHoat();
	glUniform1i(txUni, unit);
}

void HinhAnh::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void HinhAnh::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

void HinhAnh::Bind3D()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void HinhAnh::Unbind3D() { glBindTexture(GL_TEXTURE_CUBE_MAP, 0); }

void HinhAnh::Xoa() { glDeleteTextures(1, &ID); }

void FBO::KtLoi()
{
	auto stat = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (stat != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Loi FrameBuffer: " << stat << "\n";
}