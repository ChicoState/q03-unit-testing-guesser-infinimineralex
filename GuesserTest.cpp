/**
 * Unit Tests for the Guesser class
 */

#include <gtest/gtest.h>
#include <string>
#include "Guesser.h"

using std::string;

TEST(GuesserTest, MatchCorrectGuess) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    ASSERT_TRUE(g.match("abcdefghijklmnopqrstuvwxyz"));
}

TEST(GuesserTest, MatchIncorrectGuess) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    ASSERT_FALSE(g.match("aebcdefghijklmnopqrstuvwxyz"));
}

TEST(GuesserTest, MatchDifferentLengthGuess) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    ASSERT_FALSE(g.match("abcdefghijklmnopqrstuvwxyzabcde"));
}

TEST(GuesserTest, MatchEmptyGuess) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    ASSERT_FALSE(g.match(""));
}

TEST(GuesserTest, MatchBruteForceGuess) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    ASSERT_FALSE(g.match("zyxwvutsrqponmlkjihgfedcba"));
}

TEST(GuesserTest, MatchLockedSecret) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    g.match("aebcdefghijklmnopqrstuvwxyz");
    g.match("bcdefghijklmnopqrstuvwxyza");
    g.match("cdefghijklmnopqrstuvwxyzab");
    ASSERT_FALSE(g.match("abcdefghijklmnopqrstuvwxyz"));
}

TEST(GuesserTest, RemainingAfterCorrectGuess) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    g.match("abcdefghijklmnopqrstuvwxyz");
    ASSERT_EQ(g.remaining(), 3);
}

TEST(GuesserTest, RemainingAfterIncorrectGuess) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    g.match("aebcdefghijklmnopqrstuvwxyz");
    ASSERT_EQ(g.remaining(), 2);
}

TEST(GuesserTest, RemainingAfterThreeIncorrectGuesses) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    g.match("aebcdefghijklmnopqrstuvwxyz");
    g.match("bcdefghijklmnopqrstuvwxyza");
    g.match("cdefghijklmnopqrstuvwxyzab");
    ASSERT_EQ(g.remaining(), 0);
}

TEST(GuesserTest, RemainingAfterLockedSecret) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    g.match("aebcdefghijklmnopqrstuvwxyz");
    g.match("bcdefghijklmnopqrstuvwxyza");
    g.match("cdefghijklmnopqrstuvwxyzab");
    g.match("abcdefghijklmnopqrstuvwxyz");
    ASSERT_EQ(g.remaining(), 0);
}

TEST(GuesserTest, ConstructorWithEmptySecret) {
    Guesser g("");
    ASSERT_TRUE(g.match(""));
}

TEST(GuesserTest, ConstructorWithLongSecret) {
    Guesser g("abcdefghijklmnopqrstuvwxyz0123456789");
    ASSERT_FALSE(g.match("abcdefghijklmnopqrstuvwxyz0123456789abcd"));
}

TEST(GuesserTest, MatchWithCaseInsensitiveGuess) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    ASSERT_FALSE(g.match("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}

TEST(GuesserTest, MatchWithNonAlphabeticSecret) {
    Guesser g("abc123!@#$%^&*()_+");
    ASSERT_TRUE(g.match("abc123!@#$%^&*()_+"));
}

TEST(GuesserTest, MatchWithLeadingWhitespaceGuess) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    ASSERT_FALSE(g.match("  abcdefghijklmnopqrstuvwxyz"));
}

TEST(GuesserTest, MatchWithTrailingWhitespaceGuess) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    ASSERT_FALSE(g.match("abcdefghijklmnopqrstuvwxyz  "));
}

TEST(GuesserTest, MatchWithWhitespaceSecret) {
    Guesser g("abc def ghi");
    ASSERT_TRUE(g.match("abc def ghi"));
}

TEST(GuesserTest, MatchWithUnicodeCharacters) {
    Guesser g("àbcdefghijklmnopqrstuvwxyz");
    ASSERT_TRUE(g.match("àbcdefghijklmnopqrstuvwxyz"));
}

TEST(GuesserTest, RemainingAfterMultipleCorrectGuesses) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    g.match("abcdefghijklmnopqrstuvwxyz");
    g.match("aebcdefghijklmnopqrstuvwxyz");
    g.match("abcdefghijklmnopqrstuvwxyz");
    ASSERT_EQ(g.remaining(), 3);
}

TEST(GuesserTest, RemainingAfterMixedGuesses) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    g.match("aebcdefghijklmnopqrstuvwxyz");
    g.match("abcdefghijklmnopqrstuvwxyz");
    g.match("bcdefghijklmnopqrstuvwxyza");
    ASSERT_EQ(g.remaining(), 2);
}

TEST(GuesserTest, MatchWithMaxLengthSecret) {
    string maxLengthSecret(32, 'a');
    Guesser g(maxLengthSecret);
    ASSERT_TRUE(g.match(maxLengthSecret));
}

TEST(GuesserTest, MatchWithTruncatedSecret) {
    Guesser g("abcdefghijklmnopqrstuvwxyz0123456789");
    ASSERT_TRUE(g.match("abcdefghijklmnopqrstuvwxyz012345"));
}

TEST(GuesserTest, MatchWithRepeatedCharactersSecret) {
    Guesser g("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    ASSERT_TRUE(g.match("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
}

TEST(GuesserTest, MatchWithConsecutiveGuesses) {
    Guesser g("abcdefghijklmnopqrstuvwxyz");
    g.match("aebcdefghijklmnopqrstuvwxyz");
    g.match("bcdefghijklmnopqrstuvwxyza");
    g.match("cdefghijklmnopqrstuvwxyzab");
    g.match("defghijklmnopqrstuvwxyzabc");
    ASSERT_EQ(g.remaining(), 0);
}
