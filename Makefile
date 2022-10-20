all: wc_c++ wc_go data.txt
	@echo "Perf tests begin ..."
	@echo
	time wc_c++ data.txt > /dev/null ; echo
	time wc_go  data.txt > /dev/null ; echo
	time wc.js  data.txt > /dev/null ; echo
	time wc.py  data.txt > /dev/null ; echo
	time wc.pl  data.txt > /dev/null ; echo
	time wc.rb  data.txt > /dev/null ; echo
	@echo "Perf test end."
	@echo

wc_c++:
	@g++ -std=c++11 -O3 wc.cc -o wc_c++

wc_go:
	@go build -o wc_go wc.go

data.zip:
	@echo "Downloading data, it's going to take a while ..."
	@echo
	@wget -q --show-progress http://mattmahoney.net/dc/enwik9.zip -O data.zip
	@echo

data.txt: data.zip
	unzip -c data.zip | head -1000000 > data.txt
	@echo

clean:
	rm -f wc_c++ wc_go data.txt data.zip wc-*.tar.gz *~

dist: clean
	@pushd .. && \
	tar cvfpz /tmp/wc-`date "+%Y%m%d"`.tar.gz wc && \
	popd && \
	mv /tmp/wc-`date "+%Y%m%d"`.tar.gz .
