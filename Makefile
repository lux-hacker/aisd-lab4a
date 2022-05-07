all: build tree.a view.o controller.o main.o
	cc -o lab4a build/*.o -lreadline -L./build -ltree -std=c11 -g

timing: build tree.a view.o controller.o timnig.o
	cc -o timing build/*.o -lreadline -L./build -ltree -std=c11 -g

build:
	mkdir build

tree.a: model.o
	ar rcs build/libtree.a build/BinTree.o
	rm build/BinTree.o

main.o:
	cc -c main.c -o build/main.o -std=c11 -g

timnig.o:
	cc -c timing.c -o build/timnig.o -std=c11 -g

model.o:
	cc -c model/BinTree.c -o build/BinTree.o -std=c11 -g

view.o:
	cc -c view/view.c -o build/view.o -std=c11 -g

controller.o:
	cc -c controller/controller.c -o build/controller.o -std=c11 -g

clean:
	rm -rf build/
	rm lab4a
