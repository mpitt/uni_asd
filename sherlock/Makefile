all: sherlock

sherlock: sherlock.cpp
	g++ sherlock.cpp -o sherlock

test: sherlock
	bash test_all.sh ./sherlock

clean: clean_bin clean_out

clean_bin:
	rm sherlock

clean_out:
	rm output.txt


