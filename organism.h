#ifndef JNP_TASK4_ORGANISM_H
#define JNP_TASK4_ORGANISM_H


#include <cstdint>
#include <optional>
#include <tuple>
#include <cstdarg>

template<typename species_t, bool can_eat_meat, bool can_eat_plants> requires std::equality_comparable<species_t>
class Organism {
private:
    species_t m_species;
    uint64_t m_vitality;
public:
    constexpr Organism(const species_t &species, uint64_t vitality)
            : m_species(species), m_vitality(vitality) {}

    constexpr uint64_t get_vitality() const {
        return m_vitality;
    }

    const constexpr species_t &get_species() const {
        return m_species;
    }

    constexpr bool is_dead() const {
        return m_vitality == 0;
    }
};


template<typename T>
using Carnivore = Organism<T, true, false>;
template<typename T>
using Omnivore = Organism<T, true, true>;
template<typename T>
using Herbivore = Organism<T, false, true>;
template<typename T>
using Plant = Organism<T, false, false>;


/*
// Carnivore
template<typename species_t>
class Organism<species_t, true, false> {
private:
    species_t m_species;
    uint64_t m_vitality;
public:
    constexpr uint64_t get_vitality() const { return m_vitality; }

    const constexpr species_t &get_species() const { return m_species; }

    constexpr bool is_dead() const { return m_vitality == 0; }

};


// Omnivore
template<typename species_t>
class Organism<species_t, true, true> {

private:
    species_t m_species;
    uint64_t m_vitality;
public:
    constexpr Organism(const species_t &species, uint64_t vitality)
            : m_species(species), m_vitality(vitality) {}

    constexpr uint64_t get_vitality() const { return m_vitality; }

    const constexpr species_t &get_species() const { return m_species; }

    constexpr bool is_dead() const { return m_vitality == 0; }

};

// Herbivore
template<typename species_t>
class Organism<species_t, false, true> {

private:
    species_t m_species;
    uint64_t m_vitality;
public:
    constexpr Organism(const species_t &species, uint64_t vitality)
            : m_species(species), m_vitality(vitality) {}

    constexpr uint64_t get_vitality() const { return m_vitality; }

    const constexpr species_t &get_species() const { return m_species; }

    constexpr bool is_dead() const { return m_vitality == 0; }


};

// Plant
template<typename species_t>
class Organism<species_t, false, false> {

private:
    species_t m_species;
    uint64_t m_vitality;
public:
    constexpr Organism(const species_t &species, uint64_t vitality)
            : m_species(species), m_vitality(vitality) {}

    constexpr uint64_t get_vitality() const { return m_vitality; }

    const constexpr species_t &get_species() const { return m_species; }

    constexpr bool is_dead() const { return m_vitality == 0; }


};

*/


/*
requires requires{

    requires sp1_eats_m || sp2_eats_m;

}
 */

template<typename species_t, bool eat_m, bool eat_p>
constexpr uint64_t given_vitality(const Organism<species_t, eat_m, eat_p> &organism) {
    return organism.get_vitality() / 2;
}

template<typename species_t>
constexpr uint64_t given_vitality(const Plant<species_t> &organism) {
    return organism.get_vitality();
}


template<typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
constexpr std::tuple<
        Organism<species_t, sp1_eats_m, sp1_eats_p>,
        Organism<species_t, sp2_eats_m, sp2_eats_p>,
        std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>>
encounter(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
          Organism<species_t, sp2_eats_m, sp2_eats_p> organism2);


template<typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
requires (sp1_eats_m == sp2_eats_m && sp1_eats_p == sp2_eats_p)
constexpr std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>
get_child(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
          Organism<species_t, sp2_eats_m, sp2_eats_p> organism2) {

    if (organism1.get_species() == organism2.get_species()) {
        return Organism<species_t, sp1_eats_m, sp1_eats_p>
                (organism1.get_species(), (organism1.get_vitality() + organism2.get_vitality()) / 2);
    } else {
        return std::nullopt;
    }
}

template<typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
requires (sp1_eats_m != sp2_eats_m || sp1_eats_p != sp2_eats_p)
constexpr std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>
get_child(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
          Organism<species_t, sp2_eats_m, sp2_eats_p> organism2) {

    return std::nullopt;
}

template<bool eats_m, bool eats_p>
concept is_herbivore = !eats_m && eats_p;

template<bool eats_m, bool eats_p>
concept is_carnivore = eats_m && !eats_p;

template<bool eats_m, bool eats_p>
concept is_omnivore = eats_m && eats_p;

