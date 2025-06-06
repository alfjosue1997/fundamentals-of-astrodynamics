#ifndef _AstroLib_h_
#define _AstroLib_h_
/* --------------------------------------------------------------------
*
*                                AstroLib.h
*
*    this file contains miscallaneous two-body motion functions. Several areas are covered:
*    coordinate transformations, 2body routines, jpl ephemeris conversions, covariance operations
*
*    current :
*              30 sep 15  david vallado
*                           fix jd, jdfrac
*    changes :
*               3 nov 14  david vallado
*                           update to msvs2013 c++
*               4 may 09  david vallado
*                           misc updates
*              23 feb 07  david vallado
*                           3rd edition baseline
*               6 dec 05  david vallado
*                           add ijk2ll
*              20 jul 05  david vallado
*                           2nd printing baseline
*              14 may 01  david vallado
*                           2nd edition baseline
*              23 nov 87  david vallado
*                           original baseline
  ----------------------------------------------------------------------      */

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <stdint.h>

  // be sure to update to your specific paths!!
  // " " tells the compiler to look in this directory first, usually the parent directory
  // you can leave generic as MathTimeLib.h, but you have to set the include directory in the property pages
#include "D:/Codes/LIBRARY/CPP/Libraries/MathTimeLib/MathTimeLib/MathTimeLib.h"  // globals, edirection
#include "D:/Codes/LIBRARY/CPP/Libraries/eopspw/eopspw/eopspw.h"  // eopdata, spwdata, eopsize, spwsize


#pragma once

typedef enum
{
	e80,
	e96,
	e06a,
	e06b,
	e06cio
} eOpt;


const int jpldesize = 60000; // 60000 if from 1957-2100

typedef struct jpldedata
{
	double rsun[3], rmoon[3];
	int    year, mon, day;
	double rsmag, rmmag, mjd;
} jpldedata;



// setup variations on equinoctial elements
typedef enum
{
	ea_m, en_m, ep_m, ea_nu, en_nu, ep_nu
} equintype;



namespace AstroLib
{
// note these should be consistent with each gravity field used, here, EGM-08
#define mum 3.986004415e14        // m^3/s^2 stk uses .4415
#define mu 398600.4415            // km^3/s^2 stk uses .4415
#define re 6378.1363              // km  stk uses .1363
#define velkmps 7.905366149846074
#define earthrot 7.292115e-05  // 7.29211514670698e-05 older rad/s
#define speedoflight 2.99792458e8       // speed of light m/s

	void sethelp
	(
		char& iauhelp, char iauopt
	);


	// -----------------------------------------------------------------------------------------
	//                                       Coordinate system functions
	// -----------------------------------------------------------------------------------------

	void ddpsiddeps_dxdy
	(
		double ttt, double& ddpsi, double& ddeps,
		MathTimeLib::edirection direct,
		double& dx, double& dy
	);

	void gstime00
	(
		double jdut1, double deltapsi, double ttt, const iau06data& iau06arr, double fArgs[13], double& gst,
		std::vector< std::vector<double> >& st
	);

	double  gstime
	(
		double jdut1
	);

	void    lstime
	(
		double lon, double jdut1, double& lst, double& gst
	);


	void fundarg
	(
		double ttt, eOpt opt,
		double fArgs[13]
	);

	void iau06xysS
	(
		double ttt,
		const iau06data& iau06arr,
		double fArgs[14],
		double& x, double& y, double& s
	);

	void iau06xys
	(
		double jdtt, double ttt, double ddx, double ddy, char interp,
		const iau06data& iau06arr, double fArgs[14], double jdxysstart,
		double& x, double& y, double& s,
		std::vector< std::vector<double> >& nut
	);

	void iau06pn
	(
		double ttt, double ddx, double ddy, eOpt opt,
		iau06data &iau06arr,
		double x, double y, double s,
		std::vector< std::vector<double> > &nut
	);

	void precess
	(
		double ttt, eOpt opt,
		double& psia, double& wa, double& epsa, double& chia,
		std::vector< std::vector<double> > &prec
	);

	void nutation
	(
		double ttt, double ddpsi, double ddeps,
		const iau80data& iau80arr, eOpt opt, double fArgs[14],
		double& deltapsi, double& deltaeps, double& trueeps, double& meaneps, 
		std::vector< std::vector<double> >& nut
	);

