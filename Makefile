all: initialize_build_dir initialize_ninja_compile build_program

initialize_build_dir:
	mkdir -p build/	

initialize_ninja_compile:
	cd build/ && cmake -G Ninja ..

build_program:
	 ninja  -C build 

run: 
	./build/dpp 5

clean:
	rm -rf build


