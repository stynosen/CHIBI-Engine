//GLOBAL MATRICES
//***************
cbuffer updateEveryTick
{
	// The World View Projection Matrix
	float4x4 m_MatrixWorldViewProj : WORLDVIEWPROJECTION;
	// The World Matrix
	float4x4 m_MatrixWorld : WORLD;
} 

cbuffer updateAtCommand
{
	// The texture panning Matrix
	float4x4 m_MatTex;
	float4 m_SizeAlphaPriority;
}

Texture2D m_TextureDiffuse
<
	string UIName = "Diffuse Texture";
	string UIWidget = "Texture";
>;

//STATES
//******

BlendState Blend
{
	BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
    BlendOp = ADD;
    SrcBlendAlpha = ZERO;
    DestBlendAlpha = ZERO;
    BlendOpAlpha = ADD;
    RenderTargetWriteMask[0] = 0x0F;
};

RasterizerState BackCulling 
{ 
	CullMode = BACK; 
};

//TEXTURE
//**************
SamplerState m_TextureSampler
{
	Filter = MIN_MAG_MIP_POINT;
 	AddressU = WRAP;
	AddressV = WRAP;
	AddressW = WRAP;
};

//VS IN & OUT
//***********
struct VS_Input
{
	float3 Position: POSITION;
	float2 TexCoord: TEXCOORD0;
};

struct VS_Output
{
	float4 Position: SV_POSITION;
	float2 TexCoord: TEXCOORD0;
};

// The main vertex shader
VS_Output MainVS(VS_Input input) 
{
	
	VS_Output output = (VS_Output)0;
	
	input.Position.z = 10000-m_SizeAlphaPriority.w;
	input.Position.x *= m_SizeAlphaPriority.x;
	input.Position.y *= m_SizeAlphaPriority.y;

	float4 position = float4(input.Position,1);
	output.Position = mul(position, m_MatrixWorldViewProj);
	
	float4 tempTexCoord = float4(input.TexCoord,1,1);
	tempTexCoord = mul(tempTexCoord,m_MatTex);
	output.TexCoord = tempTexCoord.xy;
	
	return output;
}

// The main pixel shader
float4 MainPS(VS_Output input) : SV_TARGET 
{
	
	float4 color = m_TextureDiffuse.Sample(m_TextureSampler, input.TexCoord);
	clip(step(color.r+color.b-(color.g*1000),1.5f)-1);
	float alpha = m_SizeAlphaPriority[2];
	return float4(color.rgb,alpha);
}

// Default Technique
technique10 WithoutAlphaBlending {
	pass p0 {
		SetRasterizerState(BackCulling);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}

technique10 WithAlphaBlending {
	pass p0 {
		SetRasterizerState(BackCulling);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
		SetBlendState(Blend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);
	}
}