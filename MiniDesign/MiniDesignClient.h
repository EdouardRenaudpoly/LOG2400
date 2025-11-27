#pragma once
#include <vector>
#include <iostream>
#include "AffichageGrille.h"
#include "affichage.h"


class MiniDesignClient
{
public:
    MiniDesignClient(const std::vector<std::shared_ptr<IAffichablePoint>> &points)
        : points(points) {
            for(auto&& p: points)
            {
                elements.push_back(p);
            }
        }

    void setAffichageGrille(std::unique_ptr<AffichageGrille> affichage)
    {
        affichageGrille = std::move(affichage);
    }


    void afficherGrille();
    void choisirAffichageGrilleTexture();
    void choisirAffichageGrilleID();
    void afficherListeEtNuages();
    void deplacerPoint();
    void supprimerPoint();
    void setStrategieCreationSurface(std::shared_ptr<StrategieCreationSurface> stratCreation);
    void creerNuage();



    std::vector<std::shared_ptr<IAffichablePoint>> getPoints() const;
    std::vector<std::shared_ptr<NuageDePoints>> getNuages() const;
    

private:
    std::vector<char> texturesNuages = {'o', '#', '$'};
    std::vector<std::shared_ptr<IAffichablePoint>> points;
    std::vector<std::shared_ptr<NuageDePoints>> nuages;
    std::unique_ptr<AffichageGrille> affichageGrille;
    std::vector<std::shared_ptr<ComposanteAffichageAbs>> elements;
};