	void precnutbias00a
	(
		double ttt, double ddpsi, double ddeps,
		const iau06data& iau06arr, eOpt opt, double fArgs[14],
		std::vector< std::vector<double> >& tm
	);
		
	void sidereal
	(
		double jdut1, double deltapsi, double meaneps, double fArgs[14],
		double lod, int eqeterms, eOpt opt,
		std::vector< std::vector<double> >& st,
		std::vector< std::vector<double> >& stdot
	);

	void polarm
	(
		double xp, double yp, double ttt, eOpt opt, std::vector< std::vector<double> > &pm
	);

	void framebias
	(
		char opt,
		double& term1, double& term2, double& term3, std::vector< std::vector<double> > &fb
	);

	void eci_ecef
	(
		double reci[3], double veci[3], double aeci[3],
		MathTimeLib::edirection direct,
		double recef[3], double vecef[3], double aecef[3],
		eOpt opt,
		const iau80data& iau80arr, const iau06data& iau06arr,
		double jdtt, double jdftt, double jdut1, double jdxysstart,
		double lod, double xp, double yp, double ddpsi, double ddeps, double ddx, double ddy,
		std::vector< std::vector<double> >& trans
	);

	void itrf_j2k
	(
		double ritrf[3], double vitrf[3], double aitrf[3],
		MathTimeLib::edirection direct,
		double rj2k[3], double vj2k[3], double aj2k[3],
		const iau80data& iau80rec, eOpt opt,
		double ttt, double jdut1, double lod,
		double xp, double yp, int eqeterms,
		std::vector< std::vector<double> >& trans
	);

	void eci_pef
	(
		double reci[3], double veci[3], double aeci[3],
		MathTimeLib::edirection direct,
		double rpef[3], double vpef[3], double apef[3],
		const iau80data& iau80arr, const iau06data& iau06arr, eOpt opt,
		double jdtt, double jdftt, double jdut1, double jdxysstart, double lod, int eqeterms,
		double ddpsi, double ddeps, double ddx, double ddy
	);

	void eci_tod
	(
		double reci[3], double veci[3], double aeci[3],
		MathTimeLib::edirection direct,
		double rtod[3], double vtod[3], double atod[3],
		const iau80data& iau80arr, const iau06data& iau06arr, eOpt opt,
		double jdtt, double jdftt, double jdut1, double jdxysstart, double ddpsi, double ddeps, double ddx, double ddy
	);

	void eci_mod
	(
		double rmod[3], double vmod[3], double amod[3],
		MathTimeLib::edirection direct,
		double reci[3], double veci[3], double aeci[3], eOpt opt,
		double ttt, double jdut1
	);



	void ecef_mod
	(
		double ritrf[3], double vitrf[3], double aitrf[3],
		MathTimeLib::edirection direct,
		double rmod[3], double vmod[3], double amod[3],
		const iau80data &iau80rec, eOpt opt,
		double ttt, double jdut1, double lod, double xp,
		double yp, int eqeterms, double ddpsi, double ddeps,
		std::vector< std::vector<double> > &trans
	);

	void ecef_tod
	(
		double ritrf[3], double vitrf[3], double aitrf[3],
		MathTimeLib::edirection direct,
		double rtod[3], double vtod[3], double atod[3],
		const iau80data &iau80rec, eOpt opt,
		double ttt, double jdut1, double lod, double xp,
		double yp, int eqeterms, double ddpsi, double ddeps,
		std::vector< std::vector<double> > &trans
	);

	void ecef_pef
	(
		double ritrf[3], double vitrf[3], double aitrf[3],
		MathTimeLib::edirection direct,
		double rpef[3], double vpef[3], double apef[3],
		double ttt, double xp, double yp,
		std::vector< std::vector<double> > &trans
	);


	void teme_eci
	(
		double rteme[3], double vteme[3], double ateme[3],
		MathTimeLib::edirection direct,
		double rgcrf[3], double vgcrf[3], double agcrf[3],
		const iau80data &iau80rec, eOpt opt,
		double ttt, double ddpsi, double ddeps
	);

