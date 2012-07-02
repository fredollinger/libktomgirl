TARGET = libktomgirl

all: 
	mkdir -p build
	cd build && make 2>err
setup:
	mkdir build
	cd build && cmake ..
err:
	vim build/err
clean:
	cd build && make clean

install: build/$(TARGET).so
	cp build/$(TARGET).so /usr/lib
	mkdir -p /usr/include/$(TARGET)
	cp -r *.hpp base /usr/include/$(TARGET)
	ldconfig

deps:
	sudo apt-get install g++ cmake
