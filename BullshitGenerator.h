#pragma once

#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <istream>
#include <random>

class BullshitGenerator {
private:
    using Word = std::string;
    using Words = std::vector<std::string>;
    using WordsNumber = Words::size_type;
    using ConsequentWordsMap = std::map<std::string, Words>;

public:
    explicit BullshitGenerator(std::istream& input);

    template <typename InputIterator>
    BullshitGenerator(InputIterator currentIt, InputIterator lastIt) {
        Word word{sentinel};

        for(;currentIt != lastIt; word = *currentIt++)
            consequentWordsMap[word].emplace_back(*currentIt);

        consequentWordsMap.erase(sentinel);
        consequentWordsMap.try_emplace(*currentIt, Words(1, sentinel));
    }

    BullshitGenerator(const BullshitGenerator&) = default;
    BullshitGenerator(BullshitGenerator&&) noexcept = default;
    BullshitGenerator &operator=(const BullshitGenerator&) = default;
    BullshitGenerator &operator=(BullshitGenerator&&) noexcept = default;

    void generate(std::ostream& output, std::string word, std::size_t length) const;

private:
    Word getRandomConsequentWord(const Word& word) const;
    WordsNumber getRandomWordIndex(WordsNumber numberOfWords) const;
    static bool isSentinel(const Word& word);

    mutable std::default_random_engine randomEngine{std::random_device().operator()()};
    const Word sentinel{};
    ConsequentWordsMap consequentWordsMap;
};
