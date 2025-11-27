#include "commande.h"
#include <iostream>
using namespace std;

void CommandeCreerNuage::executer()
{
    recepteur->creerNuage();
}

void CommandeCreerNuage::annuler()
{
}

void CommandeDeplacerPoint::executer()
{
    recepteur->deplacerPoint();
}

void CommandeDeplacerPoint::annuler()
{

}

void CommandeSupprimerPoint::executer()
{
    recepteur->supprimerPoint();
}

void CommandeSupprimerPoint::annuler()
{
    
}

void CommandeAfficherListeEtNuages::executer()
{
    recepteur->afficherListeEtNuages();
    cout<<"affichage termine"<<endl;
}

void CommandeAfficherListeEtNuages::annuler()
{
}

void CommandeAffichageTexture::executer()
{
    recepteur->choisirAffichageGrilleTexture();
}
void CommandeAffichageTexture::annuler()
{
}

void CommandeAffichageID::executer()
{
    recepteur->choisirAffichageGrilleID();
}
void CommandeAffichageID::annuler()
{
}

void CommandeCreerSurfaceOrdreID::executer()
{
    auto stratSurface = make_shared<StrategieSurfaceOrdreID>();
    recepteur->setStrategieCreationSurface(stratSurface);
}

void CommandeCreerSurfaceOrdreID::annuler()
{

}

void CommandeCreerSurfaceDistanceMin::executer()
{
    auto stratSurface = make_shared<StrategieSurfaceDistanceMin>();
    recepteur->setStrategieCreationSurface(stratSurface);
}
void CommandeCreerSurfaceDistanceMin::annuler()
{

}

