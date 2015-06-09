/***********************************************************************
 * Program:
 *    Exploration 3, Bigness
 *    Brother Neff, CS237
 *
 * Author:
 *    Your Name Here
 *
 * Summary:
 *    RSA Encryption/Decryption Function Definitions using ZZ 
 *
 ***********************************************************************/

#include <cassert>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "words.h"
#include <NTL/ZZ.h>

NTL_CLIENT

/*****************************************************************************
 * Find b^n % m.
 *****************************************************************************/
ZZ modPow(ZZ& b, ZZ& n, ZZ& m)
{
   return to_ZZ(1);
}

/*****************************************************************************
 * Find s such that a * s is congruent to 1 (mod m).
 *****************************************************************************/
ZZ findInverse(ZZ& a, ZZ& m)
{
   return to_ZZ(1);
}

/****************************************************************************
 * Convert from a text message representing a base 27 number to a ZZ number.
 ****************************************************************************/
ZZ fromBase27(string message)
{
   return to_ZZ(1);
}

/****************************************************************************
 * Convert from a ZZ number to a base 27 number represented by a text message.
 ****************************************************************************/
string toBase27(const ZZ& n)
{
   return "";
}

/****************************************************************************
 * Find a suitable e for a ZZ number that is the "totient" of two primes.
 ****************************************************************************/
ZZ findE(const ZZ& t)
{
   return to_ZZ(1);
}

/*****************************************************************************
 * Find suitable primes p and q for encrypting a ZZ number that is the message.
 *****************************************************************************/
void findPandQ(const ZZ& m, ZZ& p, ZZ& q)
{
}

/*************************************************************************
 * learned
 *
 * Tells interested parties what you learned.
 *
 * Use one or more calls to out(...), or else see the whatIlearned
 * script and do the following:
 *
 *   Words words = {
 *   #include "whatIlearned.inc"
 *   nl};
 *   cout << words;
 *************************************************************************/
void learned()
{
}

/*************************************************************************
 * usage
 *
 * Tells the user how to use the program.
 *************************************************************************/
void usage(const char* programName)
{
}
