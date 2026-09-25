import csv

with open("data_template.h") as f:
    template = f.read()

with open("compiled_shannon.csv") as f:
    data = csv.reader(f)
    print(data)

    output = ""
    for i, row in enumerate(data):
        if i == 0: continue

        output += "{" + f'"{row[0]}", {row[1]}, "{row[2]}", "{row[3]}", {row[4]}, {row[5]}, "{row[6]}" ' +  "},\n"

        print(output)

    filled = template.replace("$ENTRIES", output)

    with open("data.h", "w") as f:
        f.write(filled)



