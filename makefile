iteraciones.png : iteraciones.txt matrices.py
	python matrices.py
	rm iteraciones.txt nx.txt
iteraciones.txt : matrices.x
	./matrices.x
	rm matrices.x
matrices.x : matrices.cpp
	g++ matrices.cpp -o matrices.x

clear :
	rm iteraciones.png 