template<bool eats_m, bool eats_p>
concept is_plant = !eats_m && !eats_p;

template<bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
concept can_eat_each_other = sp1_eats_m && sp2_eats_m;

template<bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
concept neither_can_eat_other = (is_herbivore<sp1_eats_m, sp1_eats_p> && is_herbivore<sp2_eats_m, sp2_eats_p>) ||
                                (is_carnivore<sp1_eats_m, sp1_eats_p> && is_plant<sp2_eats_m, sp2_eats_p>) ||
                                (is_plant<sp1_eats_m, sp1_eats_p> && is_carnivore<sp2_eats_m, sp2_eats_p>);


template<bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
concept left_can_eat_right = (sp1_eats_p && is_plant<sp2_eats_m, sp2_eats_p>) ||
                             (sp1_eats_m && is_herbivore<sp2_eats_m, sp2_eats_p>);


template<bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
concept right_can_eat_left = left_can_eat_right<sp2_eats_m, sp2_eats_p, sp1_eats_m, sp1_eats_p>;

// Omnivore vs Carnivore
template<typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
requires can_eat_each_other<sp1_eats_m, sp1_eats_p, sp2_eats_m, sp2_eats_p>
constexpr std::tuple<
        Organism<species_t, sp1_eats_m, sp1_eats_p>,
        Organism<species_t, sp2_eats_m, sp2_eats_p>,
        std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>>
encounter(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
          Organism<species_t, sp2_eats_m, sp2_eats_p> organism2) {

    if (organism1.is_dead() || organism2.is_dead()) {
        return std::tuple(organism1, organism2, std::nullopt);
    }

    auto child = get_child(organism1, organism2);

    if (child.has_value()) {
        return std::tuple(organism1, organism2, child.value());
    }

    using organism1_t = Organism<species_t, sp1_eats_m, sp1_eats_p>;
    using organism2_t = Organism<species_t, sp2_eats_m, sp2_eats_p>;

    // Fight

    if (organism1.get_vitality() == organism2.get_vitality()) {
        organism1_t dead1(organism1.get_species(), 0);
        organism2_t dead2(organism2.get_species(), 0);
        return std::tuple(dead1, dead2, std::nullopt);
    } else if (organism1.get_vitality() > organism2.get_vitality()) {
        organism1_t winner1(organism1.get_species(),
                            organism1.get_vitality() + organism2.get_vitality() / 2);
        organism2_t dead2(organism2.get_species(), 0);
        return std::tuple(winner1, dead2, std::nullopt);
    } else {
        organism1_t dead1(organism1.get_species(), 0);
        organism2_t winner2(organism2.get_species(),
                            organism2.get_vitality() + organism1.get_vitality() / 2);
        return std::tuple(dead1, winner2, std::nullopt);
    }


}

// Herbivore vs Herbivore or Carnivore vs Plant
template<typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
requires neither_can_eat_other<sp1_eats_m, sp1_eats_p, sp2_eats_m, sp2_eats_p>
constexpr std::tuple<Organism<species_t, sp1_eats_m, sp1_eats_p>,
        Organism<species_t, sp2_eats_m, sp2_eats_p>,
        std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>>
encounter(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
          Organism<species_t, sp2_eats_m, sp2_eats_p> organism2) {

    if (organism1.is_dead() || organism2.is_dead()) {
        return std::tuple(organism1, organism2, std::nullopt);
    }

    auto child = get_child(organism1, organism2);

    if (child.has_value()) {
        return std::tuple(organism1, organism2, child.value());
    }

    return std::tuple(organism1, organism2, std::nullopt);
}


template<typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
requires left_can_eat_right<sp1_eats_m, sp1_eats_p, sp2_eats_m, sp2_eats_p>
constexpr std::tuple<
        Organism<species_t, sp1_eats_m, sp1_eats_p>,
        Organism<species_t, sp2_eats_m, sp2_eats_p>,
        std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>>
encounter(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
          Organism<species_t, sp2_eats_m, sp2_eats_p> organism2) {

    if (organism1.is_dead() || organism2.is_dead()) {
        return std::tuple(organism1, organism2, std::nullopt);
    }

    auto child = get_child(organism1, organism2);

    if (child.has_value()) {
        return std::tuple(organism1, organism2, child.value());
    }

    if (organism1.get_vitality() > organism2.get_vitality()) {
        Organism<species_t, sp1_eats_m, sp1_eats_p> winner1(organism1.get_species(),
                                                            organism1.get_vitality() + given_vitality(organism2));
        Organism<species_t, sp2_eats_m, sp2_eats_p> dead2(organism2.get_species(), 0);
        return std::tuple(winner1, dead2, std::nullopt);
    } else {
        return std::tuple(organism1, organism2, std::nullopt);
    }
}


