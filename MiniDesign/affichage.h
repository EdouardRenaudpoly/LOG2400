#pragma once
#include <string>
#include <vector>
#include "StrategieCreationSurface.h"
#include <memory>

static constexpr int LARGEUR = 50;
static constexpr int HAUTEUR = 20;

// AbstractComponent
class IAffichablePoint {
public:
    virtual ~IAffichablePoint() = default;
    virtual std::string getTextures() const = 0;
    virtual std::shared_ptr<Point> getPointDeBase() { return nullptr; }
};

// AbstractDecorator
class DecorateurPoint : public IAffichablePoint {
protected:
    std::shared_ptr<IAffichablePoint> composant;
public:
    DecorateurPoint(std::shared_ptr<IAffichablePoint> composant);

    std::shared_ptr<Point> getPointDeBase() override {
        return composant ? composant->getPointDeBase() : nullptr;
    }
};

// ConcreteDecorator pour les textures
class DecorateurTexture : public DecorateurPoint {
    char texture;
public:
    DecorateurTexture(std::shared_ptr<IAffichablePoint> composant, char texture);
    std::string getTextures() const override;
};

class PointFactory{
public:
    std::vector<std::shared_ptr<IAffichablePoint>> creerPoints(const std::string& ligne);
};

class Point : public IAffichablePoint, public std::enable_shared_from_this<Point>
{
public:
    Point(int x, int y) : x(x), y(y){}
    int x, y;
    int id;
    std::string getTextures() const override;
    std::shared_ptr<Point> getPointDeBase() override { return shared_from_this(); }
};

std::ostream& operator<<(std::ostream& os, const Point& p);

class NuageDePoints
{
public:
    void relierPoints(std::vector<std::vector<char>>& grille);
    NuageDePoints(const std::vector<std::shared_ptr<IAffichablePoint>>& points, char texture);
    void setStrategieCreationSurface(const std::shared_ptr<StrategieCreationSurface>& stratSurface);
    friend std::ostream& operator<<(std::ostream& os, const NuageDePoints& nuageDePoints);
    char getTexture() const;
    bool contientPoint(int idPoint) const;
    void supprimerPoint(int idPoint);
private:
    char texture;
    std::vector<std::shared_ptr<IAffichablePoint>> points;
    std::shared_ptr<StrategieCreationSurface> stratSurface;
};

void tracerLigne(std::vector<std::vector<char>>& grille, int x0, int y0, int x1, int y1);