#pragma once
#include <string>
#include <vector>
#include "StrategieCreationSurface.h"
#include <memory>

const int LARGEUR = 30;
const int HAUTEUR = 20;

struct Point {
    int x, y;
};

class NuageDePoints
{
public:
    void imprimerGrille(const std::string& cmd);
    NuageDePoints(const std::string& ligne);
    void setStrategieCreationSurface(const std::shared_ptr<StrategieCreationSurface>& stratSurface);
private:
    std::vector<Point> points;
    std::shared_ptr<StrategieCreationSurface> stratSurface;
};

void tracerLigne(std::vector<std::vector<char>>& grille, int x0, int y0, int x1, int y1);