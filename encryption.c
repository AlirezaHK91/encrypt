#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "cs50.h"

int validateKey(string key);
void encrypt(string originalText, string key);
void decrypt(string ciphertext, string key);

int main(int argc, string argv[])
{
    if (!validateKey(argv[1]))
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    int choice;
    do
    {
        printf("Choose an option:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("0. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        getchar();  

        switch (choice)
        {
            case 1:
                {
                    string originalText = get_string("Enter plaintext to encrypt: ");
                    printf("Encryption result: ");
                    encrypt(originalText, argv[1]);
                    printf("\n");
                    break;
                }

            case 2:
                {
                    string ciphertext = get_string("Enter ciphertext to decrypt: ");
                    printf("Decryption result: ");
                    decrypt(ciphertext, argv[1]);
                    printf("\n");
                    break;
                }

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please enter 1, 2, or 0.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

int validateKey(string substitutionKey)
{
    int length = strlen(substitutionKey);

    if (length != 26)
    {
        printf("Key must contain 26 characters.");
        return 0;
    }

    for (int i = 0; i < length; i++)
    {
        if (!isalpha(substitutionKey[i]))
        {
            return 0;
        }
    }

    for (char j = 'a'; j <= 'z'; j++)
    {
        int count = 0;
        for (int i = 0; i < length; i++)
        {
            if (tolower(substitutionKey[i]) == j)
            {
                count++;
            }
        }
        if (count != 1)
        {
            return 0;
        }
    }

    return 1;
}

void encrypt(string originalText, string substitutionKey)
{
    int length = strlen(originalText);
    for (int i = 0; i < length; i++)
    {
        char outputChar;
        if (isalpha(originalText[i]))
        {
            char firstCharacter = islower(originalText[i]) ? 'a' : 'A';
            char encryptedChar = substitutionKey[originalText[i] - firstCharacter];

            outputChar = islower(originalText[i]) ? tolower(encryptedChar) : toupper(encryptedChar);
        }
        else if (isdigit(originalText[i]))
        {
            
            char encryptedDigit = substitutionKey[originalText[i] - '0' + 26];
            outputChar = encryptedDigit;
        }
        else
        {
            
            outputChar = originalText[i];
        }

        printf("%c", outputChar);
    }
}

void decrypt(string ciphertext, string substitutionKey)
{
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++)
    {
        char outputChar;
        if (isalpha(ciphertext[i]))
        {
            char firstCharacter = islower(ciphertext[i]) ? 'a' : 'A';
            char decryptedChar;

            for (int j = 0; j < 26; j++)
            {
                if (tolower(substitutionKey[j]) == tolower(ciphertext[i]))
                {
                    decryptedChar = j + firstCharacter;
                    break;
                }
            }

            outputChar = islower(ciphertext[i]) ? tolower(decryptedChar) : toupper(decryptedChar);
        }
        else if (isdigit(ciphertext[i]))
        {
            
            char decryptedDigit = substitutionKey[ciphertext[i] - '0'];
            outputChar = decryptedDigit;
        }
        else
        {
            
            outputChar = ciphertext[i];
        }

        printf("%c", outputChar);
    }
}