template<typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
requires right_can_eat_left<sp1_eats_m, sp1_eats_p, sp2_eats_m, sp2_eats_p>
constexpr std::tuple<
        Organism<species_t, sp1_eats_m, sp1_eats_p>,
        Organism<species_t, sp2_eats_m, sp2_eats_p>,
        std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>>
encounter(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
          Organism<species_t, sp2_eats_m, sp2_eats_p> organism2) {

    if (organism1.is_dead() || organism2.is_dead()) {
        return std::tuple(organism1, organism2, std::nullopt);
    }

    auto child = get_child(organism1, organism2);

    if (child.has_value()) {
        return std::tuple(organism1, organism2, child.value());
    }

    if (organism2.get_vitality() > organism1.get_vitality()) {
        Organism<species_t, sp1_eats_m, sp1_eats_p> dead1(organism1.get_species(), 0);
        Organism<species_t, sp2_eats_m, sp2_eats_p> winner2(organism2.get_species(),
                                                            organism2.get_vitality() + given_vitality(organism1));
        return std::tuple(dead1, winner2, std::nullopt);
    } else {
        return std::tuple(organism1, organism2, std::nullopt);
    }
}

/*
template<typename species_t>
constexpr std::tuple<Carnivore<species_t>, Carnivore<species_t>, std::optional<Carnivore<species_t>>>
encounter(Carnivore<species_t> organism1, Carnivore<species_t> organism2) {
    if (organism1.is_dead() || organism2.is_dead()) {
        return std::tuple(organism1, organism2, std::nullopt);
    }

    // CHILD

    if (organism1.get_vitality() == organism2.get_vitality()) {
        Carnivore<species_t> dead1(organism1.get_species(), 0);
        Carnivore<species_t> dead2(organism2.get_species(), 0);
        return std::tuple(dead1, dead2, std::nullopt);
    } else if (organism1.get_vitality() > organism2.get_vitality()) {
        Carnivore<species_t> winner1(organism1.get_species(),
                                     (organism1.get_vitality() + organism2.get_vitality()) / 2);
        Carnivore<species_t> dead2(organism2.get_species(), 0);
        return std::tuple(winner1, dead2, std::nullopt);
    } else {
        Carnivore<species_t> dead1(organism1.get_species(), 0);
        Carnivore<species_t> winner2(organism2.get_species(),
                                     (organism2.get_vitality() + organism1.get_vitality()) / 2);
        return std::tuple(dead1, winner2, std::nullopt);
    }


}
*/
/*
template<typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
constexpr std::tuple<Organism<species_t, sp1_eats_m, sp1_eats_p>,
        Organism<species_t, sp2_eats_m, sp2_eats_p>,
        std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>>
encounter(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
          Organism<species_t, sp2_eats_m, sp2_eats_p> organism2) {

    // TODO

    return std::tuple(organism1, organism2, std::nullopt);


}
*/

template<typename species_t, bool eats_m, bool eats_p>
class OrganismAcc {
public:
    Organism<species_t, eats_m, eats_p> m_org;

    constexpr explicit OrganismAcc(const Organism<species_t, eats_m, eats_p> &org) : m_org(org) {}
};

template<typename species_t, bool acc_eat_m, bool acc_eat_p, bool eat_m, bool eat_p>
constexpr void enc(OrganismAcc<species_t, acc_eat_m, acc_eat_p> &acc, const Organism<species_t, eat_m, eat_p> &org) {
    acc.m_org = std::get<0>(encounter(acc.m_org, org));
}


template<typename species_t, bool sp1_eats_m, bool sp1_eats_p, typename ... Args>
constexpr Organism<species_t, sp1_eats_m, sp1_eats_p>
encounter_series(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1, Args ... args) {


    OrganismAcc<species_t, sp1_eats_m, sp1_eats_p> acc(organism1);

    //auto* ptr = new OrganismAcc<species_t, sp1_eats_m, sp1_eats_p>(organism1);

    (..., enc(acc, std::forward<Args>(args)));

    return acc.m_org;


    //return (..., std::get<0>(encounter(organism1, std::forward<Args>(args)) ));


    // ( init op ... op pack )


    /*
    va_list list;


    std::forward<Args>(args)

//    va_end(list);
*/

    return organism1;
}


#endif //JNP_TASK4_ORGANISM_H
