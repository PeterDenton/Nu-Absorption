#include <iostream>

#include "Absorption.h"

int main()
{
	double E = 1e6; // 1 PeV
	for (double cos_zenith = -1; cos_zenith <= 1; cos_zenith += 0.01)
	{
		std::cout << cos_zenith << " " << dpdcoszenith(E, cos_zenith) << std::endl;
	} // cos_zenith

	return 0;
}
