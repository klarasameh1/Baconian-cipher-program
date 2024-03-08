#include <iostream>
#include <vector>
#include <cctype> 
#include <algorithm> 
#include <limits>
using namespace std;

/*
Function to encrypting
Takes two parameters:
 1)message:the input 
 2)ciphertaple:to search for equivalenet cipher in it
 */
string encrypt(string message, vector<string> cipherTable) {
    string cipher;         
    //for each letter in the input
    for (char letter : message) {
        // Check if the character is a letter
        if (isalpha(letter)) {        
            //switching each letter to uppercase one
            //and declaring "index" variable it's value = the subtract between ascii value of the letter and 'A'
            // to be easy to compare them with cipher code in the list of ciphers
            //for example>> index of'c'= C-A = 67-65 = 2
            //and this is right if we arrange the alphapet in a vector as A=0,B=1,C=2
            int index = toupper(letter) - 'A';   
            //Map the letter in the ciphertable  
            if (index >= 0 && index < 26) 
                cipher += cipherTable[index];
        }

        //else if it's a number or special characters write it as it is     
        else 
            cipher += letter;    
    }
    return cipher;
}


/*
Function to decrypting
Takes two parameters:
 1)Ciphermessage:the input that is written by baconian cipher
 2)ciphertaple:to search for equivalenet letter in it
 */
string decrypt(string ciphermessage, vector<string> cipherTable) {
    string text;                // the resulted text
    string substr;
    
    // for each character in the ciphermessage
    for (char letter : ciphermessage) {
        if (isalpha(letter)) {          // Check if the character is a letter
            substr += letter;           // Add the character to the substring
            if (substr.length() == 5) { // If the substring length is 5, check it
                // Search for the substring in ciphertable
                //by "find" substr in ciphertable from "begin" to "end"
                auto substr_i = find(cipherTable.begin(), cipherTable.end(), substr);
                if (substr_i != cipherTable.end()) {     // If the substring isn't found
                    int index = distance(cipherTable.begin(), substr_i); // Calculate the index of the found substring
                    char decryptedChar = 'A' + index;                    // Calculate the corresponding character
                    text +=decryptedChar;       // Append the decrypted character to the result text
                }
                substr.clear(); // Clear the substring for the next group
            }
        } 
        else {
            text += letter;   // Add the character unchanged if it's not a letter(like nums or special characters)
        }
    }
    return text;
}


int main() {
    // Cipher table a vector as a dictionery for baconian cipher 
    //it be added here to can acess to all functions
    vector<string> cipherTable = {
        "aaaaa", "aaaab", "aaaba", "aaabb", "aabaa",
        "aabab", "aabba", "aabbb", "abaaa", "abaab",
        "ababa", "ababb", "abbaa", "abbab", "abbba",
        "abbbb", "baaaa", "baaab", "baaba", "baabb",
        "babaa", "babab", "babba", "babbb", "bbaaa",
        "bbaab"
    };

    cout << "\n\t\t🖥️   Welcome to Baconian Ciphering Program 🖥️ \n";
    
    while (true) {
        string choice;
        cout <<"\nWhat do you like to do ? :" << endl
             << "A) Cipher a message" << endl
             << "B) Decipher a message" << endl
             << "C) Exit the program" << endl
             << ">> Enter your choice: ";
        cin >> choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper);     // Convert to uppercase
        
        if (choice.length() == 1 && (choice[0] == 'A' || choice[0] == 'B' || choice[0] == 'C')) {
                //Encrypting
                if (choice == "A" ) {
                    cout << "Please enter the message to cipher it:" << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                    string line;
                    getline(cin, line);    // Read all the line
                    cout <<"The encrypted message is : \n"<< encrypt(line, cipherTable)<<endl;
                    
                } 
                
                //Decrypting
                else if (choice == "B") {
                    cout << "Please enter the message to decipher it:" << endl;    
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                    string line;        
                    getline(cin, line);         // Read all the line
                    cout <<"The decrypted message is : \n"<< decrypt(line, cipherTable)<< endl;

                } 
                
                //Exiting
                else if (choice == "C") {
                    cout << "Exiting the program.....😊" << endl;
                    break; // Terminate the loop to exit the program
                } 
            }
        else {
            cout << "\nInvalid choice. Please enter A, B, or C: " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
          }
       }
  return 0;
}
