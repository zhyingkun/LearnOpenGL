Shader "Unlit/BaseShader"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
		_AwesomeFace ("AwesomeFace", 2D) = "white" {}
		_AwesomeAlpha ("AwesomeAlpha", float) = 0.5
		_ColorAlpha ("ColorAlpha", float) = 0.2
	}
	SubShader
	{
		Tags { "RenderType"="Opaque" }
		LOD 100

		Pass
		{
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			
			#include "UnityCG.cginc"

			struct appdata
			{
				float4 aPos : POSITION;
				float4 aColor : COLOR0;
				float2 aTexCoord : TEXCOORD0;
			};

			struct v2f
			{
				float4 gl_Position : SV_POSITION;
				float2 TexCoord : TEXCOORD0;
				float4 vertexColor : COLOR0;
			};

			uniform sampler2D _MainTex;
			uniform float4 _MainTex_ST;
			uniform sampler2D _AwesomeFace;
			uniform float _AwesomeAlpha;
			uniform float _ColorAlpha;
			// uniform float4x4 model;
			// uniform float4x4 view;
			// uniform float4x4 projection;
			
			v2f vert (appdata v)
			{
				v2f o;
				o.gl_Position = UnityObjectToClipPos(v.aPos);
				// o.gl_Position = projection * view * model * v.aPos;
				o.TexCoord = TRANSFORM_TEX(v.aTexCoord, _MainTex);
				o.vertexColor = v.aColor;
				return o;
			}
			
			fixed4 frag (v2f i) : SV_Target
			{
				// sample the texture
				fixed4 color1 = tex2D(_MainTex, i.TexCoord);
				fixed4 color2 = tex2D(_AwesomeFace, i.TexCoord);
				fixed4 mixColor = lerp(color1, color2, _AwesomeAlpha);
				return lerp(mixColor, i.vertexColor, _ColorAlpha);
			}
			ENDCG
		}
	}
}
