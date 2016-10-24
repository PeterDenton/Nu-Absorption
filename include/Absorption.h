#ifndef Absorption_H
#define Absorption_H

// from 1102.0691 p 13

// E in GeV
double dpdcoszenith(double E, double cos_zenith);
double interaction_length(double E, double cos_zenith);
double sigma(double E);
double sigma_helper(double eps, double C[5]);
double mean_density(double cos_zenith);
bool absorption_include(double E, double cos_zenith);

#endif
