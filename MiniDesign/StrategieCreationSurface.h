#ifndef STRATEGIE_CREATION_SURFACE_H
#define STRATEGIE_CREATION_SURFACE_H

#include <iostream>
#include <vector>

struct Point;

class StrategieCreationSurface{
public:
    virtual void relierPoints(std::vector<std::vector<char>>& grille, std::vector<std::shared_ptr<Point>>& points) = 0;
};

class StrategieSurfaceOrdreID : public StrategieCreationSurface{
public:
    void relierPoints(std::vector<std::vector<char>>& grille, std::vector<std::shared_ptr<Point>>& points) override;
};

class StrategieSurfaceDistanceMin : public StrategieCreationSurface{
public:
    void relierPoints(std::vector<std::vector<char>>& grille, std::vector<std::shared_ptr<Point>>& points) override;
};

#endif