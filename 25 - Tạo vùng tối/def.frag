#version 330 core

out vec4 MauFrag;
in vec3 vtht, bThg, mauSac;
in vec2 txCrd;
in vec4 vtSang;

uniform sampler2D pTan, pChieu, vungToi;
uniform vec4 mauDen;
uniform vec3 vtDen, vtCam;

vec4 sangCoHuong()
{
	vec3 huongDen = vtDen - vtht;
	float kCach = length(huongDen);
	float a = 2.0, b = 0.3;
	float cuongDo = 1.0f / (a * kCach * kCach + b * kCach + 1.0f);

	float mTrg = 0.2f;
	vec3 bthg = normalize(bThg);
	vec3 huongSang = normalize(huongDen);
	float phanTan = max(dot(bthg, huongSang), 0.0f);

	float anhSang = 0.2f;
	if (phanTan != 0.0f)
	{
		float phanChieu = 0.5f;
		vec3 huongNhin = normalize(vtCam - vtht);
		vec3 huongChieu = reflect(-huongSang, bthg);
		vec3 nuaDuong = normalize(huongNhin + huongSang);
	
		float luongSang = pow(max(dot(bThg, nuaDuong), 0.0f), 16);
		float anhSang = luongSang * phanChieu;
	};
	return (texture(pTan, txCrd) * (phanTan * cuongDo + mTrg) + texture(pChieu, txCrd).r * anhSang * cuongDo) * mauDen;
}

vec4 sangTrucTiep()
{
	float mTrg = 0.2f;
	vec3 bthg = normalize(bThg);
	vec3 huongSang = normalize(vtDen);
	float phanTan = max(dot(bthg, huongSang), 0.0f);
	
	float anhSang = 0.2f;
	if (phanTan != 0.0f)
	{
		float phanChieu = 0.5f;
		vec3 huongNhin = normalize(vtCam - vtht);
		vec3 nuaDuong = normalize(huongNhin + huongSang);
		float luongSang = pow(max(dot(bThg, nuaDuong), 0.0f), 16);
		anhSang = luongSang * phanChieu;
	};
	float bongToi = 0.0f;
	vec3 tdSang = vtSang.xyz / vtSang.w;
	if (tdSang.z <= 1.0f)
	{
		tdSang = (tdSang + 1.0f) / 2.0f;
		float doSauHienTai = tdSang.z;
		float doLech = max(0.025f * (1.0f - dot(bthg, huongSang)), 0.0005f);
		
		int phamVi = 2;
		vec2 pxSize = 1.0 / textureSize(vungToi, 0);
		for (int y = -phamVi; y <= phamVi; y++)
			for (int x = -phamVi; x <= phamVi; x++)
			{
				float doSauGanNhat = texture(vungToi, tdSang.xy + vec2(x, y) * pxSize).r;
				if (doSauHienTai > doSauGanNhat + doLech) bongToi += 1.0f;
			}
		bongToi /= pow((phamVi * 2 + 1), 2);
	}
	return (texture(pTan, txCrd) * (phanTan * (1.0f - bongToi) + mTrg) + texture(pChieu, txCrd).r * anhSang * (1.0f - bongToi)) * mauDen;
}

vec4 sang1diem()
{
	float benNgoai = 0.7f, benTrg = 0.85f, mTrg = 0.2f;
	vec3 bthg = normalize(bThg), huongDen = vtDen - vtht;
	vec3 huongSang = normalize(huongDen);
	float phanTan = max(dot(bthg, huongSang), 0.0f);

	float phanChieu = 0.5f;
	vec3 huongNhin = normalize(vtCam - vtht);
	vec3 huongChieu = reflect(-huongSang, bthg);
	
	float luongSang = pow(max(dot(huongNhin, huongChieu), 0.0f), 16);
	float anhSang = luongSang * phanChieu;
	float goc = dot(vec3(0.0f, -1.0f, 0.0f), -huongSang);
	float cuongDo = clamp((goc - benNgoai) / (benTrg - benNgoai), 0.0f, 1.0f);
	
	return (texture(pTan, txCrd) * (phanTan * cuongDo + mTrg) + texture(pChieu, txCrd).r * anhSang * cuongDo) * mauDen;
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
	MauFrag = sangTrucTiep() * (1.0f - doSau) + vec4(doSau * vec3(0.8f, 0.8f, 0.95f), 1.0f);
}