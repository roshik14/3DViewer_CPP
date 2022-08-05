attribute vec3 coord3d;
varying vec3 vColor;

uniform vec3 color;
uniform mat4 MVP;

void main(void) {
    gl_Position = MVP * vec4(coord3d.x, coord3d.y, coord3d.z, 1.0);
    vColor = color;
}