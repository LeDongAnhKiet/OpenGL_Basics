#version 330 core

out vec4 MauFrag;
in vec3 vtht, bThg, mauSac;
in vec2 txCrd;

uniform sampler2D pTan, pChieu;
uniform vec4 mauDen;
uniform vec3 vtDen, vtCam;

vec4 anhSang()
{
	float mTrg = 0.2f;
	vec3 bthg = normalize(bThg);
	vec3 huongSang = normalize(vec3(1.0f, 1.0f, 0.0f));
	// hinh anh phan tan se ko am, luon la so duong
	float phanTan = max(abs(dot(bthg, huongSang)), 0.0f);

	float phanChieu = 0.5f;
	vec3 huongNhin = normalize(vtCam - vtht);
	vec3 huongChieu = reflect(-huongSang, bthg);
	
	float luongSang = pow(max(dot(huongNhin, huongChieu), 0.0f), 16);
	float anhSang = luongSang * phanChieu;
	if (texture(pTan, txCrd).a < 0.1) discard;
	return (texture(pTan, txCrd) * (phanTan + mTrg) + texture(pChieu, txCrd).r * anhSang) * mauDen;
}

float gan = 0.1f, xa = 100.0f;
float tuyenTinhSau(float sau)
{
	return (2.0 * gan / xa) / (gan + xa - (sau * 2.0 - 1.0) * (xa - gan));
}

float logicSau(float sau, float doc, float bu)
{
	float z = tuyenTinhSau(sau);
	return (1 / (1 + exp(-doc * (z - bu))));
}

void main()
{
	float doc = 0.5f, bu = 5.0f;
	float doSau = logicSau(gl_FragCoord.z, doc = 0.5f, bu = 5.0f);
	MauFrag = anhSang() * (1.0f - doSau) + vec4(doSau * vec3(0.8f, 0.8f, 0.95f), 1.0f);
}