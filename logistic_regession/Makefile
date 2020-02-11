all: main

main: main.o
	g++ -o main main.o Dataset.o logisticRegression.o

main.o: logisticRegression.o
	g++ -c main.cpp -std=c++11

logisticRegression.o: Dataset.o
	g++ -c logisticRegression.cpp -std=c++11

Dataset.o:
	g++ -c Dataset.cpp -std=c++11

clean:
	rm -f Dataset.o logisticRegression.o main.o main