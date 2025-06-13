cbuffer VSConstants : register(b0)
{
    float4x4 world;
    float4x4 view;
    float4x4 projection;
};

// ���_�V�F�[�_�[�֓��͂���f�[�^
struct VSInput
{
    float4 pos : POSITION;
};


// ���_�V�F�[�_�[����o�͂���f�[�^
struct VSOutput
{
    float4 pos : SV_Position; // ���_�̍��W(�ˉe���W�n)
};
 
// ----------------------------------------------------------
// ���_�V�F�[�_�[
// ----------------------------------------------------------
VSOutput VS(VSInput vin)
{
    VSOutput Out;
    float4 p = mul(world, vin.pos);
    p = mul(view, p);
    p = mul(projection, p);
    Out.pos = p;
    return Out;
}
 
// ----------------------------------------------------------
// �s�N�Z���V�F�[�_�[
// ----------------------------------------------------------
float4 PS(VSOutput In) : SV_Target0
{
    return float4(0.5, 0.8, 0, 1);
}
