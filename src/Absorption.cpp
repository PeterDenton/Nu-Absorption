#include <cmath>

#include "Absorption.h"
#include "rng.h"

double R = 6.317e8; // mean earth radius in cm
double d = 1950e2; // average depth of IC in cm

double dpdcoszenith(double E, double cos_zenith)
{
	double A, s, e;
	A = 1; // UNNORMALIZED, but max dpdcoszenith is always at cos_zenith = 1
	s = sqrt((pow(R, 2) - 2 * R * d) * pow(cos_zenith, 2) + 2 * R * d);
	e = exp(-(s - (R - d) * cos_zenith) / interaction_length(E, cos_zenith));
	return A * e;
}

double M_N = 1.672621777e-24; // proton mass in g
double interaction_length(double E, double cos_zenith)
{
	return M_N / (sigma(E) * mean_density(cos_zenith));
}

// from arxiv:1102.0691 table 3
double CnuNC[5] = {-1.826, -17.31, -6.448, 1.431, -18.61};
double CnuCC[5] = {-1.826, -17.31, -6.406, 1.431, -17.91};
double CbarNC[5] = {-1.033, -15.95, -7.296, 1.569, -18.30};
double CbarCC[5] = {-1.033, -15.95, -7.247, 1.569, -17.72};

double sigma(double E)
{
	// average over nu, nu bar
	// energy in GeV
	// valid for 4<eps<12
	double eps = log10(E);
	double sigma_nu, sigma_bar; // cm^2

	sigma_nu = sigma_helper(eps, CnuNC) + sigma_helper(eps, CnuCC);
	sigma_bar = sigma_helper(eps, CbarNC) + sigma_helper(eps, CbarCC);
	return (sigma_nu + sigma_bar) / 2.; // cm^2
}

double sigma_helper(double eps, double C[5])
{
	double l = log(eps - C[0]);
	return pow(10, C[1] + C[2] * l + C[3] * pow(l, 2) + C[4] / l);
}

double mean_density(double cos_zenith) // TODO: IMPROVE THIS with shells
{
	return 5.514; // g/cm^3
}

bool absorption_include(double E, double cos_zenith) // note that zenith is 90 + dec, so cos_zenith=-sin(dec)
{
	double max_dp = dpdcoszenith(E, 1);
	return rng.rand(max_dp) < dpdcoszenith(E, cos_zenith);
}

