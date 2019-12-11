#version 330 core

in vec3 myColor;
in vec3 vertexPosition; // Recibimos como parametro la posicion del vertice

out vec4 FragColor;

void main() {
    FragColor = vec4( vertexPosition, 1.0);
	/*	
		Debido a que estamos pasando la posicion del vertice, cuando se va a pintar el fragmento, se pinta segun la posicion. De esta forma, tenemos los siguientes colores en las
		esquinas:
			- Vertice inferior derecha: Rojo --> Esto es debido a que el valor de la posicion en este punto es (0.5, -0.5, 0.0). En RGB, esto quiere decir que tenemos 0.5 en rojo, 0.0 en verde (que se convierte en 0) y 0 en azul.
			- Vertice inferior izquierda: Negro --> Esto es debido a que el valor de la posicion en este punto es (-0.5, -0.5, 0.0). En RGB, esto quiere decir que tenemos 0.5 en rojo (que se convierte en 0)
			, 0.5 en verde (que se convierte en 0) y 0 en azul.
			- Vertice superior: Rojo --> Esto es debido a que el valor de la posicion en este punto es (0.0, 0.5, 0.0). En RGB, esto quiere decir que tenemos 0.0 en rojo (que se convierte en 0), 0.5 en verde y 0 en azul.
		Por otro lado, el shader de fragmentos pinta los pixeles entre los vertices. Por esto, el color de cada pixel del triangulo sera su posicion. De esta forma, en el triangulo podemos ver que segun el pixel esta mas cerca
		del centro (0,0,0), este se convierte en mas negro. Por otro lado, contra mas cerca este del vertice superior, mas verde sera, contra mas cerca del vertice inferior derecho, mas rojo y contra mas cerca del vertice 
		inferior izquierdo, mas negro sera. Hay que mencionar tambien que entre el vertice superior y el vertice inferior derecho, existe una zona en la que el color verde y rojo se mezcla. Esto es debido a que estos pixeles
		tienen una posicion de, por ejemplo (0.2, 0.2, 0.0), por lo que el rojo será 0.2 y el verde 0.2, viendo la interpolacion de ambos vertices.
	*/
}