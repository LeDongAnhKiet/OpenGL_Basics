#include "Model.h"
using namespace std;

MoHinh::MoHinh(const char* f, GLuint nhanban, std::vector<glm::mat4> matran)
{
	// tạo đối tượng json
	string text = get_content(f);
	Json = json::parse(text);
	// lấy dữ liệu nhị phân
	file = f;
	data = getData();

	nhanBan = nhanban;
	maTranBan = matran;
	// đi qua tất cả các node
	nodeQua(0);
}

void MoHinh::Ve(Shader& shader, GocNhin& gocNhin, glm::vec3 dichchuyen, glm::quat xoay, glm::vec3 kichthuoc)
{
	// vẽ từng các lưới
	for (GLuint i = 0; i < mangLuoi.size(); i++)
		mangLuoi[i].Ve(shader, gocNhin, maTranLuoi[i], dichchuyen, xoay, kichthuoc);
}

vector<unsigned char> MoHinh::getData()
{
	// xác định địa chỉ tài nguyên (URI) trong file .bin
	string byte, uri = Json["buffers"][0]["uri"], taiLieu = string(file),
	// chuyển string thành byte
		thuMuc = taiLieu.substr(0, taiLieu.find_last_of('/') + 1);
	byte = get_content((thuMuc + uri).c_str());
	// chuyển byte thành véctơ
	vector<unsigned char> data(byte.begin(), byte.end());
	return data;
}

vector<float> MoHinh::getFloat(json accessor)
{
	vector<float> diem;
	// lấy thuộc tính truy cập
	GLuint buff = accessor.value("bufferView", 1), 
		dem = accessor["count"], byte = accessor.value("byteOffset", 0);
	string type = accessor["type"];

	// lấy thuộc tính bufferView
	json bView = Json["bufferViews"][buff];
	GLuint bOffset = bView["byteOffset"], n;
	// chuyển đổi loại (type) thành int
	if (type == "SCALAR") n = 1;
	else if (type == "VEC2") n = 2;
	else if (type == "VEC3") n = 3;
	else if (type == "VEC4") n = 4;
	else throw invalid_argument("Ko hợp lệ vì ko phải là Scalar, Vec2, Vec3 hay Vec4");

	// tìm dữ liệu ở đúng vị trí từ các thuộc tính trên
	GLuint batDau = bOffset + byte, len = dem * 4 * n;
	for (GLuint i = batDau; i < batDau + len; i)
	{
		unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
		float gt;
		memcpy(&gt, bytes, sizeof(float));
		diem.push_back(gt);
	}
	return diem;
}

vector<GLuint> MoHinh::getThuTu(json accessor)
{
	vector<GLuint> tt;
	// lấy thuộc tính truy cập
	GLuint buff = accessor.value("bufferView", 0), dem = accessor["count"],
		byte = accessor.value("byteOffset", 0), type = accessor["componentType"];

	// lấy thuộc tính bufferView
	json bView = Json["bufferViews"][buff];
	GLuint bOffset = bView["byteOffset"], batDau = bOffset + byte;
	// lấy đúng kiểu dữ liệu cho type
	switch (type)
	{
	case 5122:
		for (GLuint i = batDau; i < bOffset + byte + dem * 2; i)
		{
			unsigned char bytes[] = { data[i++], data[i++] };
			short gt;
			memcpy(&gt, bytes, sizeof(short));
			tt.push_back((GLuint)gt);
		}
		break;
	case 5123:
		for (GLuint i = batDau; i < bOffset + byte + dem * 2; i)
		{
			unsigned char bytes[] = { data[i++], data[i++] };
			unsigned short gt;
			memcpy(&gt, bytes, sizeof(unsigned short));
			tt.push_back((GLuint)gt);
		}
		break;
	case 5125:
		for (GLuint i = batDau; i < bOffset + byte + dem * 4; i)
		{
			unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
			GLuint gt;
			memcpy(&gt, bytes, sizeof(GLuint));
			tt.push_back((GLuint)gt);
		}
		break;
	}
	return tt;
}

vector<glm::vec2> MoHinh::nhomVec2(vector<float> diem)
{
	vector<glm::vec2> v;
	for (int i = 0; i < diem.size(); i)
		v.push_back(glm::vec2(diem[i++], diem[i++]));
	return v;
}

vector<glm::vec3> MoHinh::nhomVec3(vector<float> diem)
{
	vector<glm::vec3> v;
	for (int i = 0; i < diem.size(); i)
		v.push_back(glm::vec3(diem[i++], diem[i++], diem[i++]));
	return v;
}

vector<glm::vec4> MoHinh::nhomVec4(vector<float> diem)
{
	vector<glm::vec4> v;
	for (int i = 0; i < diem.size(); i)
		v.push_back(glm::vec4(diem[i++], diem[i++], diem[i++], diem[i++]));
	return v;
}

vector<ToaDo> MoHinh::tapHop(vector<glm::vec3> vt, vector<glm::vec3> bt, vector<glm::vec2> tuv)
{
	vector<ToaDo> td;
	for (int i = 0; i < vt.size(); i++)
		td.push_back(ToaDo{ vt[i], bt[i],
			glm::vec3(1.0f, 1.0f, 1.0f), tuv[i] });
	return td;
}

