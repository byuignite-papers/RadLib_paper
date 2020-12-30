#include <iostream>
#include "rad_rcslw.h"
#include "rad_wsgg.h"
#include "rad_planck_mean.h"
#include "rad.h"

using namespace std;

void parallel_planes(rad                  *RAD,
                     const double         L,
                     const int            ntheta,
                     const double         P, 
                     const vector<double> &T,
                     const vector<double> &xH2O,
                     const vector<double> &xCO2,
                     const vector<double> &xCO,
                     const vector<double> &xCH4,
                     const vector<double> &fvsoot,
                     vector<double>       &q,
                     vector<double>       &Q,
                     vector<double>       &x,
                     vector<double>       &xQ,
                     const bool           LzeroIbc=false
                     );

///////////////////////////////////////////////////////////////////////////////

int main() {

    //--------------------- parameters

    double P      = 101325.0;
    double L      = 1.0;
    int    nGG    = 24;
    int    ntheta = 101;
    int    nx     = 1001;
    double Twall  = 800;

    int    nGGa   = nGG+1;

    double xco2=0.0, xco=0.0, xh2o=0.12, xch4=0.0, fvs=0.0;

    //---------------------

    vector<double> xCO2(nx, xco2);
    vector<double> xCO(nx, xco);
    vector<double> xH2O(nx, xh2o);
    vector<double> xCH4(nx, 0.0);
    vector<double> fvsoot(nx, fvs);

    vector<double> x(nx, 0.0);
    vector<double> xQ;
    vector<double> T(nx, Twall);

    double dx = L/(nx-1);
    x[0] = 0.0;
    double Tavg = T[0];
    double xH2O_avg = 0.0;
    for(int i=1; i<nx; ++i){
        x[i] = x[i-1] + dx;
        T[i] = 4000*x[i]*(L-x[i])/L/L + Twall;
        xH2O[i] = 0.8*x[i]*(L-x[i])/L/L + xh2o;
        Tavg += T[i];
        xH2O_avg += xH2O[i];
    }
    Tavg /= nx;
    xH2O_avg /= nx;


    rad *rc = new rad_rcslw(4, P, Tavg, xH2O_avg, xco2, xco, fvs);    
    rad *rc1 = new rad_rcslw(1, P, Tavg, xH2O_avg, xco2, xco, fvs);    
    rad *rc8 = new rad_rcslw(8, P, Tavg, xH2O_avg, xco2, xco, fvs);    
    rad *rc2 = new rad_rcslw(2, P, Tavg, xH2O_avg, xco2, xco, fvs);    
    rad *planckmean = new rad_planck_mean();
    rad *wsgg       = new rad_wsgg();
    //
	// ------- Timing setup
    int n_sim = 7;
    clock_t c1, c2;
    double d1, d2;
    double pm_time, ws_time, rc_time, rc1_time, rc8_time, rc2_time;
    double ave = 0;
    double q_arb = 0;

    //--------------------- get q, Q

    vector<double> q;    
    vector<double> Q;

    // ---- Planckmean

    c1 = clock();
    for(int i=0; i<n_sim; i++) {
	    parallel_planes(planckmean, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot, q, Q, x, xQ);
	    q_arb += q[0];
    }
    c2 = clock();
    d1 = c1;
    d2 = c2;
    ave = (d2-d1)/CLOCKS_PER_SEC / n_sim;
    pm_time = ave;
    cout << endl << "PM    time " << pm_time;
    // cout << endl << "q_arb" << q_arb;

    // ---- WSGG

    c1 = clock();
    for(int i=0; i<n_sim; i++) {
	    parallel_planes(wsgg, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot, q, Q, x, xQ);
	    q_arb += q[0];
    }
    c2 = clock();
    d1 = c1;
    d2 = c2;
    ave = (d2-d1)/CLOCKS_PER_SEC / n_sim;
    ws_time = ave;
    cout << endl << "WSGG  time " << ws_time;

    // ---- RCLSW

    c1 = clock();
    for(int i=0; i<n_sim; i++) {
	    parallel_planes(rc, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot, q, Q, x, xQ);
	    q_arb += q[0];
    }
    c2 = clock();
    d1 = c1;
    d2 = c2;
    ave = (d2-d1)/CLOCKS_PER_SEC / n_sim;
    rc_time = ave;
    cout << endl << "RCSLW time " << rc_time;

    // ---- RCLSW 1

    c1 = clock();
    for(int i=0; i<n_sim; i++) {
	    parallel_planes(rc1, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot, q, Q, x, xQ);
	    q_arb += q[0];
    }
    c2 = clock();
    d1 = c1;
    d2 = c2;
    ave = (d2-d1)/CLOCKS_PER_SEC / n_sim;
    rc1_time = ave;
    cout << endl << "RC 1  time " << rc1_time;

    // ---- RCLSW 8

    c1 = clock();
    for(int i=0; i<n_sim; i++) {
	    parallel_planes(rc8, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot, q, Q, x, xQ);
	    q_arb += q[0];
    }
    c2 = clock();
    d1 = c1;
    d2 = c2;
    ave = (d2-d1)/CLOCKS_PER_SEC / n_sim;
    rc8_time = ave;
    cout << endl << "RC 8  time " << rc8_time;

    // ---- WSGG

    c1 = clock();
    for(int i=0; i<n_sim; i++) {
	    parallel_planes(rc2, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot, q, Q, x, xQ);
	    q_arb += q[0];
    }
    c2 = clock();
    d1 = c1;
    d2 = c2;
    ave = (d2-d1)/CLOCKS_PER_SEC / n_sim;
    rc2_time = ave;
    cout << endl << "RC 2 time " << rc2_time;


    cout << endl << "q_arb" << q_arb;
    //-------------------------------------------------------------------------

    //cout << "# x (m), Q (kW/m3)";
    //for(int i=0; i<xQ.size(); ++i)
    //    cout << endl << xQ[i] << "  " << Q[i]/1000;

    //cout << "# x (m), q (kW/m2)";
    //for(int i=0; i<x.size(); ++i)
    //    cout << endl << x[i] << "  " << q[i]/1000;

    cout << endl;
    
    return 0;

}

