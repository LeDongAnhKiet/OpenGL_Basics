#include "Texture.h"

Texture::Texture(const char* img, GLenum txType, GLenum slot, GLenum fm, GLenum pxType)
{
	// gán loại ảnh cho đối tượng texture
	type = txType;

	// lấy độ dài, độ rộng, chỉ số loại màu của ảnh
	int widImg, hegImg, nColCh;
	// lật ảnh từ dưới lên
	stbi_set_flip_vertically_on_load(true);
	// đọc dữ liệu ảnh
	unsigned char* bytes = stbi_load(img, &widImg, &hegImg, &nColCh, 0);

	// khởi tạo đối tượng Texture
	glGenTextures(1, &ID);
	// gán texture vào đơn vị ảnh
	glActiveTexture(slot);
	glBindTexture(txType, ID);

	// cấu hình lại loại giải thuật dùng cho hình ảnh
	glTexParameteri(txType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(txType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// cấu hình cách lặp của hình (nếu đc)
	glTexParameteri(txType, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(txType, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	/*		// Nếu dù GL_CLAMP_TO_BORDER
	float fClr[] = { 1.0f, 1.0f, 1.0f, 1.0f; }
	glTexParameterfv (txType, GL_TEXTURE_BORDER_COLOR, fClr);	*/

	// gán ảnh vào đối tượng OpenGL Texture
	glTexImage2D(txType, 0, GL_RGBA, widImg, hegImg, 0, fm, pxType, bytes);
	// tạo MipMaps
	glGenerateMipmap(txType);

	// xóa ảnh vì OpenGL Texture đã lưu đc
	stbi_image_free(bytes);

	// ngắt nối để ko xảy ra lỗi ngoài ý muốn
	glBindTexture(txType, 0);
}

void Texture::texUnit(Shader& shader, const char* uni, GLuint unit)
{
	// Lấy vị trí của uniform
	GLuint txUni = glGetUniformLocation(shader.ID, uni);
	// kích hoạt Shader TRƯỚC khi đổi giá trị uniform
	shader.Activate();
	// Gán giá trị vào uniform
	glUniform1i(txUni, unit);
}

void Texture::Bind() { glBindTexture(type, ID); }

void Texture::Unbind() { glBindTexture(type, 0); }

void Texture::Delete() { glDeleteTextures(1, &ID); }
