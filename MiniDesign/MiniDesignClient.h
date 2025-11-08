#include <vector>
#include <iostream>
#include "AffichageGrille.h"
#include "affichage.h"

class MiniDesignClient{
public:
    MiniDesignClient(const std::vector<std::shared_ptr<Point>>& points)
    : points(points) {}

    void setAffichageGrille(std::unique_ptr<AffichageGrille> affichage)
    {
        affichageGrille = std::move(affichage);
    }
    void afficherGrille();

    void choisirAffichageGrille(const std::string& cmd);

    void afficherListeEtNuages();
    void deplacerPoint();
    void supprimerPoint();
    void setStrategieCreationSurface(std::shared_ptr<StrategieCreationSurface> stratCreation);
    void creerNuage(char texture);
private:
    std::vector<std::shared_ptr<Point>> points;
    std::vector<std::shared_ptr<NuageDePoints>> nuages;
    std::unique_ptr<AffichageGrille> affichageGrille;
};