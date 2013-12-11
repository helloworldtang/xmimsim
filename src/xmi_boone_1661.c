/* Modified version of John M. Boone's code */
/* His code mentions no license whatsoever, so will assume it is in the public domain */
/* Tom Schoonjans 2013 */


/* --------------------------------------------------------------------------
File Name:     GENSPEC1.C
Author:        John M. Boone, Ph.D.    (jmboone@ucdavis.edu)
Date:          September 3, 1997

This file contains two subroutines, genspec1.c calls dc_spectral_model.c.
In addition to the normal *.h files, genspec1.h and mual.h are also needed
to compile this code.  Float variables here assume 4 bytes per value (32 bit),
double variables assume 8 bytes (64 bit), and INT variables are also 4 byte
(32 bit) integer variables.
-----------------------------------------------------------------------------
Description: 
============
This routine generates spectra (photons/mm**2 per E) for one mAs and
the output is calibrated to the output of a constant potential generator in 
our laboratory (a Toshiba Model 2050 x-ray generator with a "Rotanode"
x-ray tube with housing model DRX-573HD-S and insert model DR-5735H).
These spectra were calibrated to output (mR/mAs) values and HVL values
that were measured down the central axis of the x-ray beam.  The output
data are given in the manuscript, "An accurate method for computer-
generating tunsten anode x-ray spectra from 30 to 140 kV", JM Boone and 
JA Seibert, Medical Physics 23 or 24 (don't know at this time).
--------------------------------------------------------------------------- */

#include <math.h>
#include <xraylib.h>
#include "xmi_data_structs.h"
#include <stdio.h>
#include <stdlib.h>

static int nn[150]={
0,0,0,0,0,0,0,0,0,0,3,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,2,2,2,2,2,2,1,2,1,2,1,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};

