#include "Texture.h"

Texture::Texture(const char* img, GLenum txType, GLenum slot, GLenum fm, GLenum pxType)
{
	// gán loại ảnh cho đối tượng texture
	type = txType;
	// lấy độ dài, độ rộng, chỉ số loại màu của ảnh
	int widImg, hgtImg, nColCh;
	// lật ảnh từ dưới lên
	stbi_set_flip_vertically_on_load(true);
	// đọc dữ liệu ảnh
	unsigned char* byte = stbi_load(img, &widImg, &hgtImg, &nColCh, 0);

	// khởi tạo đối tượng Texture
	glGenTextures(1, &ID);
	// gán texture vào đơn vị ảnh
	glActiveTexture(slot);
	glBindTexture(txType, ID);

	// cấu hình lại loại giải thuật dùng cho hình ảnh
	glTexParameteri(txType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(txType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// cấu hình cách lặp của hình (nếu đc)
	glTexParameteri(txType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(txType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/*		// Nếu dù GL_CLAMP_TO_BORDER
	float fClr[] = { 1.0f, 1.0f, 1.0f, 1.0f; }
	glTexParameterfv (txType, GL_TEXTURE_BORDER_COLOR, fClr);	*/

	// gán ảnh vào đối tượng OpenGL Texture
	glTexImage2D(txType, 0, GL_RGBA, widImg, hgtImg, 0, fm, pxType, byte);
	// tạo MipMaps
	glGenerateMipmap(txType);
	// xóa ảnh vì OpenGL Texture đã lưu đc
	stbi_image_free(byte);
	// ngắt nối để ko xảy ra lỗi ngoài ý muốn
	glBindTexture(txType, 0);
}

void Texture::txUnit(Shader shade, const char* uni, GLuint unit)
{
	GLuint txUni = glGetUniformLocation(shade.ID, uni);
	// kích hoạt Shader TRƯỚC khi đổi giá trị uniform
	shade.Activate();
	glUniform1i(txUni, unit);
}
void Texture::Bind() { glBindTexture(type, ID); }

void Texture::Unbind() { glBindTexture(type, 0); }

void Texture::Delete() { glDeleteTextures(1, &ID); }