	void teme_ecef
	(
		double rteme[3], double vteme[3], double ateme[3],
		MathTimeLib::edirection direct,
		double recef[3], double vecef[3], double aecef[3],
		double ttt, double jdut1, double lod, double xp, double yp, int eqeterms
	);



	// -----------------------------------------------------------------------------------------
	//                                       2-body functions
	// -----------------------------------------------------------------------------------------

	void rv2coe
	(
		double r[3], double v[3],
		double& p, double& a, double& ecc, double& incl, double& raan, double& argp,
		double& nu, double& m, double& eccanom, double& arglat, double& truelon, double& lonper
	);

	void coe2rv
	(
		double p, double ecc, double incl, double raan, double argp, double nu,
		double arglat, double truelon, double lonper,
		double r[3], double v[3]
	);

	void rv2eq
	(
		double r[3], double v[3],
		double& a, double& n, double& af, double& ag, double& chi, double& psi, double& meanlonM, double& meanlonNu, int& fr
	);

	void eq2rv
	(
		double a, double af, double ag, double chi, double psi, double meanlon, int fr,
		double r[3], double v[3]
	);

	void eq2coe
	(
		double x1in, double af, double ag, double chi, double psi, double x2in, int fr, equintype typeorbit,
		double& p, double& ecc, double& incl, double& raan, double& argp, double& nu, double& m, double& eccanom, double& arglat, double& truelon, double& lonper
	);

	void findc2c3
	(
		double znew,
		double& c2new, double& c3new
	);

	void findfandg
	(
		double r1[3], double v1[3], double r2[3], double v2[3], double dtsec,
		double x, double c2, double c3, double z,
		int opt,
		double& f, double& g, double& fdot, double& gdot
	);

	void checkhitearth
	(
		double altPad, double r1[3], double v1t[3], double r2[3], double v2t[3], int nrev, char& hitearth
	);

	void checkhitearthc
	(
		double altPadc, double r1c[3], double v1tc[3], double r2c[3], double v2tc[3], int nrev, char& hitearth
	);

	void kepler
	(
		double ro[3], double vo[3], double dtseco, double r[3], double v[3]
	);

	void pkepler
	(
		double r1[3], double v1[3], double& dtsec, double& ndot, double& nddot, double r2[3], double v2[3]
	);

	void rv2rsw
	(
		double r[3], double v[3],
		double rrsw[3], double vrsw[3], std::vector< std::vector<double> > &transmat
	);

	void rv2pqw
	(
		double r[3], double v[3],
		double rpqw[3], double vpqw[3]
	);

	void rv2ntw
	(
		double r[3], double v[3],
		double rntw[3], double vntw[3], std::vector< std::vector<double> > &transmat
	);

	void newtone
	(
		double ecc, double e0, double& m, double& nu
	);
		
	void newtonm
	(
		double ecc, double m, double& e0, double& nu
	);

	void newtonnu
	(
		double ecc, double nu,
		double& e0, double& m
	);

	void gc_gd
	(
		double&    latgc,
		MathTimeLib::edirection direct,
		double&    latgd
	);

	void checkhitearth
	(
		double altPad, double r1[3], double v1t[3], double r2[3], double v2t[3], int nrev, char& hitearth
	);

	void checkhitearthc
	(
		double altPadc, double r1c[3], double v1tc[3], double r2c[3], double v2tc[3], int nrev, char& hitearth
	);

	void ecef2ll
	(
		double recef[3],
		double& latgc, double& latgd, double& lon, double& hellp
	);


	void ecef2llb
	(
		double recef[3],
		double& latgc, double& latgd, double& lon, double& hellp
	);

	void initjplde
	(
		std::vector<jpldedata> &jpldearr,
		char infilename[140],
		double& jdjpldestart, double& jdjpldestartFrac
	);

	void findjpldeparam
	(
		double  jdtdb, double jdtdbF, char interp,
		const std::vector<jpldedata> &jpldearr,
		double jdjpldestart,
		double rsun[3], double& rsmag,
		double rmoon[3], double& rmmag
	);

	void sun
	(
		double jdtdb, double jdtdbF,
		double rsun[3], double& rtasc, double& decl
	);

