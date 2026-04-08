//
// Created by parallels on 4/7/26.
//

#ifndef BUILD_PID_CONTROLLER_HPP
#define BUILD_PID_CONTROLLER_HPP

#include "delta_timer.hpp"
#include "lowpassFilter.hpp"

class pidController
{
public:
    pidController();
    void update();
    double getOutput()
    {
        return u0;
    };


    void setCon(double y)
    {
        con=y;
    };
    void setRef(double r)
    {
        ref=r;
    };



    void setKp(const double& kp);
    void setKi(const double& ki);
    void setKd(const double& kd);
    double getKp();
    double getKi();
    double getKd();




private:
    double ref = 0.0, con = 0.0;
    double e2 = 0.0, e1 = 0.0, e0 = 0.0;
    double u2 = 0.0, u1 = 0.0, u0 = 0.0;

    double N = 1.0;
    double Kp = 0.01, Ki = 1, Kd = 0;

    delta_timer timer_;

    LowPassFilter lowpassFilter;

};
#endif //BUILD_PID_CONTROLLER_HPP
