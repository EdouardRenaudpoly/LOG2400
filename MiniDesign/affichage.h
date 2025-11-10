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

class Point : public IAffichablePoint
{
public:
    Point(int x, int y) : x(x), y(y){}
    int x, y;
    int id;
    std::string getTextures() const override;
};

std::ostream& operator<<(std::ostream& os, const Point& p);

class NuageDePoints
{
public:
    void relierPoints(std::vector<std::vector<char>>& grille);
    NuageDePoints(const std::vector<std::shared_ptr<Point>>& points, char texture);
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

#pragma once
#include <memory>
#include <string>

// AbstractComponent
class IAffichablePoint {
public:
    virtual ~IAffichablePoint() = default;
    virtual std::string getTextures() const = 0;
};

// AbstractDecorator
class DecorateurPoint : public IAffichablePoint {
protected:
    std::unique_ptr<IAffichablePoint> composant;
public:
    DecorateurPoint(std::unique_ptr<IAffichablePoint> composant);
};

// ConcreteDecorator pour les textures
class DecorateurTexture : public DecorateurPoint {
    char texture;
public:
    DecorateurTexture(std::unique_ptr<IAffichablePoint> composant, char texture);
    std::string getTextures() const override;
};