	void sunmoonjpl
	(
		double jdtdb, double jdtdbF,
		char interp,
		const std::vector<jpldedata> &jpldearr,
		double jdjpldestart,
		double rsun[3], double& rtascs, double& decls,
		double rmoon[3], double& rtascm, double& declm
	);

	void moon
	(
		double jdtdb, double jdtdbF,
		double rmoon[3], double& rtasc, double& decl
	);

	// IOD type routines
	void site
	(
		double latgd, double lon, double alt,
		double rsecef[3], double vsecef[3]
	);

	/* ------------------------ angles-only techniques -------------------------- */
	void anglesgauss
	(
		double tdecl1, double tdecl2, double tdecl3,
		double trtasc1, double trtasc2, double trtasc3,
		double jd1, double jd2, double jd3,
		double rs1[3], double rs2[3], double rs3[3], double r2[3], double v2[3]
	);

	//void angleslaplace
	//    (
	//      double, double, double, double, double, double, double, double, double,
	//      double[], double[], double[], double[], double[]
	//    );

	/* ------------------------- conversion techniques -------------------------- */
	void radec_azel
	(
		double& rtasc, double& decl, double& lst, double& latgd,
		MathTimeLib::edirection direct,
		double& az, double& el
	);

	void radec_elatlon
	(
		double& rtasc, double& decl,
		MathTimeLib::edirection direct,
		double& ecllat, double& ecllon
	);

	void rv_elatlon
	(
		double rijk[3], double vijk[3],
		MathTimeLib::edirection direct,
		double& rr, double& ecllat, double& ecllon,
		double& drr, double& decllat, double& decllon
	);

	void rv_radec
	(
		double rijk[3], double vijk[3], 
		MathTimeLib::edirection direct,
		double& rr, double& rtasc, double& decl, double& drr, double& drtasc, double& ddecl
	);

	void rv_razel
	(
		double recef[3], double vecef[3], double latgd, double lon, double alt,
		MathTimeLib::edirection direct,
		double& rho, double& az, double& el, double& drho, double& daz, double& del
	);

	void rv_tradec
	(
		double rijk[3], double vijk[3], double rsijk[3],
		MathTimeLib::edirection direct,
		double& rho, double& trtasc, double& tdecl,
		double& drho, double& dtrtasc, double& dtdecl
	);

	void rvsez_razel
	(
		double rhosez[3], double drhosez[3],
		MathTimeLib::edirection direct,
		double& rho, double& az, double& el, double& drho, double& daz, double& del
	);

	void gibbs
	(
		double r1[3], double r2[3], double r3[3],
		double v2[3], double& theta, double& theta1, double& copa, char error[15]
	);

	void herrgibbs
	(
		double r1[3], double r2[3], double r3[3], double jd1, double jd2, double jd3,
		double v2[3], double& theta, double& theta1, double& copa, char error[15]
	);

	void lambertumins
	(
		double r1[3], double r2[3], int nrev, char dm,
		double& kbi, double& tof
	);

	void lambertminT
	(
		double r1[3], double r2[3], char dm, char de, int nrev,
		double& tmin, double& tminp, double& tminenergy
	);

	void lambertuniv
	(
		double r1[3], double r2[3], double v1[3], char dm, char de, int nrev, double dtsec, double tbi, double altpad,
		double v1t[3], double v2t[3], char& hitearth, int& error, FILE *outfile
	);

	void lambhodograph
	(
		double r1[3], double r2[3], double v1[3], double p, double ecc, double dnu, double dtsec,
		double v1t[3], double v2t[3]
	);

	static double kbattin(double v);

	static double seebattin(double v2);

	void lambertbattin
	(
		double r1[3], double r2[3], double v1[3], char dm, char de, int nrev, double dtsec, double altpad,
		double v1t[3], double v2t[3], char& hitearth, int& error, FILE *outfile
	);

	void target
	(
		double rint[3], double vint[3], double rtgt[3], double vtgt[3],
		char dm, char df, char kind, double dtsec,
		double v1t[3], double v2t[3], double dv1[3], double dv2[3], int error
	);


	// -----------------------------------------------------------------------------------------
	//                                       covariance functions
	// -----------------------------------------------------------------------------------------



	// -----------------------------------------------------------------------------------------
	//                                       perturbed functions
	// -----------------------------------------------------------------------------------------



};  // namespace

#endif