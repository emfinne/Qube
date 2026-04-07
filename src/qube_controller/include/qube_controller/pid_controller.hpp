//
// Created by parallels on 4/7/26.
//

#ifndef BUILD_PID_CONTROLLER_HPP
#define BUILD_PID_CONTROLLER_HPP

#include "delta_timer.hpp"

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

    double N = 20.0;
    double Kp = 1.0, Ki = 1.0, Kd = 1.0;

    delta_timer timer_;

};
#endif //BUILD_PID_CONTROLLER_HPP
