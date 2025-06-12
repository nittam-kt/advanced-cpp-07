cbuffer VSConstants : register(b0)
{
    float4x4 world;
    float4x4 view;
    float4x4 projection;
};

// 頂点シェーダーへ入力するデータ
struct VSInput
{
    float4 pos : POSITION;
};


// 頂点シェーダーから出力するデータ
struct VSOutput
{
    float4 pos : SV_Position; // 頂点の座標(射影座標系)
};
 
// ----------------------------------------------------------
// 頂点シェーダー
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
// ピクセルシェーダー
// ----------------------------------------------------------
float4 PS(VSOutput In) : SV_Target0
{
    return float4(0.5, 0.8, 0, 1);
}
