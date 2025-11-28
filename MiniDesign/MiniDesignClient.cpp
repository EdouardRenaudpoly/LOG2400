#include "MiniDesignClient.h"
#include "commande.h"
#include <iostream>
#include <cctype>
#include <sstream>
#include <algorithm>

using namespace std;

void MiniDesignClient::afficherListeEtNuages()
{
    for (auto &&element : elements)
    {
        if (typeid(*element) == typeid(NuageDePoints))
        {
            auto nuage = dynamic_pointer_cast<NuageDePoints>(element);
            if (nuage)
            {
                cout << *nuage;
            }
        }
        else
        {
            auto point = dynamic_pointer_cast<IAffichablePoint>(element);
            if (point)
            {
                string textures = point->getTextures();
                cout << "Point ID " << point->getPointDeBase()->getId() << ": " << *(point->getPointDeBase()) << " textures: '" << textures << "'" << endl;
            }
        }
    }
}

void MiniDesignClient::creerNuage()
{
    if (nuages.size() == texturesNuages.size())
    {
        cout << "Nombre maximal de nuages atteint";
        return;
    }

    vector<shared_ptr<IAffichablePoint>> pointsNuage;

    cout << "IDs des points à fusionner dans un nuage (ex: 0 2 4): ";
    string line;
    getline(cin >> ws, line);

    istringstream iss(line);
    int idRecherche;
    bool erreur = false;

    while (iss >> idRecherche)
    {
        auto itElem = find_if(elements.begin(), elements.end(),
                              [&](const shared_ptr<ComposanteAffichageAbs> &e)
                              {
                                  return e->getId() == idRecherche;
                              });

        if (itElem != elements.end())
        {
            if (auto p = dynamic_pointer_cast<IAffichablePoint>(*itElem))
            {
                // Check if this point is already decorated (i.e., already in another nuage)
                auto itExistingPoint = find_if(points.begin(), points.end(),
                                               [&](const shared_ptr<IAffichablePoint> &pt)
                                               {
                                                   return pt->getPointDeBase()->getId() == p->getPointDeBase()->getId();
                                               });
                
                auto decorated = make_shared<DecorateurTexture>(p, texturesNuages[nuages.size()]);
                size_t idx = distance(elements.begin(), itElem);
                elements[idx] = decorated;
                points[idx] = decorated;
                pointsNuage.push_back(decorated);
            }
            else if (auto n = dynamic_pointer_cast<NuageDePoints>(*itElem))
            {
                vector<shared_ptr<IAffichablePoint>> subPoints;
                subPoints = n->getPoints(subPoints);
                for (auto &sub : subPoints)
                {
                    // Check if the point is already in elements/points
                    auto itExistingPoint = find_if(points.begin(), points.end(),
                                                   [&](const shared_ptr<IAffichablePoint> &pt)
                                                   {
                                                       return pt->getPointDeBase()->getId() == sub->getPointDeBase()->getId();
                                                   });
                    
                    if (itExistingPoint != points.end())
                    {
                        // Point already exists, wrap it with another decorator
                        auto decoratedSub = make_shared<DecorateurTexture>(*itExistingPoint, texturesNuages[nuages.size()]);
                        // Update the points and elements arrays
                        size_t idxExisting = distance(points.begin(), itExistingPoint);
                        points[idxExisting] = decoratedSub;
                        auto itElemExisting = find_if(elements.begin(), elements.end(),
                                                      [&](const shared_ptr<ComposanteAffichageAbs> &e)
                                                      {
                                                          if (auto pt = dynamic_pointer_cast<IAffichablePoint>(e))
                                                              return pt->getPointDeBase()->getId() == sub->getPointDeBase()->getId();
                                                          return false;
                                                      });
                        if (itElemExisting != elements.end())
                        {
                            size_t idxElemExisting = distance(elements.begin(), itElemExisting);
                            elements[idxElemExisting] = decoratedSub;
                        }
                        pointsNuage.push_back(decoratedSub);
                    }
                    else
                    {
                        // New point, decorate it
                        auto decoratedSub = make_shared<DecorateurTexture>(sub, texturesNuages[nuages.size()]);
                        pointsNuage.push_back(decoratedSub);
                    }
                }
            }
        }
        else
        {
            cout << "Aucun élément avec l'ID " << idRecherche << endl;
            erreur = true;
        }
    }

    if (!erreur && !pointsNuage.empty())
    {
        vector<shared_ptr<ComposanteAffichageAbs>> converted;
        for (auto &p : pointsNuage)
        {
            converted.push_back(p);
        }

        auto nuage = make_shared<NuageDePoints>(converted, texturesNuages[nuages.size()]);
        nuage->setId(elements.size());
        nuages.push_back(nuage);
        elements.push_back(nuage);

        cout << "Nuage créé avec " << pointsNuage.size() << " points." << endl;
    }
    else if (pointsNuage.empty())
    {
        cout << "Aucun point valide fourni." << endl;
    }
}

