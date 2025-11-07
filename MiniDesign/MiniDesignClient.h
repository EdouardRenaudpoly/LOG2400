#include <vector>
#include <iostream>
#include "affichage.h"

class MiniDesignClient{
public:
    MiniDesignClient(const std::vector<std::shared_ptr<Point>>& points)
    {
        this->points = points;
    }
    void afficherListeEtNuages();
    void afficherGrilleTexture();
    void afficherGrilleID();
    void fusionnerPoints();
    void deplacerPoint();
    void supprimerPoint();
    void setStrategieCreationSurface(std::shared_ptr<StrategieCreationSurface> stratCreation);
    void boucleCommande();
    char trouverTexture();
    void creerNuage();
private:
    std::vector<std::shared_ptr<Point>> points;
    std::vector<NuageDePoints> nuages;
};