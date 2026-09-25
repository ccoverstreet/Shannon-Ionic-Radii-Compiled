shannonradiicli: compiled_shannon.csv main.cpp data.h
	g++ -O3 main.cpp -o shannonradiicli

data.h: data_template.h compiled_shannon.csv make_header.py
	python make_header.py

compiled_shannon.csv: parse.py
	python parse.py

clean:
	rm shannonradiicli.py

