#version 330 core

out vec4 MauFrag;
in vec2 txCrd;
uniform sampler2D hinh;
uniform float gamma;

const float _x = 1.0f / 800.0f, _y = 1.0f / 800.0f;
vec2 offset[9] = vec2[]
(
	vec2(-_x,   _y), vec2(0.0f,   _y), vec2(_x,   _y),
	vec2(-_x, 0.0f), vec2(0.0f, 0.0f), vec2(_x, 0.0f),
	vec2(-_x,  -_y), vec2(0.0f,  -_y), vec2(_x,  -_y)
);
float cotLoi[9] = float[]
(
	3,   3, 3,
	3, -23, 3,
	3,   3, 3
);

void main()
{
	// khung canh trang den
	//vec3 mauSac = vec3(0.0f);
	//for (int i = 0; i < 9; i++)
	//	mauSac += vec3(texture(hinh, txCrd.st + offset[i])) * cotLoi[i];
	//float trb = (mauSac.x + mauSac.y + mauSac.z) / 3.0f;
	
	vec3 phanManh = texture(hinh, txCrd).rgb;
	float huongDen = 0.1;
	vec3 chinhSua = vec3(1.0f) - exp(-phanManh * huongDen);
	MauFrag.rgb = pow(chinhSua.rgb, vec3(1.35f + gamma));
}