vector<HinhAnh> MoHinh::getHinhAnh()
{
	vector<HinhAnh> hinhanh;
	string taiLieu = string(file),
		thuMuc = taiLieu.substr(0, taiLieu.find_last_of('/') + 1);

	// xét các hình ảnh
	for (GLuint i = 0; i < Json["images"].size(); i++)
	{
		// uri của ảnh
		string anh = Json["images"][i]["uri"];
		// xét nếu hình ảnh đã chạy
		bool b = false;
		for (GLuint j = 0; j < tenAnh.size(); j++)
			if (tenAnh[j] == anh)
			{
				hinhanh.push_back(hinhAnh[j]);
				b = true;
				break;
			}
		// chạy ảnh phân tán
		if (anh.find("baseColor") != std::string::npos || anh.find("diffuse") != std::string::npos && !b)
		{
			HinhAnh phanTan = HinhAnh((thuMuc + anh).c_str(), "phanTan", hinhAnh.size());
			hinhanh.push_back(phanTan);
			hinhAnh.push_back(phanTan);
			tenAnh.push_back(anh);
		}
		// chạy ảnh phản chiếu
		else if (anh.find("metallicRoughness") != std::string::npos || anh.find("specular") != std::string::npos && !b)
		{
			HinhAnh phanChieu = HinhAnh((thuMuc + anh).c_str(), "phanChieu", hinhAnh.size());
			hinhanh.push_back(phanChieu);
			hinhAnh.push_back(phanChieu);
			tenAnh.push_back(anh);
		}
	}

	return hinhanh;
}

void MoHinh::taiLuoi(GLuint mluoi)
{
	// lấy các thứ tự điểm truy cập
	GLuint vitri = Json["meshes"][mluoi]["primitives"][0]["attributes"]["POSITION"],
		bthg = Json["meshes"][mluoi]["primitives"][0]["attributes"]["NORMAL"],
		anh = Json["meshes"][mluoi]["primitives"][0]["attributes"]["TEXCOORD_0"],
		thutu = Json["meshes"][mluoi]["primitives"][0]["indices"];

	// lấy các thành phần tọa độ điểm
	vector<float> vt = getFloat(Json["accessors"][vitri]),
		bt = getFloat(Json["accessors"][bthg]),
		tx = getFloat(Json["accessors"][anh]);
	vector<glm::vec3> v = nhomVec3(vt), b = nhomVec3(bt);
	vector<glm::vec2> t = nhomVec2(tx);

	// kết hợp các thành phần thành các điểm, hình ảnh
	vector<ToaDo> td = tapHop(v, b, t);
	vector<GLuint> tt = getThuTu(Json["accessors"][thutu]);
	vector<HinhAnh> h = getHinhAnh();
	// kếp hợp tọa độ, thứ tự điểm và hình ảnh để tạo 1 mạng lưới
	mangLuoi.push_back(Luoi(td, tt, h, nhanBan, maTranBan));
}

void MoHinh::nodeQua(GLuint next, glm::mat4 matran)
{
	// Node hiện tại
	json node = Json["nodes"][next];
	// dịch chuyển nếu có
	glm::vec3 dichchuyen = glm::vec3(0.0f, 0.0f, 0.0f);
	if (node.find("translation") != node.end())
	{
		float giatri[3];
		for (GLuint i = 0; i < node["translation"].size(); i++)
			giatri[i] = (node["translation"][i]);
		dichchuyen = glm::make_vec3(giatri);
	}
	// xoay nếu có
	glm::quat xoay = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	if (node.find("rotation") != node.end())
	{
		float giatri[4] = { node["rotation"][3], node["rotation"][0],
			node["rotation"][1], node["rotation"][2] };
		xoay = glm::make_quat(giatri);
	}
	// kích thước nếu có
	glm::vec3 kichthuoc = glm::vec3(1.0f, 1.0f, 1.0f);
	if (node.find("scale") != node.end())
	{
		float giatri[3];
		for (GLuint i = 0; i < node["scale"].size(); i++)
			giatri[i] = (node["scale"][i]);
		kichthuoc = glm::make_vec3(giatri);
	}
	// ma trận nếu có
	glm::mat4 mat = glm::mat4(1.0f);
	if (node.find("matrix") != node.end())
	{
		float giatri[16];
		for (GLuint i = 0; i < node["matrix"].size(); i++)
			giatri[i] = (node["matrix"][i]);
		mat = glm::make_mat4(giatri);
	}

	// khởi tạo ma trận
	glm::mat4 dc, x, kt = dc = x = glm::mat4(1.0f);
	// biến đổ các ma trận
	dc = glm::translate(dc, dichchuyen);
	x = glm::mat4_cast(xoay);
	kt = glm::scale(kt, kichthuoc);
	// kết hợp chúng lại (= phép nhân)
	glm::mat4 matNext = matran * mat * dc * x * kt;

	// kiểm tra nếu node có lưới để chạy
	if (node.find("mesh") != node.end())
	{
		dichChuyen.push_back(dichchuyen);
		vongXoay.push_back(xoay);
		kichThuoc.push_back(kichthuoc);
		maTranLuoi.push_back(matNext);

		taiLuoi(node["mesh"]);
	}

	// kiểm tra nếu node đó là node cha (có node con) thì đi qua node con
	if (node.find("children") != node.end())
	{
		for (GLuint i = 0; i < node["children"].size(); i++)
			nodeQua(node["children"][i], matNext);
	}
}