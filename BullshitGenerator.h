#pragma once

#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <istream>
#include <random>

namespace bullshit {
using Word = std::string;
using Words = std::vector<Word>;
using WordsNumber = Words::size_type;
using ConsequentWordsMap = std::map<Word, Words>;

template <typename InputIterator>
ConsequentWordsMap read(InputIterator currentIt, InputIterator lastIt) {
    ConsequentWordsMap consequentWordsMap;
    const Word sentinel{};

    if (currentIt == lastIt)
        return consequentWordsMap;

    for (Word const *firstWord{&sentinel}, *secondWord{&*currentIt}; currentIt != lastIt; ++currentIt) {
        auto& words = consequentWordsMap[*firstWord];
        words.push_back(*secondWord);
        firstWord = &words.back();
    }

    consequentWordsMap.erase(Word{});
    consequentWordsMap.try_emplace(*currentIt, Words(1, Word{}));

    return consequentWordsMap;
}

ConsequentWordsMap read(std::istream &input);

void generate(std::ostream &output, ConsequentWordsMap const &consequentWordsMap, Word const &word, std::size_t length);
}