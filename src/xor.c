#include <stdio.h>
#include <string.h>

// XOR each character with the key, repeating the key as needed.
void xor_cipher(char *text, int len, const char *key) {
    int key_len = strlen(key);
    for (int i = 0; i < len; i++) {
        text[i] = text[i] ^ key[i % key_len];
    }
}

int main(void) {
    char text[1025];
    char key[1025];

    printf("Enter original phrase: ");
    if (fgets(text, sizeof(text), stdin) == NULL) return 1;
    text[strcspn(text, "\n")] = '\0';  // remove the newline

    printf("Enter key: ");
    if (fgets(key, sizeof(key), stdin) == NULL) return 1;
    key[strcspn(key, "\n")] = '\0';
    int len = strlen(text);

    printf("Original:  %s\n", text);
    printf("Original (hex): ");
    for (int i = 0; i < len; i++) {
        printf("%02x ", (unsigned char)text[i]);
    }
    printf("\n");

    // Encryption: plain text ^ key = hidden text
    xor_cipher(text, len, key);
    printf("Encrypted: ");
    for (int i = 0; i < len; i++) {
        printf("%02x ", (unsigned char)text[i]);
    }
    printf("\n");

    // Decryption: hidden text ^ key = plain text (the same call)
    xor_cipher(text, len, key);
    printf("Decrypted: %s\n", text);

    return 0;
}
