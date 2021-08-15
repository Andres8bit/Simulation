#pragma once
class Vec
{
public:
        Vec(double x = 0, double y = 0)
        {
            this->x = x; this->y = y;
        }
        Vec(const Vec& val)
        {
            this->x = val.x; this->y = val.y;
        }

        double x;
        double y;
};

