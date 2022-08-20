#pragma once
/************************************************************************************************/
/*** Topic: Dynamic Runge-Kutta 4th Order Method application in the class for each step       ***/
/***         whitout time dependent							                                  ***/
/***        solved numerically using RungeKutta 4th order method with adaptive time step size ***/
/***           Explosive synchronization in interlayer phase-shifted Kuramoto oscillators on  ***/
/***             multiplex networks     --Sarika Jalan--                                      ***/
/*** Version Release 17.12 rev 11256                                                Ali-Seif  ***/
/*** Date: 8/19/2022                                                                          ***/
/*** Code implemented in Microsoft Visual Studio Enterprise 2019 C++ compiler                 ***/
/*** MSI: PX60 6QD/ DDR4                                                                      ***/
/*** Run under a Intel� Core� i7-6700HQ CPU @ 2.60GHz � 64 based processor with 16 GB RAM     ***/
/*** in the computational server manual parallel                                              ***/
/************************************************************************************************/
/*#include"RK4.h"                                                            //import library Kuramoto

int main() {                                                                    //Beginning main
    int Number = 10;
    double t_last= 4.0, dt_min= 0.001, y_tol= 0.001, dy_min= 0.008, dy_max= 0.01;
    RK4 RK(Number,t_last, dt_min, y_tol, dy_min, dy_max);
    double* y = new double[Number]; //Making zerro Array y[0,Number-1]=0
    double* dt = new double[Number]; //Making zerro Array y[0,Number-1]=0.01
    for (int i = 0; i < Number;i++) { dt[i] = 0.01; y[i] = 0;}
    y = RK.DRK4(dt, y);//double (dt,y) //Dynamic Runge-Kutta 4th Order
    cout << y[5] << endl;
    
    //y= RK.CRK4(dt, y);//double (dt,y)  //Constant Runge-Kutta 4th Order
    //cout << y[5] << endl;


    return 0;                                                                   //run program was correct
}            */





//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include<iostream>                                                              //for cout                              //$$$$
#include<fstream>                                                               //infile /ofstream                      //$$$$
using namespace std;                                                                                                    //$$$$
double mfun(double y)                                                                                                   //$$$$
{                                                                                                                       //$$$$
    //double mf =y-y+5; //for this example t_last=40                                                                    //$$$$
    double mf = exp(y) - y*exp(y); //for this example t_last=4                                                          //$$$$
    return mf;                                                                                                          //$$$$
}                                                                                                                       //$$$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@                                                                                @@@@
//@@@                                class Kuramoto                                  @@@@
//@@@                                                                                @@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
class RK4 {                                                                //create and define class 
private:                                                                        //private values
    int Number;
    double t_last;                                                                  //step lenth
    double dt_min;                                                              //time final
    double y_tol;                                                            //stringh cupling
    double dy_min;
    double dy_max;
public:                                                                         //public values
    RK4                                                                    //
    (int Number_,double t_last_, double dt_min_, double y_tol_, double dy_min_, double dy_max_) ://input data in class
        Number(Number_),t_last(t_last_), dt_min(dt_min_), y_tol(y_tol_), dy_min(dy_min_), dy_max(dy_max_) {//change name input to privet


    }
    double* DRK4(double*,double*);      //Dynamic Runge-Kutta 4th Order
    double* CRK4(double*, double*);     //Constant Runge-Kutta 4th Order

};



