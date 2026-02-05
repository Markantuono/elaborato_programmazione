#include <iostream>
#include "Informations.h"
#include "Item.h"
#include "List.h"
#include "User.h"

int main() {

    try{
        //Creazione utenti
        User niccolò("Niccolò");
        User chiara("Chiara");

        //Creazione lista
        niccolò.createList("Spesa");

        //Condivisione lista
        std::cout << "~CONDIVISIONE LISTA~" << std::endl;
        niccolò.shareList(&chiara, "Spesa");

        //Creazione oggetti
        Item mela("Mela", 5, 2, 2026, "Melinda", Category::Frutta, 2, 0.90, false);
        Item pollo("Pollo", 5, 2, 2026, "Amadori" , Category::Carne, 1, 3.50, false);
        Item formaggio("Pecorino", 5, 2 , 2026, "Biancospino", Category::Latticini, 1, 4.20, false);
        Item pesce("Sgombro", 5, 2, 2026, "Capitan Findus", Category::Pesce, 1, 4.65, false);
        Item patatine("Patatine chips", 5, 2, 2026, "Pringles", Category::Snack, 3, 1.90, false);
        Item drink("Energy drink", 5, 2, 2026, "Monster", Category::Bevande, 4, 1.15, false);
        Item mocio("Mocio", 5, 2, 2026, "Vileda", Category::Non_alimentari, 1, 1.99, false);

        //Aggiungo gli oggetti alla lista
        niccolò.addItemToList("Spesa", mela);
        niccolò.addItemToList("Spesa", pollo);
        niccolò.addItemToList("Spesa", formaggio);
        niccolò.addItemToList("Spesa", pesce);
        niccolò.addItemToList("Spesa", patatine);
        niccolò.addItemToList("Spesa", drink);
        niccolò.addItemToList("Spesa", mocio);

        //Controllo delle liste esistenti
        niccolò.showAllList();

        //Aggiornamento quantità
        niccolò.updateQuantity("Spesa", "Mela", 3);
        niccolò.updateQuantity("Spesa", "Pecorino", 2);
        niccolò.updateQuantity("Spesa", "Energy drink", 6);

        //Cambio status
        niccolò.updateStatus("Spesa", "Mela", true);
        niccolò.updateStatus("Spesa", "Sgombro", true);

        //Modifica della lista(condivisa) da altro utente
        chiara.removeItemFromList("Spesa", "Energy drink");
        chiara.showAllList();

        //Ricontrollo lista singola
        niccolò.showSingleList("Spesa");
    }

    catch (const std::exception& e){
        std::cerr << "Errore: " << e.what() << std::endl;
    }

    return 0;
}
