#ifndef _CHRONOLOG_H
#define _CHRONOLOG_H

#include <iostream>
#include <time.h>
#include <chrono>

/**
 * @class Chronolog
 * @brief Classe utilitaire pour gérer des intervalles de temps et des temporisations.
 *
 * Utilise les horloges C++ (`chrono` et `clock`) pour suivre des délais précis dans le jeu.
 * Peut servir à synchroniser des actions (ex: cooldowns, délais entre événements...).
 */
class Chronolog
{
private:
    std::chrono::milliseconds interval = std::chrono::milliseconds(0); ///< Intervalle de temps défini
    std::chrono::time_point<std::chrono::steady_clock> timeStart;      ///< Point de départ pour la mesure d'intervalle
    clock_t timer;                                                     ///< Timer basé sur clock() pour des mesures globales

public:

    /**
     * @brief Constructeur par défaut.
     *
     * Initialise le point de départ avec l'horloge `steady_clock`.
     */
    Chronolog() : timeStart(std::chrono::steady_clock::now()) { timer = clock(); }

    /**
     * @brief Définit une nouvelle durée d’intervalle en millisecondes.
     * @param intervalMs Durée de l’intervalle en millisecondes.
     */
    void defineInterval(unsigned int intervalMs)
    {
        interval = std::chrono::milliseconds(intervalMs);
        timeStart = std::chrono::steady_clock::now();
    }

    /**
     * @brief Vérifie si l’intervalle défini est écoulé.
     *
     * Si le délai est écoulé, il remet le point de départ à maintenant et retourne `true`.
     *
     * @return `true` si l'intervalle est écoulé, `false` sinon.
     */
    bool hasElapsed()
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - timeStart);

        if (elapsed >= interval)
        {
            timeStart = now;
            timer = clock();
            return true;
        }
        return false;
    }

    /**
     * @brief Retourne le temps écoulé depuis le dernier déclenchement, en secondes.
     * @return Temps en secondes (approximatif).
     */
    int getTimer()
    {
        return (int)((clock() - timer) / 1000);
    }
};

#endif
