#version 330 core

out vec4 MauFrag;
in vec3 vtht, bThg, mauSac, vtDen, vtCam;
in vec2 txCrd;
in vec4 vtSang;

uniform sampler2D pTan, pChieu, vungToi, chuan, saiVt;
uniform vec4 mauDen;
uniform samplerCube khoiToi;
uniform float tamXa;

vec4 sangCoHuong()
{
	vec3 huongDen = vtDen - vtht;
	float kCach = length(huongDen), a = 0.0003f, b = 0.00002f;
	float cuongDo = 1.0f / (a * kCach * kCach + b * kCach + 1.0f);

	vec3 huongNhin = normalize(vtCam - vtht);
	float doCao = 0.05f, mTrg = 0.2f;
	const float lopDau = 8.0f, lopCuoi = 64.0f;
	float nLop = mix(lopCuoi, lopDau, abs(dot(vec3(0.0f, 0.0f, 1.0f), huongNhin)));
	float lopSau = 1.0f / nLop, lopHienTai = 0.0f;
	
	vec2 S = huongNhin.xy / huongNhin.z * doCao;
	vec2 deltaUV = S / nLop, UV = txCrd;
	float gtSauHienTai = 1.0f - texture(saiVt, UV).r;
	while (lopHienTai < gtSauHienTai)
	{
		UV -= deltaUV;
		gtSauHienTai = 1.0f - texture(saiVt, UV).r;
		lopHienTai += lopSau;
	}
	vec2 txCrdTruoc = UV + deltaUV;
	float doSauSau = gtSauHienTai - lopHienTai,
		doSauTruoc = 1.0f - texture(saiVt, txCrdTruoc).r - lopHienTai + lopSau;
	float khoiLg = doSauSau / (doSauSau - doSauTruoc);
	UV = txCrdTruoc * khoiLg + UV * (1.0f - khoiLg);

	if (UV.x > 1.0 || UV.y > 1.0 || UV.x < 0.0 || UV.y < 0.0) discard;
	vec3 bthg = normalize(texture(chuan, UV).xyz * 2.0f - 1.0f);
	vec3 huongSang = normalize(huongDen);
	float phanTan = max(dot(bthg, huongSang), 0.0f);

	float anhSang = 0.0f;
	if (phanTan != 0.0f)
	{
		float phanChieu = 0.5f;
		vec3 nuaDuong = normalize(huongNhin + huongSang);
		float luongSang = pow(max(dot(bthg, nuaDuong), 0.0f), 16);
		anhSang = luongSang * phanChieu;
	};
	float bongToi = 0.2f;
	vec3 vtSang = vtht - vtDen;
	float doSauHienTai = length(vtSang);
	float doLech = max(0.5f * (1.0f - dot(bthg, huongSang)), 0.0005f);

	int phamVi = 2;
	float pxSize = 1.0f / 1024.0f;
	for (int z = -phamVi; z <= phamVi; z++)
		for (int y = -phamVi ; y <= phamVi; y++)
			for (int x = -phamVi; x <= phamVi; x++)
			{
				float doSauGanNhat = texture(khoiToi, vtSang + vec3(x, y, z) * pxSize).r;
				doSauGanNhat *= tamXa;
				if (doSauHienTai > doSauGanNhat + doLech) bongToi += 1.0f;
			}
	bongToi /= pow((phamVi * 2 + 1), 3);
	return (texture(pTan, UV) * (phanTan * (1.0f - bongToi) * cuongDo + mTrg) + texture(pChieu, UV).r * anhSang * (1.0f - bongToi) * cuongDo) * mauDen;
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
		float luongSang = pow(max(dot(bthg, nuaDuong), 0.0f), 16);
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
	
	float bongToi = 0.0f;
	vec3 tdSang = vtSang.xyz / vtSang.w;
	if (tdSang.z <= 1.0f)
	{
		tdSang = (tdSang + 1.0f) / 2.0f;
		float doSauHienTai = tdSang.z;
		float doLech = max(0.00025f * (1.0f - dot(bthg, huongSang)), 0.000005f);
		
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
	return (texture(pTan, txCrd) * (phanTan * (1.0f - bongToi) * cuongDo + mTrg) + texture(pChieu, txCrd).r * anhSang * (1.0f - bongToi) * cuongDo) * mauDen;
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
	MauFrag = sangCoHuong();
}