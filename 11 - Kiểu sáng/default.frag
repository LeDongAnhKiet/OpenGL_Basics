#version 330 core

out vec4 MauFrag;
in vec3 mauSac, bThg, vtht;
in vec2 txCrd;

uniform sampler2D tex0, tex1;
uniform vec4 mauDen;
uniform vec3 vtDen, vtCam;

vec4 sangCoHuong()
{
	// tao cac bien de ko can tinh toan 2 lan
	vec3 huongDen = vtDen - vtht;
	// khoang cach tu huong den tao cuong do anh sang
	float kCach = length(huongDen);
	float a = 2.0, b = 0.3;
	float cuongDo = 1.0f / (a * kCach * kCach + b * kCach + 1.0f);

	float mTrg = 0.2f;
	vec3 bthg = normalize(bThg);
	vec3 huongSang = normalize(huongDen);
	float phanTan = max(dot(bthg, huongSang), 0.0f);

	float phanChieu = 0.5f;
	vec3 huongNhin = normalize(vtCam - vtht);
	vec3 huongChieu = reflect(-huongSang, bthg);
	
	float luongSang = pow(max(dot(huongNhin, huongChieu), 0.0f), 16);
	float anhSang = luongSang * phanChieu;
	return (texture(tex0, txCrd) * (phanTan * cuongDo + mTrg) + texture(tex1, txCrd).r * anhSang * cuongDo) * mauDen;
}

vec4 sangTrucTiep()
{
	float mTrg = 0.2f;
	vec3 bthg = normalize(bThg);
	vec3 huongSang = normalize(vec3(1.0f, 1.0f, 0.0f));
	float phanTan = max(dot(bthg, huongSang), 0.0f);

	float phanChieu = 0.5f;
	vec3 huongNhin = normalize(vtCam - vtht);
	vec3 huongChieu = reflect(-huongSang, bthg);
	
	float luongSang = pow(max(dot(huongNhin, huongChieu), 0.0f), 16);
	float anhSang = luongSang * phanChieu;
	return (texture(tex0, txCrd) * (phanTan + mTrg) + texture(tex1, txCrd).r * anhSang) * mauDen;
}

vec4 sang1diem()
{
	// tao vung sang
	float benNgoai = 0.7f, benTrg = 0.85f, mTrg = 0.2f;
	vec3 bthg = normalize(bThg), huongDen = vtDen - vtht;
	vec3 huongSang = normalize(huongDen);
	float phanTan = max(dot(bthg, huongSang), 0.0f);

	float phanChieu = 0.5f;
	vec3 huongNhin = normalize(vtCam - vtht);
	vec3 huongChieu = reflect(-huongSang, bthg);
	
	float luongSang = pow(max(dot(huongNhin, huongChieu), 0.0f), 16);
	float anhSang = luongSang * phanChieu;
	// tinh cuong do sang cua vung hien tai dua tren goc do va diem giua cai den chieu
	float goc = dot(vec3(0.0f, -1.0f, 0.0f), -huongSang);
	float cuongDo = clamp((goc - benNgoai) / (benTrg - benNgoai), 0.0f, 1.0f);
	
	return (texture(tex0, txCrd) * (phanTan * cuongDo + mTrg) + texture(tex1, txCrd).r * anhSang * cuongDo) * mauDen;
}

void main()
{
	// moi ham kieu sang khac nhau
	MauFrag = sang1diem();
	//	MauFrag = sangTrucTiep();
	//	MauFrag = sangCoHuong();

}