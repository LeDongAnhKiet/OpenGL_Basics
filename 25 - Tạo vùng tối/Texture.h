#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/img.h>
#include "Shader.h"

class HinhAnh
{
public:
	GLuint ID, unit;
	const char* type;
	// hình ảnh có txType tự định nghĩa
	HinhAnh(const char* img, const char* txType, GLuint slot);
	// hình ảnh thường
	HinhAnh(const char* img, const char* txType, GLuint slot, GLenum fm, GLenum pxType);
	// 1 mảng hình ảnh => khối lập phương hình ảnh
	HinhAnh(const char* img[]);
	
// khởi tạo khung ảnh, hình ảnh có khung
	// khung thường
	HinhAnh(int rong, int cao);
	// khung khử răng cưa
	HinhAnh(int rong, int cao, GLuint mau, const GLenum);
	// khung có vùng tối
	HinhAnh(int rong, int cao, const GLenum txType);

	void texUnit(Shader& shader, const char* unif, GLuint unit);
	void Bind();
	void Bind(int unit);
	void Unbind();
	void Bind3D();
	void Unbind3D();
	void Xoa();
};

#endif