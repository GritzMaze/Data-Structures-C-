#include <iostream>
#include <set>
#include <string>
#include "hashMap.h"

///
/// Represents a multiset of words
///
/// If you need to see how it is intended to be used,
/// check out the corresponding unit tests
///
/// Implement all methods of this class
///
class WordsMultiset
{
public:
	/// Adds times occurences of word to the container
	///
	/// For example, add("abc") adds the word "abc" once,
	/// while add("abc", 4) adds 4 occurrances.
	void add(const std::string &word, size_t times = 1);

	/// Checks whether word is contained in the container
	bool contains(const std::string &word) const;

	/// Number of occurrances of word
	size_t countOf(const std::string &word) const;

	/// Number of unique words in the container
	size_t countOfUniqueWords() const;

	/// Returns a multiset of all words in the container
	std::multiset<std::string> words() const;

	// You can add additional members if you need to

	void removeOne(const std::string &word);
	// void compareInPercentage(const ComparisonReport &report, const WordsMultiset& file1, const WordsMultiset& file2);
	void print() const;

private:
	HashMap<std::string, int> hash;
};

///
/// Results of the comparison of two streams of words
/// DO NOT modify this class
/// If you need to see how it is intended to be used,
/// check out the corresponding unit tests
///
class ComparisonReport
{
public:
	/// A multiset of all words that exist in both streams
	WordsMultiset commonWords;

	/// Multisets of words unique to the two streams
	/// The first element of the array contains the words that are unique
	/// to the first stream (a) and the second one -- to the second stream (b)
	WordsMultiset uniqueWords[2];
};

///
/// Can be used to compare two streams of words
///
class Comparator
{
public:
	ComparisonReport compare(std::istream &a, std::istream &b);

	// You can add additional members if you need to
	void compareInPercentage(const ComparisonReport &report);

private:
	int file1_words = 0;
	int file2_words = 0;
	int common_words = 0;
};

void WordsMultiset::add(const std::string &word, size_t times)
{
	if (this->contains(word))
	{
		this->hash[word] += times;
	}
	else
	{
		this->hash[word] = times;
	}
}

bool WordsMultiset::contains(const std::string &word) const
{
	return this->hash.contains(word);
}

size_t WordsMultiset::countOf(const std::string &word) const
{
	return hash.countOf(word);
}

size_t WordsMultiset::countOfUniqueWords() const
{
	return hash.size();
}

std::multiset<std::string> WordsMultiset::words() const
{
	return hash.keys();
}

void WordsMultiset::removeOne(const std::string &word)
{
	if (this->contains(word))
	{
		this->hash[word]--;
		if (this->hash[word] == 0)
		{
			this->hash.remove(word);
		}
	}
}

ComparisonReport Comparator::compare(std::istream &a, std::istream &b)
{
	ComparisonReport report;
	std::string word;
	WordsMultiset a_set;
	WordsMultiset b_set;

	while (a >> word)
	{
		a_set.add(word);
		this->file1_words++;
	}

	while (b >> word)
	{
		b_set.add(word);
		this->file2_words++;
	}


	for (std::string word : a_set.words())
	{
		if (b_set.contains(word))
		{
			a_set.removeOne(word);
			b_set.removeOne(word);
			report.commonWords.add(word);
			this->common_words++;
		}
		else
		{
			if (!report.uniqueWords[0].contains(word))
			{
				report.uniqueWords[0].add(word);
			}
		}
	}

	for (std::string word : b_set.words())
	{
		if (!report.uniqueWords[1].contains(word))
		{
			report.uniqueWords[1].add(word);
		}
	}

	return report;
}

void WordsMultiset::print() const
{
	for (std::string word : this->words())
	{
		std::cout << word << " ";
	}
}

void Comparator::compareInPercentage(const ComparisonReport &report)
{

	int percentageF1 = (this->common_words) * 100 / this->file1_words;
	int percentageF2 = (this->common_words) * 100 / this->file2_words;


	std::cout << "file1 contains " << this->file1_words << " words and "
			  << this->common_words << " are also in file2 (" << percentageF1 << "%)"
			  << std::endl;

	std::cout << "file2 contains " << this->file2_words << " words and "
			  << this->common_words << " are also in file1 (" << percentageF2 << "%)"
			  << std::endl;
	return;
}