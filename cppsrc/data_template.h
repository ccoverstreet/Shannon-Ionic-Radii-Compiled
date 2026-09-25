#include <vector>
#include <cstdint>
#include <iostream>

struct RadiiEntry {
	const char *symbol;
	int8_t charge;
	const char *coord;
	const char *spin;
	float r_crystal;
	float r_ionic;
	const char *key;
};

void RadiiEntry_print(RadiiEntry &e) {
	//std::cout << e.symbol << " " << int(e.charge) << " " << e.coord << " " << e.r_crystal << " " << e.r_ionic << "\n";
	printf("%3s %6d %6s %13.3f %13.3f\n", e.symbol, e.charge, e.coord, e.r_crystal, e.r_ionic);
}

std::vector<RadiiEntry> RADII = {
	$ENTRIES
};
