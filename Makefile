all: procyon

procyon:
	g++ *.cpp -o procyon -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm procyon
