#!/usr/bin/env python3

import pandas as pd
import argparse
import io
import textwrap
# CSV
# symbol,charge,coord,spin state,r_crystal [Å],r_ionic [Å],key

CSV_STRING = """
$CSV_STRING
"""
DATA = pd.read_csv(io.StringIO(CSV_STRING))

def main():
    parser = argparse.ArgumentParser(
        prog="ShannonRadiiCLI",
        description="CLI for Shannon Ionic Radii database"
    )

    parser.add_argument("elementsymbols", nargs="+", help="Symbols of elements")
    parser.add_argument("--coord", nargs="?", help="Specify coordination as Roman numeral (ex. VI)", type=str)
    parser.add_argument("--charge", nargs="?", help="Specify charge state", type=int)
    parser.add_argument("--sort", nargs="?", help="Sort by column: symbol, charge, spin, r_crystal, r_ionic, key")

    args = parser.parse_args()

    sel_by_elems = DATA[DATA["symbol"].isin(args.elementsymbols)]

    sel_by_coord = sel_by_elems
    if args.coord != None:
        sel_by_coord = sel_by_elems[sel_by_elems["coord"] == args.coord]

    sel_by_charge = sel_by_coord
    if args.charge != None:
        sel_by_charge = sel_by_coord[sel_by_coord["charge"] == args.charge]


    if len(sel_by_charge) == 0:
        print("No matches found")
        return 


    sel = sel_by_charge.fillna("")

    if args.sort != None:
        col = args.sort
        if "r_" in col:
            col += " [Å]"

        sel = sel.sort_values(col)


        
    #sel_by_charge["key"] = sel_by_charge["key"].apply(textwrap.fill, width=5)
    pd.set_option('display.max_columns', None)
    pd.set_option('display.max_rows', None)
    pd.set_option('display.max_colwidth', None)
    pd.set_option('display.width', None)
    print(sel)


if __name__ == "__main__":
    main()
