#include <Entropy.h>

const char consonants[] = "bcdfghjklmnpqrstvwxyz";
const char vowels[] = "aeiou";

char getRandomConsonant() {
  int index = Entropy.random(sizeof(consonants) - 1);
  return consonants[index];
}

char getRandomVowel() {
  int index = Entropy.random(sizeof(vowels) - 1);
  return vowels[index];
}

String generatePseudoword() {
  int length = Entropy.random(2, 11);
  String word = "";
  
  for (int i = 0; i < length; i++) {
    word += getRandomConsonant();
    if (Entropy.random(2) == 0 && word.length() < length) {
      word += getRandomVowel();
    }
  }

  return word;
}

void setup()
{
  Serial.begin(115200);
  Entropy.initialize();
}

void loop()
{
  String alphaNumeric = "";
  
  // Generate a string of 5 random alphanumeric characters
  for(int i = 0; i < 5; i++) {
    int randomNumber = Entropy.random(48, 122);
    
    if (randomNumber > 90 && randomNumber < 97) {
      randomNumber -= 7;
    }

    alphaNumeric += (char)randomNumber;
  }

  String pseudoword = generatePseudoword();
  
  int randomNum = Entropy.random();
  Serial.print("Random Number: ");
  Serial.print(randomNum);
  Serial.print(", Alphanumeric String: ");
  Serial.print(alphaNumeric);
  Serial.print(", Pseudoword: ");
  Serial.println(pseudoword);

  delay(1000);
}
