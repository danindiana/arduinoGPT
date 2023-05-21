#include <Entropy.h>

void setup()
{
  Serial.begin(115200);
  Entropy.initialize();
}

void loop()
{
  String alphaNumeric = "";
  
  // Generate a string of how many random alphanumeric characters you like by changing the for value (default is 23)
  for(int i = 0; i < 23; i++) {
    int randomNumber = Entropy.random(48, 122);

    // Check if the generated number is in the range of unprintable ASCII characters. 
    // If it is, just move it to a printable character range.
    if (randomNumber > 90 && randomNumber < 97) {
      randomNumber -= 7;
    }

    alphaNumeric += (char)randomNumber;
  }
  
  // Print the random number followed by the alphanumeric string
  int randomNum = Entropy.random();
  Serial.print("Random Number: ");
  Serial.print(randomNum);
  Serial.print(", Alphanumeric String: ");
  Serial.println(alphaNumeric);

  delay(1000);
}
