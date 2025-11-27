#include "affichage.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "MiniDesignClient.h"
#include "Executeur.h"
#include "Commande.h"

using namespace std;

int main(int argc, char* argv[]) {
    string args;
    // On accepte des points en entrée.
    if (argc > 1) {
        ostringstream oss;
        for (int i = 1; i < argc; ++i) oss << argv[i] << " ";
        args = oss.str();
    } else {
        cout << "Entrez les points au format (x,y) :\n> ";
        getline(cin, args);
    }
    
    // Voici des fonctions utiles pour réaliser le TP. 
    // TODO: Il faudrait les placer dans des classes appropriées.

    PointFactory pointFactory;
    shared_ptr<MiniDesignClient> receveur = make_shared<MiniDesignClient>(pointFactory.creerPoints(args));
    Executeur executeur;
  
   
    string cmd;
    
    // Menu
    while (true) {
        cout << "\nCommandes:\n"
                  << "a  - Afficher les points et les nuages\n"
                  << "o1 - Afficher l'orthèse avec les textures des points\n"
                  << "o2 - Afficher l'orthèse avec les IDs des points\n"
                  << "f  - Fusionner des points dans un nuage (et appliquer texture)\n"
                  << "d  - Deplacer un point (ID)\n"
                  << "s  - Supprimer un point (ID)\n"
                  << "c1 - Créer les surfaces selon l'ordre des IDs\n"
                  << "c2 - Créer les surfaces selon la distance minimale\n"
                  << "q  - Quitter\n> ";
        getline(std::cin, cmd);
        
        if(cmd == "a")
        {
            shared_ptr<Commande> cmdAfficher = make_shared<CommandeAfficherListeEtNuages>(receveur);
            executeur.executerEtSauvergarder(cmdAfficher);
        }
        if (cmd == "q") break;
        if(cmd == "f")
        {
            shared_ptr<Commande> cmdCreerNuage = make_shared<CommandeCreerNuage>(receveur);
            executeur.executerEtSauvergarder(cmdCreerNuage);
        }
        if(cmd == "d")
        {
            shared_ptr<Commande> cmdDeplacerPoint = make_shared<CommandeDeplacerPoint>(receveur);
            executeur.executerEtSauvergarder(cmdDeplacerPoint);
        }
        if(cmd == "s")
        {
            shared_ptr<Commande> cmdSupprimerPoint = make_shared<CommandeSupprimerPoint>(receveur);
            executeur.executerEtSauvergarder(cmdSupprimerPoint);
        }
        if(cmd == "c1")
        {
            shared_ptr<Commande> cmdCreerSurface = make_shared<CommandeCreerSurfaceOrdreID>(receveur);
            executeur.executerEtSauvergarder(cmdCreerSurface);
        }
        if(cmd == "c2")
        {
            shared_ptr<Commande> cmdCreerSurface = make_shared<CommandeCreerSurfaceDistanceMin>(receveur);
            executeur.executerEtSauvergarder(cmdCreerSurface);
        }
        if (cmd == "o1")
        {
            shared_ptr<Commande> cmdAffichageTexture = make_shared<CommandeAffichageTexture>(receveur);
            executeur.executerEtSauvergarder(cmdAffichageTexture);
        }
        if(cmd == "o2")
        {
            
        }
        if(cmd == "r")
        {
            executeur.reexecuterCommande();
        }
        if(cmd == "u")
        {
            executeur.annulerDerniereCommande();
        }

    }

    return 0;
}