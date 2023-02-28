/*
    Diffie Helman Key Exchange with very large (2048 bit) number taken from RFC3526.
    This example is using a BigInteger class from https://github.com/Wholanz/Encrypt-BigInteger/blob/master/%E6%BA%90%E4%BB%A3%E7%A0%81/cpp%E6%96%87%E4%BB%B6/main.cpp
*/ 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include "BigInteger.h"
  
int main() 
{  
  
    std::random_device rd;
    std::mt19937 rng{rd()};  
    std::uniform_int_distribution<uint64_t> uid(1,std::numeric_limits<uint64_t>::max()); 

    /*
        https://datatracker.ietf.org/doc/html/rfc3526#section-3
        2048-bit MODP Group
        This group is assigned id 14.
        In order to fully write out a 2048 bit number, you would need 617 decimal digits.
        This prime is: 2^2048 - 2^1984 - 1 + 2^64 * { [2^1918 pi] + 124476 }
        The generator is: 2.
    */

    BigInteger p("32317006071311007300338913926423828248817941241140239112842009751400741706634354222619689417363569347117901737909704191754605873209195028853758986185622153212175412514901774520270235796078236248884246189477587641105928646099411723245426622522193230540919037680524235519125679715870117001058055877651038861847280257976054903569732561526167081339361799541336476559160368317896729073178384589680639671900977202194168647225871031411336429319536193471636533209717077448227988588565369208645296636077250268955505928362751121174096972998068410554359584866583291642136218231078990999448652468262416972035911852507045361090559"); 
    
    // Generator
    BigInteger g("2");  

    // This is shared for both parties
    std::cout << "p = " << p  << std::endl; 
    std::cout << "g = " << g  << std::endl; 
   
    // Choose a private key a for Alice and compute A = g^a mod p
    BigInteger a(std::to_string(uid(rng)));
    std::cout << "a = " << a  << std::endl; 

    // Compute Public Alice key
    BigInteger A = g.powMod(a,p);  
    std::cout << "A = " << A  << std::endl; 
 
    // Choose a private key b for Bob and compute B = g^b mod p
    BigInteger b(std::to_string(uid(rng)));
    std::cout << "b = " << b << std::endl; 

    // Compute Public Bob key 
    BigInteger B = g.powMod(b,p); 
    std::cout << "B = " << B << std::endl; 

    // Alice and Bob exchange public keys A and B, respectively
    printf("Exchanging public keys\n");
 
    // Compute the shared secret s = B^a mod p = A^b mod p
    BigInteger s1 = B.powMod(a, p);
    BigInteger s2 = A.powMod(b, p);

    // Spit out shared secrets for Alice and Bob
    std::cout << "s1 = " << s1  << std::endl;
    std::cout << "s2 = " << s2  << std::endl;
 
    return 0;
}