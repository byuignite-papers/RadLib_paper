#include "rad_planck_mean.h"
#include "rad_wsgg.h"
#include "rad_rcslw.h"
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

///////////////////////////////////////////////////////////////////////////////

int main() {

    //----------------- define parameters

    double T      = 2000.0;    // K
    double P      = 101325.0;  // atm
    double xH2O   = 0.8;       // xH2O=0.2 is roughly stoich. CH4/air products
    double xCO2   = 0.2;       // xCO2=0.1 is roughly stoich. CH4/air products
    double xCO    = 0.;
    double xCH4   = 0.;
    double fvsoot = 0.;

    vector<double> kabs_pm, kabs_wsgg, kabs_rcslw;
    vector<double> awts_pm, awts_wsgg, awts_rcslw;

    //----------------- create radiation objects

    rad *planckmean = new rad_planck_mean();
    rad *wsgg       = new rad_wsgg();
    rad *rcslw      = new rad_rcslw(4, P, T, xH2O, xCO2, xCO, fvsoot);
    rad *rc1        = new rad_rcslw(1, P, T, xH2O, xCO2, xCO, fvsoot);
    rad *rc8        = new rad_rcslw(8, P, T, xH2O, xCO2, xCO, fvsoot);
    rad *rc24       = new rad_rcslw(24, P, T, xH2O, xCO2, xCO, fvsoot);

    //----------------- compute absorption coefficients and weights

    // planckmean->get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_pm,    awts_pm);
    // wsgg->get_k_a(      T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_wsgg,  awts_wsgg);
    // rcslw->get_k_a(     T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_rcslw, awts_rcslw);

    int n_sim = 100;
    int skipped = 0;
    clock_t c1, c2;
    double d1, d2;
    double time;
    vector<double> pm_times, ws_times, rc_times, rc8_times, rc24_times;
    double ave = 0;


    //Planck Mean
    n_sim = 1000000;
    c1 = clock();
    for(int i=0; i<n_sim; i++) {
	    planckmean->get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_pm,    awts_pm);
	    // cout << " " << setw(6) << kabs_pm[0];
    }
    c2 = clock();
    d1 = c1;
    d2 = c2;
    time = (d2-d1)/CLOCKS_PER_SEC;
    ave = time/n_sim;
    cout << endl << "PM average time = " << ave ;

    // WSGG
    n_sim = 1000000;
    c1 = clock();
    for(int i=0; i<n_sim; i++) {
	    wsgg->get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_pm,    awts_pm);
	    // cout << " " << setw(6) << kabs_pm[0];
    }
    c2 = clock();
    d1 = c1;
    d2 = c2;
    time = (d2-d1)/CLOCKS_PER_SEC;
    ave = time/n_sim;
    cout << endl << "WSGG average time = " << ave ;

    // RCSLW - 4
    n_sim = 1000000;
    c1 = clock();
    for(int i=0; i<n_sim; i++) {
	    rcslw->get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_pm,    awts_pm);
	    // cout << " " << setw(6) << kabs_pm[0];
    }
    c2 = clock();
    d1 = c1;
    d2 = c2;
    time = (d2-d1)/CLOCKS_PER_SEC;
    ave = time/n_sim;
    cout << endl << "RCSLW average time = " << ave ;

    // RCSLW - 1
    n_sim = 1000000;
    c1 = clock();
    for(int i=0; i<n_sim; i++) {
	    rc1->get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_pm,    awts_pm);
	    // cout << " " << setw(6) << kabs_pm[0];
    }
    c2 = clock();
    d1 = c1;
    d2 = c2;
    time = (d2-d1)/CLOCKS_PER_SEC;
    ave = time/n_sim;
    cout << endl << "RCSLW 1gas average time = " << ave ;

    // RCSLW - 8
    n_sim = 1000000;
    c1 = clock();
    for(int i=0; i<n_sim; i++) {
	    rc8->get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_pm,    awts_pm);
	    // cout << " " << setw(6) << kabs_pm[0];
    }
    c2 = clock();
    d1 = c1;
    d2 = c2;
    time = (d2-d1)/CLOCKS_PER_SEC;
    ave = time/n_sim;
    cout << endl << "RCSLW 8gas average time = " << ave ;

    // RCSLW - 24
    n_sim = 1000000;
    c1 = clock();
    for(int i=0; i<n_sim; i++) {
	    rc24->get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_pm,    awts_pm);
	    // cout << " " << setw(6) << kabs_pm[0];
    }
    c2 = clock();
    d1 = c1;
    d2 = c2;
    time = (d2-d1)/CLOCKS_PER_SEC;
    ave = time/n_sim;
    cout << endl << "RCSLW 24gas average time = " << ave ;

    cout << endl;

    return 0;

    //----------------- cleanup

    delete planckmean;
    delete wsgg;
    delete rcslw;

}
