#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <json/json.h>
#include "Mesh.h"

using json = nlohmann::json;


class MoHinh
{
public:
	// chạy 1 mô hình từ 1 file, chuyển dữ liệu thành data, json, file khác
	MoHinh(const char* file);
	void Ve(Shader& shader, GocNhin& gocNhin,
		glm::vec3 dichchuyen = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat xoay = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 kichthuoc = glm::vec3(1.0f, 1.0f, 1.0f));

private:
	// biến công khai để dễ truy cập
	const char* file;
	std::vector<unsigned char> data;
	json Json;
	// tránh 1 hình ảnh chạy 2 lần
	std::vector<std::string> tenAnh;
	std::vector<HinhAnh> hinhAnh;

	// mạng lưới và các kiểu biến đổi
	std::vector<Luoi> mangLuoi;
	std::vector<glm::vec3> dichChuyen, kichThuoc;
	std::vector<glm::quat> vongXoay;
	std::vector<glm::mat4> maTran;

	// chạy 1 lưới = chỉ số
	void taiLuoi(unsigned int mluoi);
	// đi qua một nút theo cách đệ quy để đi qua hết tất cả các node kết nối nhau
	void nodeQua(unsigned int next, glm::mat4 matran = glm::mat4(1.0f));

	// lấy dữ liệu nhị phân từ 1 file
	std::vector<unsigned char> getData();
	// chuyển đổi dữ liệu đó thành các giá trị float, thứ tự điểm và hình ảnh
	std::vector<float> getFloat(json truycap);
	std::vector<GLuint> getThuTu(json truycap);
	std::vector<HinhAnh> getHinhAnh();

	// tập hợp lại các điểm thành các nhóm float
	std::vector<glm::vec2> nhomVec2(std::vector<float> diem);
	std::vector<glm::vec3> nhomVec3(std::vector<float> diem);
	std::vector<glm::vec4> nhomVec4(std::vector<float> diem);
	// tập hợp các giá trị float thành điểm
	std::vector<ToaDo> tapHop(std::vector<glm::vec3> vt,
		std::vector<glm::vec3> thg, std::vector<glm::vec2> tuv);
};
#endif