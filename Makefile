all:
	g++ -o main main.cpp
	g++ -o solution solution.cpp
	g++ -o wrong1 wrong1.cpp
	g++ -o wrong2 wrong2.cpp
	g++ -o judge judge.cpp
install:
	echo "Compiling and copying executable to /usr/local/bin"
	g++ -o interactor main.cpp
	sudo cp ./interactor /usr/local/bin/interactor
example:
	@make all
	./main solution judge
	./main wrong1 judge
	./main wrong2 judge