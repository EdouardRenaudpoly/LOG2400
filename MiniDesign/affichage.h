#pragma once
#include <string>
#include <vector>
#include "StrategieCreationSurface.h"
#include <memory>

static constexpr int LARGEUR = 50;
static constexpr int HAUTEUR = 20;

class PointFactory{
public:
    std::vector<std::shared_ptr<Point>> creerPoints(const std::string& ligne);
};

struct Point {
    int x, y;
    int id;
};

std::ostream& operator<<(std::ostream& os, const Point& p);

class NuageDePoints
{
public:
    void relierPoints(std::vector<std::vector<char>>& grille);
    NuageDePoints(const std::vector<std::shared_ptr<Point>>& points);
    void setStrategieCreationSurface(const std::shared_ptr<StrategieCreationSurface>& stratSurface);
    friend std::ostream& operator<<(std::ostream& os, const NuageDePoints& nuageDePoints);
    char getTexture() const;
    bool contientPoint(int idPoint) const;
    void supprimerPoint(int idPoint);
private:
    char texture;
    std::vector<std::shared_ptr<Point>> points;
    std::shared_ptr<StrategieCreationSurface> stratSurface;
};

void tracerLigne(std::vector<std::vector<char>>& grille, int x0, int y0, int x1, int y1);