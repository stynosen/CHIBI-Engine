//GLOBAL MATRICES
//***************
// The World View Projection Matrix
float4x4 m_MatrixWorldViewProj : WORLDVIEWPROJECTION;

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

RasterizerState FrontCulling 
{ 
	CullMode = FRONT; 
};

RasterizerState BackCulling 
{ 
	CullMode = BACK; 
};

RasterizerState DisableCulling
{ 
	CullMode = NONE; 
};

float4 m_Color
<
	string UIName = "Color";
	string UIWidget = "Color";
> = float4(1,1,1,1);

int	  m_DrawPriority = 0;


//VS IN & OUT
//***********
struct VS_Input
{
	float3 Position: POSITION;
};

struct VS_Output
{
	float4 Position: SV_POSITION;
};

// The main vertex shader
VS_Output MainVS(VS_Input input) 
{
	
	VS_Output output = (VS_Output)0;
	
	input.Position.z = 10000-m_DrawPriority;
	
	float4 position = float4(input.Position,1);
	output.Position = mul(position, m_MatrixWorldViewProj);
	
	return output;
}

// The main pixel shader
float4 MainPS(VS_Output input) : SV_TARGET 
{
	return m_Color;
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