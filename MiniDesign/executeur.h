#pragma once
#include "commande.h"
#include <memory>
#include <stack>

class Executeur {
public:
    Executeur() = default;
    void executerCommande(const std::shared_ptr<Commande>& cmd) ;
    void annulerDerniereCommande() ;
    void executerEtSauvegarder(const std::shared_ptr<Commande>& cmd);
    void reexecuterCommande();
private:
    std::stack<std::shared_ptr<Commande>> undoStack;
    std::stack<std::shared_ptr<Commande>> redoStack;

};