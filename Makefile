all:
	g++ huffman_encode_decode.cpp -std=c++11 -o exe

clean:
	/bin/rm -rf exe
