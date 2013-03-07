all: quicksort mergesort

quicksort: quicksort.cpp
	g++ quicksort.cpp -o quicksort

mergesort: mergesort.cpp
	g++ mergesort.cpp -o mergesort

select_quick: quicksort
	ln -s quicksort sort 
	ln -s quicksort.cpp sort.cpp 

select_merge: mergesort
	ln -s mergesort sort 
	ln -s mergesort.cpp sort.cpp 


