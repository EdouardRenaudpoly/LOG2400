#ifndef AFFICHAGE_GRILLE_H
#define AFFICHAGE_GRILLE_H
#pragma once
#include <vector>
#include <memory>
#include "affichage.h"


class AffichageGrille {
protected:

    std::vector<std::shared_ptr<NuageDePoints>> nuages;
    std::vector<std::shared_ptr<IAffichablePoint>> points;

    virtual void afficherPoints(std::vector<std::vector<char>>& grille) = 0;

public:
    AffichageGrille(const std::vector<std::shared_ptr<NuageDePoints>>& nuages,
                    const std::vector<std::shared_ptr<IAffichablePoint>>& points);

    virtual ~AffichageGrille() = default;

    void afficherGrille();

protected:
    void tracerLigne(std::vector<std::vector<char>>& grille, int x1, int y1, int x2, int y2);
};


// Version affichant les points par texture
class AffichageGrilleTexture : public AffichageGrille {
protected:
    void afficherPoints(std::vector<std::vector<char>>& grille) override;

public:
    using AffichageGrille::AffichageGrille;
};


// Version affichant les points par ID
class AffichageGrilleID : public AffichageGrille {
protected:
    void afficherPoints(std::vector<std::vector<char>>& grille) override;

public:
    using AffichageGrille::AffichageGrille;
};

#endif
