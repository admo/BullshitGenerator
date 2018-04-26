#include "BullshitGenerator.h"

BullshitGenerator::BullshitGenerator(std::istream &input)
        : BullshitGenerator{std::istream_iterator<Word>{input}, std::istream_iterator<Word>{}} {}

void BullshitGenerator::generate(std::ostream &output, std::string word, std::size_t length) const  {
    if (0 == consequentWordsMap.count(word))
        throw std::invalid_argument(word + " not found in input data");

    for (auto i = decltype(length){0}; i < length && !isSentinel(word); ++i, word = getRandomConsequentWord(word))
        output << word << ' ';

    output << '\n';
}

BullshitGenerator::Word BullshitGenerator::getRandomConsequentWord(const Word &word) const {
    const auto& consequentWords = consequentWordsMap.at(word);
    return consequentWords[getRandomWordIndex(consequentWords.size())];
}

BullshitGenerator::WordsNumber BullshitGenerator::getRandomWordIndex(WordsNumber numberOfWords) const {
    return std::uniform_int_distribution<WordsNumber >{0, numberOfWords-1}(randomEngine);
}

bool BullshitGenerator::isSentinel(const BullshitGenerator::Word &word) {
    return word.empty();
}

