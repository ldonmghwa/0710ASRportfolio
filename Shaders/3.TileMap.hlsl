
struct VertexInput
{
    float4  position : POSITION0;
    float2  uv : UV0;
    float4  color : COLOR0; //��������
    float   tileMapIdx : INDICES0;
    float   tileState : STATE0;
};
// PI
struct PixelInput
{
    float4  position : SV_POSITION; //ȭ����ǥ�� ������
    float2  uv : UV0; //���ε� ��ǥ
    float4  color : COLOR0; //��������
    float   tileMapIdx : INDICES0;
    float   tileState : STATE0;
};

//������� ũ��� 16byte����� �������Ѵ�.

cbuffer VS_WVP : register(b0) 
{
    matrix WVP;
}
//cbuffer VS_COLOR : register(b1)
//{
//    //4 ���� 4����Ʈ
//	float4 color;
//}
//cbuffer VS_UV : register(b2)
//{
//    float4 uv;
//}

cbuffer PS_LIGHT : register(b0)
{
	float2 screenPos; //��ũ����ǥ
	float radius; //������ũ��
	float select; //���� Ÿ�� ����
	float4 lightColor; //���� ��
	float4 outColor; //�ܰ� ��
};



//���ؽ� ���̴�
//��ȯ��  �Լ��̸�(�Ű�����)
// VertexInput(in) ->  VS  -> PixelInput (out)
PixelInput VS(VertexInput input)
{
    //������ȯ�� ���� ������ ��
    PixelInput output;
    output.position = mul(input.position, WVP);
	output.color = input.color;
    output.uv = input.uv;
    output.tileMapIdx = input.tileMapIdx;
    output.tileState = input.tileState;
    return output;
}

//�ؽ��� �ڿ�  (srv) ���� ����
Texture2D Texture0 : register(t0);
SamplerState Sampler0 : register(s0);

Texture2D Texture1 : register(t1);
SamplerState Sampler1 : register(s1);

Texture2D Texture2 : register(t2);
SamplerState Sampler2 : register(s2);

Texture2D Texture3 : register(t3);
SamplerState Sampler3 : register(s3);


//�ȼ����̴� ���� �Լ�
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET �� Ÿ���̵� ���� 
{
    float4 TextureColor;
    // ���ε� ��ǥ�� �ؽ��� �ε�
   
    [branch]
    if (input.tileMapIdx == 0.0f)
    {
        TextureColor = Texture0.Sample(Sampler0, input.uv);
    }
    else if (input.tileMapIdx == 1.0f)
    {
        TextureColor = Texture1.Sample(Sampler1, input.uv);
    }
    else if (input.tileMapIdx == 2.0f)
    {
        TextureColor = Texture2.Sample(Sampler2, input.uv);
    }
    else if (input.tileMapIdx == 3.0f)
    {
        TextureColor = Texture3.Sample(Sampler3, input.uv);
    }
	//return float4(input.tileMapIdx/3.0f.xxx,1);
    
    //�о�� �׸������� �ȼ������� ���ǹ����� ��
    [flatten]
    if (TextureColor.r == 1.0f &&
        TextureColor.g == 0.0f &&
        TextureColor.b == 1.0f)
    {
        //�ش� �ȼ��� ��������ʴ´�.
        discard;
    }
    
    TextureColor = TextureColor + (input.color * 2.0f - 1.0f);
    
    TextureColor = saturate(TextureColor);

      //����ȿ��
	float2 Minus = input.position.xy - screenPos;
	float dis = sqrt(Minus.x * Minus.x + Minus.y * Minus.y);
	if (select == 0.0f)
	{
		if (dis > radius)
		{
			TextureColor.rgb += (outColor.rgb * 2.0f - 1.0f);
		}
		else
		{
			TextureColor.rgb += (lightColor.rgb * 2.0f - 1.0f);
		}
	}
	else
	{
        //�ܰ����� 0 ����� 1
		float temp2 = pow(saturate(dis / radius), 3.0f);
		float temp = 1.0f - temp2;
        
		TextureColor.rgb =
		saturate((TextureColor.rgb + (lightColor.rgb * 2.0f - 1.0f)) * temp) +
		saturate((TextureColor.rgb + (outColor.rgb * 2.0f - 1.0f)) * temp2);
        
		//TextureColor.rgb *= temp;
	}
	
    //�����Ϳ����� Ȯ���Ҷ� �߰��Ұ�
    
	//if (input.tileState == 1.0f)
	//{
	//	return TextureColor + float4(0.5, 0, 0, 0);
	//}
    
    
	return saturate(TextureColor);
}