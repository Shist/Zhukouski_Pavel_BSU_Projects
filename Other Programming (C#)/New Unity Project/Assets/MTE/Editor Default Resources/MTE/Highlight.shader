Shader "Hidden/MTE/Highlight"
{
    Properties
    {
        _Color("Tint Color", Color) = (0.6, 0, 0, 1)
    }

    SubShader
    {
        Tags
        {
            "Queue" = "Transparent"
            "RenderType" = "Transparent"
        }
        LOD 250
        CULL OFF
        AlphaToMask On

        CGPROGRAM
        #pragma surface surf Lambert decal:add
        fixed4 _Color;
        struct Input {
            float4 color : COLOR;
        };

        void surf(Input IN, inout SurfaceOutput o) {
            fixed4 c = _Color;
            o.Albedo = c.rgb;
            o.Alpha = c.a;
        }
        ENDCG
    }
}
