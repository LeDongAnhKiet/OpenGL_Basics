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
	
	if (type == "chuan")
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, rong, cao, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	else if (type == "saiVt")
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, rong, cao, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	else switch (nCol)
	{
		case 1:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, rong, cao, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
		break;
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, rong, cao, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
		break;
	case 4:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, rong, cao, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
		break;
	default:
		throw std::invalid_argument("Loại hình ảnh ko hợp lệ");
		break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

HinhAnh::HinhAnh(const char* img, const char* txType, GLuint slot, GLenum fm, GLenum pxType)
{
	type = txType;
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(img, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, fm, pxType, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
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
		}
		else std::cout << "Tải ko thành công hình " << img[i] << "\n";
		stbi_image_free(data);
	}
	type = (char*)GL_TEXTURE_2D; unit = ID;
}

HinhAnh::HinhAnh(int rong, int cao)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, rong, cao, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	type = (char*)GL_TEXTURE_2D, unit = NULL;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ID, 0);
}

HinhAnh::HinhAnh(int rong, int cao, GLuint mau, const GLenum txType)
{
	glGenTextures(1, &ID);
	glBindTexture(txType, ID);
	glTexImage2DMultisample(txType, mau, GL_RGB16F, rong, cao, GL_TRUE);
	unit = mau, type = (char*)txType;

	glTexParameteri(txType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(txType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(txType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(txType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, txType, ID, 0);
}

HinhAnh::HinhAnh(int rong, int cao, const GLenum txType)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, txType, rong, cao, 0, txType, GL_FLOAT, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	
	float mauSac[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, mauSac);
	type = (char*)GL_TEXTURE_2D, unit = NULL;
}

HinhAnh::HinhAnh(const int canh, GLenum type1, GLenum type2)
{
	glGenTextures(1, &ID);
	glBindTexture(type1, ID);
	for (GLuint i = 0; i < 6; i++)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, type2, canh, canh, 0, type2, GL_FLOAT, NULL);
	
	glTexParameteri(type1, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(type1, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(type1, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(type1, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(type1, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	type = (char*)type1, unit = NULL;
}

void HinhAnh::texUnit(Shader& shader, const char* unif, GLuint unit)
{
	GLuint txUni = glGetUniformLocation(shader.ID, unif);
	shader.KichHoat();
	glUniform1i(txUni, unit);
}

void HinhAnh::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void HinhAnh::Bind(int unit, GLenum txType)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(txType, ID);
}

void HinhAnh::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

void HinhAnh::Bind3D()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void HinhAnh::Unbind3D() { glBindTexture(GL_TEXTURE_CUBE_MAP, 0); }

void HinhAnh::Xoa() { glDeleteTextures(1, &ID); }