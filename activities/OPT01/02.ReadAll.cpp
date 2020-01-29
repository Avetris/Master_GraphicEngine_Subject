#include <vector>
#include <iostream>

// Implemented by subclasses; reads up to `bytes` bytes into `buf`, returns 
// number of bytes actually read.  If the return value is less than requested 
// `bytes`, the end of the stream has been encountered.
size_t Read(char* buf, size_t bytes) {
	for (size_t i = 0; i < bytes && i < 50000; i++) {
		buf[i] = i;
	}
	if (bytes > 50000) {
		return 50000;
	}
	else {
		return bytes;
	}
}

// Candidate to implement: return a vector with all bytes in the file.  Note 
// that the size of the stream is unknown.
std::vector<char> ReadAll() {
	std::vector<char> vec;
	size_t bytes = 1;
	size_t bytes_read = 1;
	while (bytes_read == bytes) {
		bytes *= 10; // Multiplicamos por 10 los bytes, para avanzar mas rapido
		char* buf = new char[bytes]; // Generamos el buffer
		bytes_read = Read(buf, bytes); // Leemos los bytes y obtenemos los bytes totales leidos
		if (bytes_read != bytes) { // En caso de no haber leido todos los bytes que hemos pasado
			vec.insert(vec.end(), buf, buf + bytes_read); // Lo guardamos los bytes en el vector y salimos del loop
		}
		delete[] buf; // Destruimos el buffer
	}
	return vec;
}
void main() {
	std::vector<char> vec = ReadAll();
	for (auto it = vec.begin(); it < vec.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}