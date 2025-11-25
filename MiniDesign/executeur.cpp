#include "executeur.h"
using namespace std;

void Executeur::executerCommande(const shared_ptr<Commande>& cmd) {
    cmd->executer("cmd");
    historique.push(cmd);
}
void Executeur::annulerDerniereCommande() {
    if (!historique.empty()) {
        shared_ptr<Commande> cmd = historique.top();
        cmd->annuler();
        historique.pop();
    }
}