static double aa[151][4]={
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{-2.470985e+000,+7.522494e-002,+1.601297e-004,+0.000000e+000},
{-5.468520e+001,+2.825971e+000,-3.702585e-002,+1.685450e-004},
{-1.149660e+002,+7.181666e+000,-1.041506e-001,+5.246942e-004},
{-2.023117e+001,+7.523026e+000,-9.725916e-002,+5.262351e-004},
{+3.440159e+002,+3.179575e+000,-3.306927e-002,+3.115530e-004},
{+5.493292e+002,+1.507932e+001,-9.656648e-002,+5.142380e-004},
{+1.032546e+003,+2.793458e+001,-1.517779e-001,+6.491026e-004},
{+1.056836e+003,+5.305293e+001,+4.006209e-002,-7.164506e-004},
{+1.098845e+003,+8.295003e+001,+3.061647e-001,-2.617126e-003},
{+4.957978e+002,+1.470037e+002,-1.102818e-001,-1.354507e-003},
{-1.437833e+002,+2.229100e+002,-6.206306e-001,+1.896847e-004},
{-1.106664e+003,+2.770497e+002,-5.743618e-001,-1.066210e-003},
{-2.281766e+003,+3.424422e+002,-5.793318e-001,-2.303580e-003},
{-5.591722e+003,+4.724134e+002,-1.429958e+000,+5.049076e-004},
{-9.340535e+003,+6.186368e+002,-2.407872e+000,+3.701711e-003},
{-1.406504e+004,+7.760495e+002,-3.430400e+000,+6.646413e-003},
{-1.920322e+004,+9.418671e+002,-4.544806e+000,+9.920156e-003},
{-2.515954e+004,+1.130912e+003,-5.997636e+000,+1.441550e-002},
{-3.151928e+004,+1.331120e+003,-7.556880e+000,+1.925802e-002},
{-3.165938e+004,+1.293120e+003,-6.625241e+000,+1.593667e-002},
{-3.197696e+004,+1.259429e+003,-5.721722e+000,+1.269609e-002},
{-3.150203e+004,+1.213018e+003,-4.995401e+000,+1.068630e-002},
{-3.404540e+004,+1.273283e+003,-5.440755e+000,+1.275048e-002},
{-3.525747e+004,+1.267165e+003,-5.052590e+000,+1.140252e-002},
{-3.659796e+004,+1.264495e+003,-4.698218e+000,+1.017435e-002},
{-3.935522e+004,+1.325721e+003,-5.260133e+000,+1.251165e-002},
{-4.239447e+004,+1.396684e+003,-5.961586e+000,+1.539180e-002},
{-4.505477e+004,+1.445302e+003,-6.324550e+000,+1.657817e-002},
{-4.807436e+004,+1.506528e+003,-6.841015e+000,+1.832282e-002},
{-4.772176e+004,+1.455009e+003,-6.183720e+000,+1.609850e-002},
{-4.687265e+004,+1.383587e+003,-5.296423e+000,+1.305337e-002},
{-4.534002e+004,+1.304458e+003,-4.458635e+000,+1.029127e-002},
{-4.729671e+004,+1.337299e+003,-4.768113e+000,+1.129840e-002},
{-4.592165e+004,+1.239852e+003,-3.651701e+000,+7.505117e-003},
{-4.417617e+004,+1.131552e+003,-2.422704e+000,+3.340713e-003},
{-4.975325e+004,+1.307914e+003,-4.490898e+000,+1.093279e-002},
{-5.613191e+004,+1.511968e+003,-6.875300e+000,+1.962943e-002},
{-5.524074e+004,+1.421870e+003,-5.669106e+000,+1.487642e-002},
{-5.449938e+004,+1.337319e+003,-4.527925e+000,+1.035718e-002},
{-5.884185e+004,+1.478833e+003,-6.293272e+000,+1.687622e-002},
{-6.310984e+004,+1.616216e+003,-8.009326e+000,+2.321589e-002},
{-5.995594e+004,+1.496680e+003,-6.906032e+000,+1.977848e-002},
{-5.964100e+004,+1.456697e+003,-6.534316e+000,+1.853666e-002},
{-6.132553e+004,+1.489142e+003,-6.956800e+000,+2.005068e-002},
{-6.304895e+004,+1.522434e+003,-7.390895e+000,+2.161122e-002},
{-5.994340e+004,+1.380871e+003,-5.839743e+000,+1.619943e-002},
{-5.610868e+004,+1.218272e+003,-4.092096e+000,+1.018410e-002},
{-1.825729e+004,-1.382119e+002,+9.557819e+000,-2.140051e-002},
{+2.220017e+004,-1.568661e+003,+2.389806e+001,-5.505689e-002},
{+5.501707e+004,-2.721157e+003,+3.527805e+001,-8.047399e-002},
{+8.922944e+004,-3.915854e+003,+4.704985e+001,-1.070557e-001},
{+2.104991e+004,-1.557364e+003,+2.321886e+001,-5.134972e-002},
{-5.076517e+004,+9.032211e+002,-1.579828e+000,+7.306299e-003},
{-6.030789e+004,+1.202068e+003,-4.552311e+000,+1.419530e-002},
{-6.984994e+004,+1.499854e+003,-7.513087e+000,+2.103801e-002},
{-7.108636e+004,+1.507313e+003,-7.472137e+000,+2.024801e-002},
{-7.327537e+004,+1.540893e+003,-7.689933e+000,+2.028554e-002},
{-3.161176e+004,+1.297773e+002,+6.392479e+000,-1.693738e-002},
{+1.036295e+004,-1.288012e+003,+2.051981e+001,-5.423905e-002},
{-4.132485e+004,+4.420904e+002,+2.448595e+000,+2.202247e-005},
{-9.983141e+004,+2.351143e+003,-1.722188e+001,+5.896824e-002},
{-8.345827e+004,+1.820261e+003,-1.140761e+001,+3.474510e-002},
{-6.038053e+004,+1.099142e+003,-3.836391e+000,+5.215208e-003},
{-7.332230e+004,+1.472738e+003,-7.481134e+000,+1.644730e-002},
{-8.866886e+004,+1.911744e+003,-1.172736e+001,+2.948703e-002},
{-8.906282e+004,+1.903695e+003,-1.166640e+001,+2.953372e-002},
{-9.122084e+004,+1.949906e+003,-1.212404e+001,+3.119028e-002},
{-9.195919e+004,+1.956641e+003,-1.222022e+001,+3.155684e-002},
{-9.393503e+004,+1.997570e+003,-1.264453e+001,+3.294245e-002},
{-9.460591e+004,+1.985575e+003,-1.240631e+001,+3.188458e-002},
{-9.465909e+004,+1.947305e+003,-1.191912e+001,+3.005542e-002},
{-1.054958e+005,+2.287738e+003,-1.546565e+001,+4.192772e-002},
{-1.128820e+005,+2.523280e+003,-1.806383e+001,+5.099440e-002},
{-5.652375e+004,+8.460812e+002,-1.890296e+000,+0.000000e+000},
{-6.253113e+004,+9.546213e+002,-2.421458e+000,+0.000000e+000},
{-6.063249e+004,+9.093265e+002,-2.222830e+000,+0.000000e+000},
{-5.839087e+004,+8.581494e+002,-1.999379e+000,+0.000000e+000},
{-6.177439e+004,+9.096954e+002,-2.219623e+000,+0.000000e+000},
{-6.551339e+004,+9.674375e+002,-2.466158e+000,+0.000000e+000},
{-6.482105e+004,+9.463755e+002,-2.384063e+000,+0.000000e+000},
{-6.396586e+004,+9.225355e+002,-2.290526e+000,+0.000000e+000},
{-5.976377e+004,+8.384694e+002,-1.918134e+000,+0.000000e+000},
{-5.483239e+004,+7.418415e+002,-1.492676e+000,+0.000000e+000},
{-5.545914e+004,+7.392220e+002,-1.466754e+000,+0.000000e+000},
{-5.191874e+004,+6.677125e+002,-1.159438e+000,+0.000000e+000},
{-5.337262e+004,+6.864440e+002,-1.248563e+000,+0.000000e+000},
{-5.499713e+004,+7.080823e+002,-1.349865e+000,+0.000000e+000},
{-6.109855e+004,+8.103042e+002,-1.805236e+000,+0.000000e+000},
{-6.780313e+004,+9.224389e+002,-2.301017e+000,+0.000000e+000},
{-6.463570e+004,+8.536160e+002,-1.980542e+000,+0.000000e+000},
{-6.142322e+004,+7.841977e+002,-1.658250e+000,+0.000000e+000},
{-6.542573e+004,+8.551263e+002,-1.999140e+000,+0.000000e+000},
{-6.850218e+004,+9.104404e+002,-2.275249e+000,+0.000000e+000},
{-6.775178e+004,+8.733046e+002,-2.050653e+000,+0.000000e+000},
{-5.670986e+004,+6.717305e+002,-1.174642e+000,+0.000000e+000},
{-6.431161e+004,+7.982173e+002,-1.730212e+000,+0.000000e+000},
{-7.284777e+004,+9.397040e+002,-2.345359e+000,+0.000000e+000},
{-7.296366e+004,+9.370416e+002,-2.349089e+000,+0.000000e+000},
{-7.251969e+004,+9.256901e+002,-2.318580e+000,+0.000000e+000},
{-7.373791e+004,+9.387560e+002,-2.371741e+000,+0.000000e+000},
{-7.522138e+004,+9.557057e+002,-2.440560e+000,+0.000000e+000},
{-6.645010e+004,+8.129935e+002,-1.892077e+000,+0.000000e+000},
{-5.391723e+004,+6.111141e+002,-1.110798e+000,+0.000000e+000},
{-6.950106e+004,+8.381854e+002,-1.943843e+000,+0.000000e+000},
{-7.656837e+004,+9.340291e+002,-2.272803e+000,+0.000000e+000},
{-7.169818e+004,+8.562692e+002,-1.994058e+000,+0.000000e+000},
{-6.307650e+004,+7.199495e+002,-1.490337e+000,+0.000000e+000},
{-6.896102e+004,+8.014658e+002,-1.785938e+000,+0.000000e+000},
{-7.948799e+004,+9.545463e+002,-2.356450e+000,+0.000000e+000},
{-8.038940e+004,+9.603943e+002,-2.368062e+000,+0.000000e+000},
{-8.186549e+004,+9.744751e+002,-2.411129e+000,+0.000000e+000},
{-8.127234e+004,+9.784392e+002,-2.501457e+000,+0.000000e+000},
{-6.447853e+004,+7.327550e+002,-1.638994e+000,+0.000000e+000},
{-3.806982e+004,+3.131658e+002,+0.000000e+000,+0.000000e+000},
{-3.797812e+004,+3.101094e+002,+0.000000e+000,+0.000000e+000},
{-4.023389e+004,+3.255209e+002,+0.000000e+000,+0.000000e+000},
{-4.280943e+004,+3.432826e+002,+0.000000e+000,+0.000000e+000},
{-4.114666e+004,+3.272756e+002,+0.000000e+000,+0.000000e+000},
{-3.925966e+004,+3.096545e+002,+0.000000e+000,+0.000000e+000},
{+3.191650e+002,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{-4.425804e+004,+3.425401e+002,+0.000000e+000,+0.000000e+000},
{+8.115607e+001,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{-3.867988e+004,+2.969811e+002,+0.000000e+000,+0.000000e+000},
{+1.306709e+003,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+1.153422e+003,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+9.817065e+002,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+8.099662e+002,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+6.688839e+002,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+5.277812e+002,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+3.498336e+002,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+1.718605e+002,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
{+0.000000e+000,+0.000000e+000,+0.000000e+000,+0.000000e+000},
};

/* -----------------------------------------------------------------------------
The following code generates an x-ray spectrum based in the input kV, added 
aluminum filtration, and voltage ripple (in percent). 
Inputs:
   kvolt:  The kilovoltage of the x-ray spectrum to be generated
   ripple: The kilovoltage waveform ripple factor, in percent (0.0 to 100.0)
Output:
    spec[]: An array containing the generated spectrum, with the keV
    corresponding to the index number.  For example, spec[50] contains the 
    the x-ray photon fluence (photons/mm**2) for that spectrum in the energy
    region from 49.5 to 50.5 keV.
----------------------------------------------------------------------------- */

static int dc_spectral_model(double kvolt, double spec[151]);

static int genspec1(double kvolt, double ripple, double spec[151])
{
	double xkv,xspec[151];
	double pi,kva,kvb,dkv,kv,x,factor,p;
	int i,j,k,iphase,np;

	if (kvolt < 30.0 || kvolt > 140.0) {
		fprintf(stderr,"Illegal tube voltage detected in genspec1\nOnly values between 30.0 and 140.0 keV are accepted\n");
		return 0;
	}
	if (ripple < 0.0 || ripple > 100.0) {
		fprintf(stderr, "Illegal generator ripple value detected in genspec1\nOnly values between 0.0 and 100.0 are accepted\n");	
		return 0;
	}
	if( ripple==0.0 ) {
		dc_spectral_model( kvolt,spec );
		return 1;		
		}
	pi = 3.1415926535;
	kva = kvolt;
	dkv = kva * ripple * 0.01;
	kvb = kvolt - dkv;
	for( i=0; i<=150; ++i ) {
		spec[i] = 0.0;
		}
	np = 20;
	p = np;
	for( iphase=1; iphase<=np; ++iphase ) {
		x = (pi/p) * iphase;
		factor = fabs( sin( x ) );
		kv = kvb + dkv * factor;
		dc_spectral_model( kv,xspec);
		for( i=0; i<=150; ++i ) {
			spec[i] += xspec[i];
			}
		}
	for( i=0; i<=150; ++i ) {
		spec[i] = spec[i] / p;
		}
	return 1;
}

/* -----------------------------------------------------------------------------
The following code, dc_spectral_model, generates raw spectra with DC waveform
characteristics.  
Inputs:
    kvolt:  The kilovoltage ranging from 30 to 140 kV
Output:
    spec[]: An array containing the generated spectrum, with the keV
    corresponding to the index number.  For example, spec[50] contains the 
    the x-ray photon fluence (photons/mm**2) for that spectrum in the energy
    region from 49.5 to 50.5 keV.
----------------------------------------------------------------------------- */

static int dc_spectral_model(double kvolt,double spec[151])
{
	double arg;
	double mr,xval,x,sum,factor;
	int ien,nterms,nt,iemax,kv,ikv;
	int i,j,k,l,m,n,ians,ival,npts,kpts,nx,ny,kans;
	x = kvolt;
	kv = kvolt;
	for( ien=0; ien<=150; ++ien ) spec[ien] = 0.0;
	for( ien=10; ien<=(kv+3); ++ien ) {
		sum = aa[ien][0];
		arg = x;
		for( j=1; j<nn[ien]; ++j ) {
			sum = sum + aa[ien][j] * arg;
			arg = arg * x;
			}
		if( sum < 0.0 ) sum = 0.0;
		spec[ien] = sum;
		}
	return 1;
}

int xmi_tube_boone_1661(struct xmi_layer *tube_window, struct xmi_layer *tube_filter,
		  double tube_ripple, double tube_voltage,
		  double tube_current, double tube_solid_angle, 
		  struct xmi_excitation **boone_spectrum
		  ) {
	double spec[151];
	struct xmi_excitation *boone_spectrum_local = NULL;
	int i;
	const double mm_square_to_sterad = 4.0 * atan(1.0/2000.0/sqrt(4.0*1000.0*1000.0 + 1.0 + 1.0));


	if (genspec1(tube_voltage, tube_ripple, spec) == 0) {
		return 0;
	}

	boone_spectrum_local = (struct xmi_excitation *) malloc(sizeof(struct xmi_excitation));

	boone_spectrum_local->n_discrete = 0;
	boone_spectrum_local->discrete = NULL;
	boone_spectrum_local->n_continuous= 0;
	boone_spectrum_local->continuous = NULL;

	for (i = 0 ; i < 150 ; i++) {
		double intensity = spec[i];
		if (intensity == 0.0)
			continue;

		intensity /= mm_square_to_sterad;
		intensity *= tube_solid_angle;
		intensity *= tube_current;
		if (tube_window) {
			intensity *= exp(-1.0 * tube_window->density * CS_Total_Kissel(tube_window->Z[0], (float) i) * tube_window->thickness);
		}

		if (tube_filter) {
			intensity *= exp(-1.0 * tube_filter->density * CS_Total_Kissel(tube_filter->Z[0], (float) i) * tube_filter->thickness);
		}

		if (intensity <= 0.0)
			continue;

		boone_spectrum_local->continuous = realloc(boone_spectrum_local->continuous, sizeof(struct xmi_energy_continuous)*++boone_spectrum_local->n_continuous);
		boone_spectrum_local->continuous[boone_spectrum_local->n_continuous-1].energy = (double) i;
		boone_spectrum_local->continuous[boone_spectrum_local->n_continuous-1].horizontal_intensity = 
		boone_spectrum_local->continuous[boone_spectrum_local->n_continuous-1].vertical_intensity = intensity/2.0;
		boone_spectrum_local->continuous[boone_spectrum_local->n_continuous-1].sigma_x = 
		boone_spectrum_local->continuous[boone_spectrum_local->n_continuous-1].sigma_xp = 
		boone_spectrum_local->continuous[boone_spectrum_local->n_continuous-1].sigma_y = 
		boone_spectrum_local->continuous[boone_spectrum_local->n_continuous-1].sigma_yp = 0.0;
	}

	*boone_spectrum = boone_spectrum_local;
	return 1;
}
