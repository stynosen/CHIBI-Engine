cbuffer perTick
{
	float4x4 m_MatViewProjection : VIEWPROJECTION;
}

Texture2D m_TextureDiffuse;
float	  m_Alpha;


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
//VS IN & OUT
//***********
struct VS_Input
{
	float3 	Position		: POSITION;
	float2 	TexCoord		: TEXCOORD0;
	float4	PosSizePriority	: WORLD0;
	float4	TexInfo			: WORLD1;
};

struct VS_Output
{
	float4 Position: SV_POSITION;
	float2 TexCoord: TEXCOORD0;
};

float4x4 DecodeMatrix(float2 pos)
{
	return float4x4(	float4(1,0,0,0),
						float4(0,1,0,0),
						float4(0,0,1,0),
						float4(pos.x,pos.y,0,1));
}

float4x4 BuildTexMatrix(float4 texInfo)
{
	float4x4 output = float4x4(
	texInfo.x,0,0,0
	,0,texInfo.y,0,0
	,texInfo.z,texInfo.w,0,0
	,0,0,0,0);
	
	return output;
}

// The main vertex shader
VS_Output MainVS(VS_Input input) 
{
	
	VS_Output output = (VS_Output)0;
	
	input.Position.z = 10000-input.PosSizePriority.w;
	input.Position.x *= input.PosSizePriority.z;
	input.Position.y *= input.PosSizePriority.z;

	float4x4 matWorldViewProjection = mul(DecodeMatrix(input.PosSizePriority.xy),m_MatViewProjection);
	float4x4 matTex = BuildTexMatrix(input.TexInfo);

	float4 position = float4(input.Position,1);
	output.Position = mul(position, matWorldViewProjection);
	
	float4 tempTexCoord = float4(input.TexCoord,1,1);
	tempTexCoord = mul(tempTexCoord,matTex);
	output.TexCoord = tempTexCoord.xy;
	
	return output;
}

// The main pixel shader
float4 MainPS(VS_Output input) : SV_TARGET 
{
	
	float4 color = m_TextureDiffuse.Sample(m_TextureSampler, input.TexCoord);
	clip(step(color.r+color.b-(color.g*1000),1.5f)-1);
	return float4(color.rgb,m_Alpha);
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