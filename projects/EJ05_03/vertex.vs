#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUV;
layout (location=2) in vec3 aNormal;

out vec2 UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main() {
    UV = aUV;
    gl_Position = proj * view * model * vec4(aPos, 1.0); // original
 //   gl_Position = proj * model * view * vec4(aPos, 1.0);
 //   gl_Position = model * proj * view * vec4(aPos, 1.0);
 //   gl_Position = view * proj * model * vec4(aPos, 1.0);
 //   gl_Position = model * view * proj * vec4(aPos, 1.0);
 //   gl_Position = view * model * proj * vec4(aPos, 1.0);
}

// Se puede observar como al cambiar el orden de las transformaciones, se comporta de manera diferente. De esta forma, ocurren las diferentes transformaciones:
//      - proj * view * model = La transformacion es la que queremos, en la que el cubo rota sobre si mismo, con una proyeccion perspectiva y en la posicion (0,0,-3)
//      - proj * model * view = Se puede observar como el cubo rota (o eso creo) sobre el eje de la vista, en vez de su propio eje, moviendolo fuera de la pantalla
//      - model * proj * view = Se realiza una rotacion sobre el eje de la matriz de proyeccion. Ademas, la direccion de los vertices del cubo cambian, por lo que le faltan caras al cubo.
//      - view * proj *  model = No se visualiza nada. Entiendo que es porque el objeto se encuentra fuera de la camara ya que la proyeccion que se esta aplicando es el de la vista (0,0,-3) y el cubo esta en (0.5f, 1.0f, 0.0f)
//      - model * view * proj = No se visualiza nada. Entiendo que es porque la transformacion de la proyeccion se esta aplicando antes que el resto, por lo que se esta sacando de la camara.
//      - view * model * proj = 