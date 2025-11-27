#include "StrategieCreationSurface.h"
#include "affichage.h"
#include <iostream>
#include <cmath>
#include <memory>
#include <algorithm>

void StrategieSurfaceOrdreID::relierPoints(std::vector<std::vector<char>>& grille,
                                           std::vector<std::shared_ptr<IAffichablePoint>>& points)
{
    if (points.size() < 2) return;

    // construire une copie triée des pointeurs selon l'id du Point de base
    std::vector<std::shared_ptr<IAffichablePoint>> pts = points;
    std::sort(pts.begin(), pts.end(), [](const auto& a, const auto& b) {
        auto pa = a->getPointDeBase();
        auto pb = b->getPointDeBase();
        return pa->getId() < pb->getId();
    });

    int size = static_cast<int>(pts.size());
    for (int i = 0; i < size; ++i) {
        auto pa = pts[i]->getPointDeBase();
        auto pb = pts[(i + 1) % size]->getPointDeBase();
        tracerLigne(grille, pa->x, pa->y, pb->x, pb->y);
    }
}

void StrategieSurfaceDistanceMin::relierPoints(std::vector<std::vector<char>>& grille, std::vector<std::shared_ptr<IAffichablePoint>>& points) 
{
    
    std::vector<bool> visite(points.size(), false);
    int indexCourant = 0;
    visite[indexCourant] = true;
    int nbVisites = 1;

    while (nbVisites < points.size()) 
    {
        int suivant = -1;
        double distMin = 1e9;

        for (int i = 0; i < points.size(); i++) 
        {
            if (!visite[i]) 
            {
                double dx = points[i]->getPointDeBase()->x - points[indexCourant]->getPointDeBase()->x;
                double dy = points[i]->getPointDeBase()->y - points[indexCourant]->getPointDeBase()->y;
                double dist = sqrt(dx*dx + dy*dy);
                
                if (dist < distMin) 
                {
                    distMin = dist;
                    suivant = i;
                }
            }
        }

        tracerLigne(grille, points[indexCourant]->getPointDeBase()->x, points[indexCourant]->getPointDeBase()->y, points[suivant]->getPointDeBase()->x, points[suivant]->getPointDeBase()->y);
        visite[suivant] = true;
        indexCourant = suivant;
        ++nbVisites;
    }

    tracerLigne(grille, points[indexCourant]->getPointDeBase()->x, points[indexCourant]->getPointDeBase()->y, points[0]->getPointDeBase()->x, points[0]->getPointDeBase()->y);
}
