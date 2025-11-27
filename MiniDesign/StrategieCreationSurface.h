#ifndef STRATEGIE_CREATION_SURFACE_H
#define STRATEGIE_CREATION_SURFACE_H
#pragma once
#include <iostream>
#include <vector>
#include <memory>


struct IAffichablePoint;
struct Point;

class StrategieCreationSurface{
public:
    virtual void relierPoints(std::vector<std::vector<char>>& grille, std::vector<std::shared_ptr<IAffichablePoint>>& points) = 0;
};

class StrategieSurfaceOrdreID : public StrategieCreationSurface{
public:
    void relierPoints(std::vector<std::vector<char>>& grille, std::vector<std::shared_ptr<IAffichablePoint>>& points) override;
};

class StrategieSurfaceDistanceMin : public StrategieCreationSurface{
public:
    void relierPoints(std::vector<std::vector<char>>& grille, std::vector<std::shared_ptr<IAffichablePoint>>& points) override;
};

#endif