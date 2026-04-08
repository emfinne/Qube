
#ifndef BUILD_LOWPASSFILTER_HPP
#define BUILD_LOWPASSFILTER_HPP



class LowPassFilter
{
public:
    LowPassFilter(){};

    double update(double x, double dt)
    {
        double alpha = dt / (tau_ + dt);
        y_ = alpha * x + (1.0 - alpha) * y_;
        return y_;
    }




private:
    double tau_=0.01;
    double y_=0;
};

#endif //BUILD_LOWPASSFILTER_HPP
