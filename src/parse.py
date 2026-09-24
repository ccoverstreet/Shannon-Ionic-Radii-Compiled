from bs4 import BeautifulSoup

#def coord_to_number(coord):
#    # Can't be bothered to make a proper parser right now
#    mapping = {
#        "I": 1,
#        "II": 2,
#        "III": 3,
#        "IV": 4,
#        "V": 5,
#        "VI": 6,
#        "VII": 7,
#        "VIII": 8,
#        "IX": 9,
#        "X": 10,
#        "XI": 11,
#        "XII": 12
#    }

def key_mapping(key):
    if key == "": return ""

    mapping = {
        "R": "From r^3 vs V",
        "C": "Calc. from len.-str. eq",
        "E": "Estimated",
        "?": "Doubtful",
        "*": "Most Reliable",
        "M": "From Metallic Oxides",
        "A": "Ahrens (1952) Ionic radius",
        "P": "Paulings (1960) Crystal Radius",
    }

    out = ""
    for c in key:
        out += mapping[c] + ". "

    return out

with open("radii.html") as f:
    soup = BeautifulSoup(f.read(), features="lxml")

tables = soup.find_all("table")



out = []

cur_elem = None
cur_charge = None
iterator = iter(tables[1].children)
for i, c in enumerate(iterator):
    if c.name == None: continue
    if i == 1:
        continue
    
    contents = list(filter(lambda x: x.name == "td", c.contents))

    if len(contents) == 7:
        print("NEW ELEM")
        cur_elem = contents[0].text
        cur_charge = contents[1].text
    if len(contents) == 6:
        cur_charge = contents[0].text
    if len(contents) < 5:
        continue

    coord = contents[-5].text
    spin_state = contents[-4].text if contents[-4].text != '&nbsp' else ""
    crystal_radius = float(contents[-3].text)
    ionic_radius = float(contents[-2].text)
    key = contents[-1].text if contents[-1].text != '&nbsp' else ""

    out.append((
        cur_elem,
        cur_charge,
        coord,
        spin_state,
        crystal_radius,
        ionic_radius,
        key_mapping(key)
    ))


with open("compiled_shannon.csv", "w") as f:
    f.write(f"symbol,charge,coord,spin,r_crystal [Å],r_ionic [Å],key\n")
    for row in out:
        f.write(",".join((str(x) for x in row)) + "\n")


    
print(out)
