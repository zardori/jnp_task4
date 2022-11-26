#ifndef JNP_TASK4_ORGANISM_H
#define JNP_TASK4_ORGANISM_H


#include <cstdint>
#include <optional>
#include <tuple>

template <typename species_t, bool can_eat_meat, bool can_eat_plants>
class Organism {

private:
    species_t m_species;
    uint64_t m_vitality;
public:
    constexpr Organism(const species_t& species, uint64_t vitality)
        : m_species(species), m_vitality(vitality){ }

    constexpr uint64_t get_vitality() const { return m_vitality; }

    const constexpr species_t& get_species() const { return m_species; }

    constexpr bool is_dead() const { return m_vitality == 0; }


};



template <typename T>
using Carnivore = Organism<T, true, false>;
template <typename T>
using Omnivore = Organism<T, true, true>;
template <typename T>
using Herbivore = Organism<T, false, true>;
template <typename T>
using Plant = Organism<T, false, false>;


/*
// Carnivore
template <typename species_t>
class Organism<species_t, true, false> {

private:
    species_t m_species;
    uint64_t m_vitality;
public:
    constexpr Organism(const species_t& species, uint64_t vitality)
        : m_species(species), m_vitality(vitality){ }

    constexpr uint64_t get_vitality() const { return m_vitality; }

    const constexpr species_t& get_species() const { return m_species; }

    constexpr bool is_dead() const { return m_vitality == 0; }


};


// Omnivore
template <typename  species_t>
class Organism<species_t, true, true> {

private:
    species_t m_species;
    uint64_t m_vitality;
public:
    constexpr Organism(const species_t& species, uint64_t vitality)
        : m_species(species), m_vitality(vitality){ }

    constexpr uint64_t get_vitality() const { return m_vitality; }

    const constexpr species_t& get_species() const { return m_species; }

    constexpr bool is_dead() const { return m_vitality == 0; }

};

// Herbivore
template <typename species_t>
class Organism<species_t, false, true> {

private:
    species_t m_species;
    uint64_t m_vitality;
public:
    constexpr Organism(const species_t& species, uint64_t vitality)
        : m_species(species), m_vitality(vitality){ }

    constexpr uint64_t get_vitality() const { return m_vitality; }

    const constexpr species_t& get_species() const { return m_species; }

    constexpr bool is_dead() const { return m_vitality == 0; }



};

// Plant
template <typename species_t>
class Organism<species_t, false, false> {

private:
    species_t m_species;
    uint64_t m_vitality;
public:
    constexpr Organism(const species_t& species, uint64_t vitality)
        : m_species(species), m_vitality(vitality){ }

    constexpr uint64_t get_vitality() const { return m_vitality; }

    const constexpr species_t& get_species() const { return m_species; }

    constexpr bool is_dead() const { return m_vitality == 0; }


};

 */



template <typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
constexpr std::tuple<Organism<species_t, sp1_eats_m, sp1_eats_p>,
        Organism<species_t, sp2_eats_m, sp2_eats_p>,
        std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>>
encounter(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
          Organism<species_t, sp2_eats_m, sp2_eats_p> organism2) {


    //TODO

    return std::tuple(organism1, organism2, std::nullopt);


}


template <typename species_t, bool sp1_eats_m, bool sp1_eats_p, typename ... Args>
constexpr Organism<species_t, sp1_eats_m, sp1_eats_p>
encounter_series(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1, Args ... args) {

    //TODO

    return organism1;
}



#endif //JNP_TASK4_ORGANISM_H