//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//$$$$$                                                                                                                  $$$$$
//$$$$$                                                    DRK4                                                          $$$$$
//$$$$$                                                                                                                  $$$$$
double* RK4::DRK4(double* dt,double* y) {                                                                                  //$$$$
    //ofstream Print_DRK4("DRK4.txt");                                                                                  //$$$$
        double* k1 = new double[Number]; double* k2 = new double[Number];
        double* k3 = new double[Number]; double* k4 = new double[Number];
        double* sy = new double[Number]; double* hsy = new double[Number];
        double* dsy = new double[Number]; double* ny = new double[Number];

        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                       //$$$$
        //@@@                                                                                @@@@                       //$$$$
        //@@@                                    Nurmal step                                 @@@@                       //$$$$
        //@@@                                                                                @@@@                       //$$$$
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                       //$$$$
        for (int i = 0; i < Number; i++) { k1[i] = mfun(y[i]); }
        for (int i = 0; i < Number; i++) { k2[i] = mfun(y[i] + dt[i] * k1[i] / 2); }
        for (int i = 0; i < Number; i++) { k3[i] = mfun(y[i] + dt[i] * k2[i] / 2); }
        for (int i = 0; i < Number; i++) { k4[i] = mfun(y[i] + dt[i] * k3[i]); }
        for (int i = 0; i < Number; i++) { sy[i] = y[i] + dt[i] / 6 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]); }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                       //$$$$
        //@@@                                                                                @@@@                       //$$$$
        //@@@                                    Half step                                   @@@@                       //$$$$
        //@@@                                                                                @@@@                       //$$$$
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                       //$$$$
        for (int i = 0; i < Number; i++) { k2[i] = mfun(y[i] + dt[i] * k1[i] / 4); }
        for (int i = 0; i < Number; i++) { k3[i] = mfun(y[i] + dt[i] * k2[i] / 4); }
        for (int i = 0; i < Number; i++) { k4[i] = mfun(y[i] + dt[i] * k3[i] / 2); }
        for (int i = 0; i < Number; i++) { hsy[i] = y[i] + dt[i] / 12 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]); }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                       //$$$$
        //@@@                                                                                @@@@                       //$$$$
        //@@@                                   Double step                                  @@@@                       //$$$$
        //@@@                                                                                @@@@                       //$$$$
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                       //$$$$
        for (int i = 0; i < Number; i++) { k2[i] = mfun(y[i] + dt[i] * k1[i]); }
        for (int i = 0; i < Number; i++) { k3[i] = mfun(y[i] + dt[i] * k2[i]); }
        for (int i = 0; i < Number; i++) { k4[i] = mfun(y[i] + dt[i] * k3[i] * 2); }
        for (int i = 0; i < Number; i++) { dsy[i] = y[i] + dt[i] / 3 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]); }

        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                       //$$$$
        //@@@                                                                                @@@@                       //$$$$
        //@@@                                  compareand use                                @@@@                       //$$$$
        //@@@                                                                                @@@@                       //$$$$
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                       //$$$$
        for (int i = 0; i < Number; i++) {
            if (abs(sy[i]) < y_tol) {                                                              //@@@                       //$$$$
                if (dt[i] = !dt_min) {                                                             //@@@                       //$$$$
                    dt[i] = dt_min;                                                                //@@@                       //$$$$
                }                                                                               //@@@                       //$$$$
                ny[i] = sy[i];                                                                        //@@@                       //$$$$
            }
            else {                                                                             //@@@                       //$$$$
                if (abs(sy[i]) > y_tol && (abs(sy[i] - hsy[i]) / abs(sy[i])) > dy_max) {                    //@@@                       //$$$$
                    dt[i] = dt[i] / 2;                                                                //@@@                       //$$$$
                    ny[i] = hsy[i];                                                                   //@@@                       //$$$$
                }                                                                               //@@@                       //$$$$
                else if (abs(sy[i]) > y_tol && (abs(sy[i] - dsy[i]) / abs(sy[i])) < dy_min) {               //@@@                       //$$$$
                    dt[i] = dt[i] * 2;                                                                //@@@                       //$$$$
                    ny[i] = dsy[i];                                                                   //@@@                       //$$$$
                }
                else {                                                                         //@@@                       //$$$$
                    ny[i] = sy[i];                                                                    //@@@                       //$$$$
                }                                                                               //@@@                       //$$$$
            }                                                                                   //@@@                       //$$$$
        }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                       //$$$$
        return ny;                                                                                                      //$$$$
        //Print_DRK4 << t << '\t' << y << endl;                                                                         //$$$$
}                                                                                                                       //$$$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//$$$$$                                                                                                                  $$$$$
//$$$$$                                                    CRK4                                                          $$$$$
//$$$$$                                                                                                                  $$$$$
double*  RK4::CRK4(double* dt, double* y) {                                                                                //$$$$
    //ofstream Print_CRK4("CRK4.txt");                                                                                  //$$$$
        double* k1 = new double[Number]; double* k2 = new double[Number];
        double* k3 = new double[Number]; double* k4 = new double[Number];
        double* sy = new double[Number];
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                       //$$$$
        //@@@                                                                                @@@@                       //$$$$
        //@@@                                    Nurmal step                                 @@@@                       //$$$$
        //@@@                                                                                @@@@                       //$$$$
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                       //$$$$
        for (int i = 0; i < Number; i++) { k1[i] = mfun(y[i]); }
        for (int i = 0; i < Number; i++) { k2[i] = mfun(y[i] + dt[i] * k1[i] / 2); }
        for (int i = 0; i < Number; i++) { k3[i] = mfun(y[i] + dt[i] * k2[i] / 2); }
        for (int i = 0; i < Number; i++) { k4[i] = mfun(y[i] + dt[i] * k3[i]); }
        for (int i = 0; i < Number; i++) { sy[i] = y[i] + dt[i] / 6 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]); }
        return sy;                                                                                                      //$$$$
       // Print_CRK4 << t << '\t' << y << endl;                                                                         //$$$$
}                                                                                                                       //$$$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$