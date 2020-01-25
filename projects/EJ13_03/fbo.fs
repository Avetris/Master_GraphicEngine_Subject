#version 330 core

out vec4 FragColor;

in vec2 uv;

uniform sampler2D screenTexture;

uniform float rt;

float offset[5] = float[](0.0, 1.0, 2.0, 3.0, 4.0);
float weight[5] = float[](0.2270270270, 0.1945945946, 0.1216216216,
                                  0.0540540541, 0.0162162162);

void main() 
{ 
    vec3 tc = texture2D(screenTexture, uv).rgb * weight[0];

    for (int i=1; i<5; i++) 
    {
        tc += texture2D(screenTexture, uv + vec2(0.0, offset[i])/rt).rgb \
                * weight[i];
        tc += texture2D(screenTexture, uv - vec2(0.0, offset[i])/rt).rgb \
                * weight[i];
    }
    FragColor = vec4(tc, 1.0);
}

