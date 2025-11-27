#pragma once
#include <string>
#include <vector>
#include "StrategieCreationSurface.h"
#include <memory>

static constexpr int LARGEUR = 50;
static constexpr int HAUTEUR = 20;


class ComposanteAffichageAbs
{

public:
    virtual std::string getTextures() const = 0;
    virtual void ajouterComposant(const std::shared_ptr<ComposanteAffichageAbs> &element) = 0;
    virtual void supprimerPoint(int idPoint) = 0;
    void setId(int newId) { id = newId; }
    int getId() const { return id; }

protected:
    int id;
private:
    char texture;


};

// AbstractComponent
class IAffichablePoint : public ComposanteAffichageAbs
{
public:
    virtual ~IAffichablePoint() = default;

    virtual std::shared_ptr<Point> getPointDeBase() { return nullptr; }
};

// AbstractDecorator
class DecorateurPoint : public IAffichablePoint
{
protected:
    std::shared_ptr<IAffichablePoint> composant;

public:
    DecorateurPoint(std::shared_ptr<IAffichablePoint> composant);

    std::shared_ptr<Point> getPointDeBase() override
    {
        return composant ? composant->getPointDeBase() : nullptr;
    }
};

// ConcreteDecorator pour les textures
class DecorateurTexture : public DecorateurPoint
{
    char texture;

public:
    DecorateurTexture(std::shared_ptr<IAffichablePoint> composant, char texture);
    std::string getTextures() const override;
    void ajouterComposant(const std::shared_ptr<ComposanteAffichageAbs> &element) override {}
    void supprimerPoint(int idPoint) override {}
};

class PointFactory
{
public:
    std::vector<std::shared_ptr<IAffichablePoint>> creerPoints(const std::string &ligne);
};

class Point : public IAffichablePoint, public std::enable_shared_from_this<Point>
{
public:
    Point(int x, int y) : x(x), y(y) {}
    int x, y;
    std::string getTextures() const override;
    std::shared_ptr<Point> getPointDeBase() override { return shared_from_this(); }
    void ajouterComposant(const std::shared_ptr<ComposanteAffichageAbs> &element) override {}
    void supprimerPoint(int idPoint) override {}
};

std::ostream &operator<<(std::ostream &os, const Point &p);

class NuageDePoints : public ComposanteAffichageAbs
{
public:
    void relierPoints(std::vector<std::vector<char>> &grille);
    NuageDePoints(const std::vector<std::shared_ptr<ComposanteAffichageAbs>> &points, char texture);
    void setStrategieCreationSurface(const std::shared_ptr<StrategieCreationSurface> &stratSurface);
    friend std::ostream &operator<<(std::ostream &os, const NuageDePoints &nuageDePoints);
    std::string getTextures() const override;
    bool contientPoint(int idPoint) const;
    void supprimerPoint(int idPoint) override;
    void ajouterComposant(const std::shared_ptr<ComposanteAffichageAbs> &element) override;
    std::vector<std::shared_ptr<IAffichablePoint>> &getPoints(std::vector<std ::shared_ptr<IAffichablePoint>> &vecRec) const;

private:
    char texture;
    std::vector<std::shared_ptr<ComposanteAffichageAbs>> points;
    std::shared_ptr<StrategieCreationSurface> stratSurface;
};


void tracerLigne(std::vector<std::vector<char>> &grille, int x0, int y0, int x1, int y1);