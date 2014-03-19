all: build/ktomgirl
	cd build && make 2>err

build/ktomgirl:
				export QT_SELECT=qt4 && mkdir -p build && cd build && cmake ..
clean:
	rm -rvf build/ktomgirl

dist-clean:
	rm -rvf build

test: build/ktomgirl
	build/ktomgirl

