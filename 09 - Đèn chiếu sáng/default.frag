#version 330 core

out vec4 MauFrag;
// nhap mau sac tu Vertex shader
in vec3 mauSac;
// nhap toa do ket cau tu Vertex shader
in vec2 txCrd;
// nhap toa do binh thuong tu Vertex shader
in vec3 bThg;
// nhap vi tri hien tai tu Vertex shader
in vec3 vtht;

uniform sampler2D tex;
// lay mau sac cua den chieu tu ham chinh
uniform vec4 mauDen;
// lay vi tri cua den chieu tu ham chinh
uniform vec3 vtDen;
// lay vi tri goc nhin tu ham chinh
uniform vec3 vtCam;

void main()
{
	// moi truong sang
	float mTrg = 0.2f;
	// phan tan anh sang
	vec3 bthg = normalize(bThg);
	vec3 huongSang = normalize(vtDen - vtht);
	float phanTan = max(dot(bthg, huongSang), 0.0f);

	// anh sang phan chieu
	float phanChieu = 0.5f;
	vec3 huongNhin = normalize(vtCam - vtht);
	vec3 huongChieu = reflect(-huongSang, bthg);
	float luongSang = pow(max(dot(huongNhin, huongChieu), 0.0f), 8);
	float anhSang = luongSang * phanChieu;
	// xuat mau sac anh sang
	MauFrag = texture(tex, txCrd) * mauDen * (phanTan + mTrg + anhSang);
}