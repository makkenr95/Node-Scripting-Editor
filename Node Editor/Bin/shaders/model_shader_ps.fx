#include "common.fx"

SamplerState SampleType;

#define DIFFUSE_MAP 0
#define NORMAL_MAP 1

Texture2D shaderTextures[2] : register( t1 );

float4 PShader(PixelInputType input) : SV_TARGET
{
	float4 Diffuse = shaderTextures[DIFFUSE_MAP].Sample(SampleType, input.tex) * input.color;
	Diffuse.a = 1;
	Diffuse = input.color;
	return Diffuse;
}