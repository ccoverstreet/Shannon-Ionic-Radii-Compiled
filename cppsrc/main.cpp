#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include "data.h"

void print_help() {
	std::cout << "Help" << "\n";
}

void throw_exception(const char *msg) {
	throw std::invalid_argument(msg);
}

struct Filter {
	std::vector<const char*> symbols;
	const char *coord;
	const char *charge;
	const char *sort;

};

void print_filt(const Filter &filt) {
	for (int i = 0; i < filt.symbols.size(); i++) {
		std::cout << filt.symbols[i] << " ";
	}
	std::cout << "\n";
	std::cout << filt.coord << " " << filt.charge << " " << filt.sort << "\n";
}

Filter parse_args(int argc, char *argv[]) {
	int i = 1;
	Filter filt = Filter{{}, "", "", ""};

	while (i < argc) {
		if (strcmp(argv[i], "--coord") == 0) {
			if (i+1 >= argc) throw_exception("No argument provided for --coord");

			filt.coord = argv[i+1];
			i++;
		} else if (strcmp(argv[i], "--charge") == 0) {
			if (i+1 >= argc) throw_exception("No argument provided for --charge");

			filt.charge = argv[i+1];
			i++;
		} else if (strcmp(argv[i], "--sort") == 0) {
			if (i+1 >= argc) throw_exception("No argument provided for --sort");

			filt.sort = argv[i+1];
			i++;
		} else {
			filt.symbols.push_back(argv[i]);
		}

		i++;
	}
	
	return filt;
}


int main(int argc, char *argv[]) {
	if (argc == 1) { print_help(); }



	Filter filt = parse_args(argc, argv);

	std::vector<RadiiEntry> sel_elems;

	std::copy_if(RADII.begin(), RADII.end(), std::back_inserter(sel_elems),
			[filt](RadiiEntry r) {
				for (int i = 0; i < filt.symbols.size(); i++) {
					if (strcmp(r.symbol, filt.symbols[i]) == 0) return true;
				}
				return false;
			});

	std::vector<RadiiEntry> sel_coord;

	if (strcmp(filt.coord, "") != 0) {
		std::copy_if(sel_elems.begin(), sel_elems.end(), std::back_inserter(sel_coord),
				[filt](RadiiEntry r) {
					//std::cout << r.coord << filt.coord << strcmp(r.coord, filt.coord) << "\n";
					if (strcmp(r.coord, filt.coord) == 0) return true;
					return false;
				});
	} else {
		sel_coord = sel_elems;
	}

	std::vector<RadiiEntry> sel_charge;
	if (strcmp(filt.charge, "") !=0) {
		char *end;
		long charge_int = strtol(filt.charge, &end, 10);
		std::copy_if(sel_coord.begin(), sel_coord.end(), std::back_inserter(sel_charge),
				[charge_int, filt](RadiiEntry r) {
						//std::cout << r.coord << filt.coord << strcmp(r.coord, filt.coord) << "\n";
						if (r.charge == charge_int) return true;
						return false;
					});

	} else {
		sel_charge = sel_coord;
	}

	std::vector<RadiiEntry> sel_final;

	if (strcmp(filt.sort, "") != 0) {
		sel_final = sel_charge;
		if (strcmp(filt.sort, "r_ionic") == 0) {
			std::sort(sel_final.begin(), sel_final.end(), 
					[](RadiiEntry a, RadiiEntry b) {
						return a.r_ionic < b.r_ionic;
					});
		} else if (strcmp(filt.sort, "r_crystal") == 0) {
			std::sort(sel_final.begin(), sel_final.end(), 
					[](RadiiEntry a, RadiiEntry b) {
						return a.r_crystal < b.r_crystal;
					});
		} else if (strcmp(filt.sort, "charge") == 0) {
			std::sort(sel_final.begin(), sel_final.end(), 
					[](RadiiEntry a, RadiiEntry b) {
						return a.charge < b.charge;
					});
		}
	} else {
		sel_final = sel_charge;
	}

	printf("%3s %6s %6s %13s %15s\n", "sym", "charge", "coord", "r_crystal [Å]", "r_ionic [Å]");
	for (size_t i = 0; i < sel_final.size(); i++) {
		RadiiEntry_print(sel_final[i]);
	}

	return 0;
}

