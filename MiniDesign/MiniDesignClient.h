#pragma once
#include <vector>
#include <memory>
#include "AffichageGrille.h"
#include "affichage.h"

class CommandeDeplacerPoint;
class CommandeSupprimerPoint;
class StrategieCreationSurface;

// Receveur des commandes
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
    void deplacerPoint(const std::shared_ptr<CommandeDeplacerPoint>& cmd );
    void supprimerPoint(const std::shared_ptr<CommandeSupprimerPoint>& cmd);
    void setStrategieCreationSurface(const std::shared_ptr<StrategieCreationSurface>& stratCreation);
    void creerNuage();
    void recreerPoint(std::shared_ptr<IAffichablePoint> point, std::vector<std::shared_ptr<NuageDePoints>>& nuagesContenantPoint);



    std::vector<std::shared_ptr<IAffichablePoint>> getPoints() const;
    std::vector<std::shared_ptr<NuageDePoints>> getNuages() const;
    

private:
    std::vector<char> texturesNuages = {'o', '#', '$'};
    std::vector<std::shared_ptr<IAffichablePoint>> points;
    std::vector<std::shared_ptr<NuageDePoints>> nuages;
    std::unique_ptr<AffichageGrille> affichageGrille;
    std::vector<std::shared_ptr<ComposanteAffichageAbs>> elements;
};