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

void HinhAnh::Xoa() { glDeleteTextures(1, &ID); }