void MiniDesignClient::deplacerPoint(const shared_ptr<CommandeDeplacerPoint> &cmd)
{
    int idPoint;
    int newX, newY;
    if (cmd->getancienneX() == -1 && cmd->getancienneY() == -1)
    {

        cout << "ID du point à déplacer: ";
        cin >> idPoint;

        cout << "Nouvelle position (x y): ";

        if (cin >> newX >> newY)
        {
        }
        else
        {
            cout << "Entrée invalide" << endl;
        }
    }
    else
    {
        newX = cmd->getancienneX();
        newY = cmd->getancienneY();
    }

    auto itPoint = find_if(points.begin(), points.end(),
                           [&](const shared_ptr<IAffichablePoint> &p)
                           { return p->getPointDeBase()->getId() == idPoint; });

    if (itPoint != points.end())
    {
        cmd->setSavedData(*itPoint, (*itPoint)->getPointDeBase()->x, (*itPoint)->getPointDeBase()->y);
        (*itPoint)->getPointDeBase()->x = newX;
        (*itPoint)->getPointDeBase()->y = newY;
    }
    else
    {
        cout << "Ce point n'existe pas" << endl;
    }
}

void MiniDesignClient::supprimerPoint(const shared_ptr<CommandeSupprimerPoint> &cmd)
{

    int idPoint;
    if (cmd->getPointSupprime() != nullptr)
    {
        idPoint = cmd->getPointSupprime()->getPointDeBase()->getId();
    }
    else
    {
        cout << "ID du point à supprimer: ";
        cin >> idPoint;
    }

    auto it = find_if(points.begin(), points.end(),
                      [&](const shared_ptr<IAffichablePoint> &p)
                      { return p->getPointDeBase()->getId() == idPoint; });
    if (it == points.end())
        return;

    shared_ptr<IAffichablePoint> pointASupprimer = *it;

    vector<shared_ptr<NuageDePoints>> nuagesContenantPoint;
    
    for (auto &nuage : this->nuages)
    {
        if (nuage->contientPoint(idPoint))
        {
            nuagesContenantPoint.push_back(nuage);
        }
    }
    
    cmd->setSavedData(pointASupprimer, nuagesContenantPoint);

    for (auto &nuage : nuages)
    {
        nuage->supprimerPoint(idPoint);
    }

    points.erase(it);
    elements.erase(remove_if(elements.begin(), elements.end(),
                             [&](const shared_ptr<ComposanteAffichageAbs> &e)
                             { return e->getId() == idPoint; }),
                   elements.end());
}

void MiniDesignClient::afficherGrille()
{
    if (affichageGrille)
    {
        affichageGrille->afficherGrille();
    }
}

void MiniDesignClient::choisirAffichageGrilleTexture()
{

    affichageGrille = make_unique<AffichageGrilleTexture>(nuages, points);
    this->afficherGrille();
}

void MiniDesignClient::choisirAffichageGrilleID()
{
    affichageGrille = make_unique<AffichageGrilleID>(nuages, points);
    this->afficherGrille();
}

void MiniDesignClient::setStrategieCreationSurface(const shared_ptr<StrategieCreationSurface> &stratCreation)
{
    for (auto &&nuage : nuages)
    {
        nuage->setStrategieCreationSurface(stratCreation);
    }
}

vector<shared_ptr<IAffichablePoint>> MiniDesignClient::getPoints() const
{
    return points;
}

vector<shared_ptr<NuageDePoints>> MiniDesignClient::getNuages() const
{
    return nuages;
}

void MiniDesignClient::recreerPoint(shared_ptr<IAffichablePoint> point, vector<shared_ptr<NuageDePoints>> &nuagesContenatntPoint)
{
    points.push_back(point);
    elements.push_back(point);
    std::sort(elements.begin(), elements.end(),
              [](const std::shared_ptr<ComposanteAffichageAbs> &a,
                 const std::shared_ptr<ComposanteAffichageAbs> &b)
              {
                  return a->getId() < b->getId();
              });
}
