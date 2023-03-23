#include "HypoGl/Animation.h"

#include <iostream>

#include "HypoGl/Maths.h"

void Animation::addKey(const AnimationKey& key)
{
    keys.insert({key.getTimeStamp(), key});
}

AnimationKey Animation::getAnimState(const float& time) const
{
    if(keys.size() == 0)
    {
        std::cout << "Impossible de donner l'etat de l'animation car aucune cle n'a ete definie.";
        exit(1);
    }

    // Recherche de la clé précédant et de la clé suivant la valeur time.
    auto before = keys.end(), after = keys.end();

    for(auto it = keys.begin() ; it != keys.end() ; it++)
    {
        if(time >= it->first) before = it;

        else if(after == keys.end())
        {
            after = it;
            break;
        }
    }

    // Si la clé précédente n'a pas été trouvée, c'est que time est avant toutes les clés. Donc on renvoie la première clé.
    if(before == keys.end()) return keys.begin()->second;

    // Si la clé suivante n'a pas été trouvée, plusieurs solutions sont possibles. Mais dans tous les cas,
    // on prendra la clé se situant juste après first, ou la première si first est la dernière clé de l'animation.
    if(after == keys.end())
    {
        after = before; after++;
        if(after == keys.end()) after = keys.begin();
    }

    return lerp(before->second, after->second, (time - before->first) / (after->first - before->first));
}
