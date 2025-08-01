#include "common.fx"

struct VertexInputType
{
    float4 position : POSITION; 
	float4 Bones : BONES;  
	float4 Weights : WEIGHTS;  
    float2 tex : UV;
};

cbuffer BoneBuffer : register(b1)
{
	matrix myBones[64];
};

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	
	float2 Resolution = myResolution.xy;
	float ratio = Resolution.y / Resolution.x;

    // Change the position vector to be 4 units for proper matrix calculations.
	 
    input.position.w = 1.0f; 
	
	//input.position.x -= myPivot.x; 
	//input.position.y += myPivot.y;
	 
	//input.position.xy *= myRotationAndSize.yz ;
	
	//float2x2 theRotation = ComputeRotation(myRotationAndSize.x);
	//input.position.xy = mul(input.position.xy, theRotation);
	//input.position.x *= ratio;
	//input.position.xy += myPosition;

	float4 skinnedPos = 0;
	uint iBone = 0;
	float fWeight = 0;
	
	iBone = input.Bones.x;
	fWeight = input.Weights.x;
	
	// Bone 0
	iBone = input.Bones.x;
	fWeight = input.Weights.x;
	float4 pos = input.position;
	skinnedPos += fWeight * mul(pos, myBones[iBone]);

	// Bone 1
	iBone = input.Bones.y;
	fWeight = input.Weights.y;
	skinnedPos += fWeight * mul(pos, myBones[iBone]);
	
	// Bone 2
	iBone = input.Bones.z;
	fWeight = input.Weights.z;
	skinnedPos += fWeight * mul(pos, myBones[iBone]);

	// Bone 3
	iBone = input.Bones.w;
	fWeight = input.Weights.w;
	skinnedPos += fWeight * mul(pos, myBones[iBone]);
	
	output.position.x = skinnedPos.x;
	output.position.y = skinnedPos.y;
	output.position.z = 0;
	output.position.w = 1;
	output.position.xy *= 0.01f;
	
	//output.position = input.position;
	output.position *= 0.5;
	output.position.w = 1;

	output.tex = myUV.xy + (input.tex * myUV.zw);
	output.color = 1; 
	output.textureMappingData = 0;
	
    return output;  
}