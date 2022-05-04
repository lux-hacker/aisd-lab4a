all: build model.o view.o controller.o main.o
	cc -o lab4a build/*.o -lreadline -std=c11 -g

build:
	mkdir build

main.o:
	cc -c main.c -o build/main.o -std=c11 -g

model.o:
	cc -c model/BinTree.c -o build/BinTree.o -std=c11 -g

view.o:
	cc -c view/view.c -o build/view.o -std=c11 -g

controller.o:
	cc -c controller/controller.c -o build/controller.o -std=c11 -g

clean:
	rm -rf build/
	rm lab4a
