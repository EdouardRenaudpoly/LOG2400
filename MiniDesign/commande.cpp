#include "commande.h"
#include "MiniDesignClient.h"
#include "affichage.h"
#include "StrategieCreationSurface.h"
#include <iostream>
using namespace std;

void CommandeCreerNuage::executer()
{
    recepteur->creerNuage();
}



void CommandeDeplacerPoint::executer()
{
    
    recepteur->deplacerPoint(shared_from_this());
}

void CommandeDeplacerPoint::annuler()
{
    recepteur->deplacerPoint(shared_from_this());
}

void CommandeSupprimerPoint::executer()
{
    recepteur->supprimerPoint(shared_from_this());
}

void CommandeSupprimerPoint::annuler()
{
    recepteur->recreerPoint(pointSupprime, nuagesContenantPoint);
    for (auto &nuage : nuagesContenantPoint)
    {
        nuage->rajouterPoint(pointSupprime);
    }
}

void CommandeSupprimerPoint::setSavedData(std::shared_ptr<IAffichablePoint> point, const std::vector<std::shared_ptr<NuageDePoints>>& nuages)
{
    pointSupprime = point;
    nuagesContenantPoint = nuages;
}

void CommandeAfficherListeEtNuages::executer()
{
    recepteur->afficherListeEtNuages();
}



void CommandeAffichageTexture::executer()
{
    recepteur->choisirAffichageGrilleTexture();
}


void CommandeAffichageID::executer()
{
    recepteur->choisirAffichageGrilleID();
}


void CommandeCreerSurfaceOrdreID::executer()
{
    auto stratSurface = make_shared<StrategieSurfaceOrdreID>();
    recepteur->setStrategieCreationSurface(stratSurface);
}



void CommandeCreerSurfaceDistanceMin::executer()
{
    auto stratSurface = make_shared<StrategieSurfaceDistanceMin>();
    recepteur->setStrategieCreationSurface(stratSurface);
}


