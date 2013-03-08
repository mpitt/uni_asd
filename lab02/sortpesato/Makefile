all: sortpesato

sortpesato: sortpesato.cpp
	g++ sortpesato.cpp -o sortpesato

clean:
	rm sortpesato output.txt

test: sortpesato.cpp
	g++ sortpesato.cpp -o sortpesato_test
	./sortpesato_test
	read actual < output.txt
	read expected < expected_output.txt
	[[ "$$actual" == "$$expected" ]] && echo OK || echo NO
	rm sortpesato_test
