#include "commande.h";
#include <memory>;
#include <stack>;

class Executeur {
public:
    Executeur() = default;
    void executerCommande(const std::shared_ptr<Commande>& cmd) ;
    void annulerDerniereCommande() ;
private:
    std::stack<std::shared_ptr<Commande>> historique;
};