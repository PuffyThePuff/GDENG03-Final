struct VS_INPUT {
	float4 position: POSITION0;
	float2 texcoord: TEXCOORD0;
};

struct VS_OUTPUT {
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
};

cbuffer constant: register(b0) {
	row_major float4x4 worldMatrix;
	row_major float4x4 viewMatrix;
	row_major float4x4 projectionMatrix;
	float coefficient;
};

VS_OUTPUT vsmain(VS_INPUT input) {
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.texcoord = input.texcoord;
	return output;
}