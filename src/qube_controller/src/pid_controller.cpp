#include "qube_controller/pid_controller.hpp"

using namespace std::chrono_literals;


pidController::pidController()
{

}
void pidController::update()
{
    // source https://www.scilab.org/discrete-time-pid-controller-implementation
    double Ts = timer_.step(1e-3,100e-3);

    double a0=(1+N*Ts);
    double a1 = -(2 + N*Ts);
    double a2 = 1;

    double b0 = Kp*(1+N*Ts) + Ki*Ts*(1+N*Ts) + Kd*N;

    double b1 = -(Kp*(2+N*Ts) + Ki*Ts + 2*Kd*N);
    double b2 = Kp + Kd*N;

    double ku1 = a1/a0;
    double ku2 = a2/a0;
    double ke0 = b0/a0;
    double ke1 = b1/a0;
    double ke2 = b2/a0;

    e0=(ref)-(lowpassFilter.update(con,Ts));

    u0=-ku1*u1-ku2*u2+ke0*e0+ke1*e1+ke2*e2;


    e2=e1;
    e1=e0;
    u2=u1;
    u1=u0;
}

void setKp(const double& kp);
void setKi(const double& ki);
void setKd(const double& kd);
//getters and setters

void pidController::setKp(const double& kp)
{
    Kp=kp;
}
void pidController::setKi(const double& ki)
{
    Ki=ki;
}
void pidController::setKd(const double& kd)
{
    Kd=kd;
}

double pidController::getKp()
{
    return Kp;
}

double pidController::getKi()
{
    return Ki;
}
double pidController::getKd()
{
    return Kd;
}