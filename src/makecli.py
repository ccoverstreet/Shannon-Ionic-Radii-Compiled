with open("cli_template.py") as f:
    template = f.read()

with open("compiled_shannon.csv") as f:
    data = f.read()

out = template.replace("$CSV_STRING", data)

with open("shannonradiicli.py", "w") as f:
    f.write(out)
