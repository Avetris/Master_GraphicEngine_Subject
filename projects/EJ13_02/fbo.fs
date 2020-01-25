#version 330 core

out vec4 FragColor;

in vec2 uv;

uniform sampler2D screenTexture;

uniform float offsetX;
uniform float offsetY;

void main() {

    float horizontalKernel[9] = float[] (
        offsetX, 0, -offsetX,
        2*offsetX, 0, -2*offsetX,
        offsetX, 0, -offsetX
    );
    float verticalKernel[9] = float[] (
        -offsetY, -2*offsetY, -offsetY,
         0, 0, 0,
         offsetY, 2*offsetY, offsetY
    );
    vec4 G[9];
    for (int i = 0; i < 9; ++i) {
        G[i] = texture(screenTexture, uv + vec2(horizontalKernel[i], verticalKernel[i])); // Generamos el kernel
    }
    vec4 Gx = G[2] + G[5] + G[8] - (G[0] + G[3] + G[6]);
    vec4 Gy = G[0] + G[1] + G[2] - (G[6] + G[7] + G[8]);

    vec4 color = sqrt((Gx * Gx) + (Gy * Gy));

    FragColor = vec4(color.rgb, 1.0);
}



