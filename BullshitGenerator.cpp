#include "BullshitGenerator.h"

namespace bullshit {
namespace {

static std::default_random_engine randomEngine{std::random_device().operator()()};

bool isSentinel(Word const* word) {
    return word->empty();
}

WordsNumber getRandomWordIndex(WordsNumber numberOfWords) {
    return std::uniform_int_distribution<WordsNumber>{0, numberOfWords-1}(randomEngine);
}

Word const* getRandomConsequentWord(const ConsequentWordsMap& consequentWordsMap, Word const* word) {
    auto const & consequentWords = consequentWordsMap.at(*word);
    return consequentWords.data() + getRandomWordIndex(consequentWords.size());
}
}

void generate(std::ostream &output, const ConsequentWordsMap &consequentWordsMap, Word const &firstWord, std::size_t length) {
    Word const *currentWord = &firstWord;

    for (auto i = decltype(length){0}; i < length && !isSentinel(currentWord); ++i, currentWord = getRandomConsequentWord(consequentWordsMap, currentWord))
        output << *currentWord << ' ';

    output << '\n';
}

ConsequentWordsMap read(std::istream &input) {
    return bullshit::read(std::istream_iterator<Word>{input}, std::istream_iterator<Word>{});
}
}
