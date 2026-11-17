# Simple Encryption using XOR - Yash Gupta

This repository documents my exploration of how the XOR operation can be used to simply encrypt and decrypt messages. 

## Topic

XOR (written `^` in C) is a bitwise operation that **outputs 1 only when its inputs differ**:

| A | B | A ^ B |
|:-:|:-:|:-----:|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

**Same inputs → 0:** `0 ^ 0 = 0`, `1 ^ 1 = 0`
**Different inputs → 1:** `0 ^ 1 = 1`, `1 ^ 0 = 1`


## What I explored

### Simple encryption involves three parts

| Part | What it is |
|------|------------|
| **Plain text** | The original message that is being encrypted. |
| **Key** | A mutually decided phrase that can encode and decode data. |
| **Hidden text** | The encrypted data, which can be decoded to reveal the original message. |

### Encoding: XOR the plain text with the key

Every character is stored as a number in binary (ASCII). Using the plain text `"H"` and the key `"K"`:

```
  01001000   PLAIN text  ("H")
^ 01001011   Key         ("K")
= 00000011   HIDDEN text
```

### Decoding: XOR the hidden text with the same key

```
  00000011   HIDDEN text
^ 01001011   Key         ("K")
= 01001000   PLAIN text  ("H")
```



## Most interesting discoveries

### 1. Encrypting and decrypting are the exact same operation

XORing twice with the same key returns the original data:

```
(H ^ K) ^ K = H
```

This works because anything XORed with itself is 0, and anything XORed with 0 stays the same. So my program has no separate "decode" function. It just calls `xor_cipher` a second time.

### 2. Simple XOR isn't the strongest form of encryption

1. The key repeats every `key_len` bytes, so patterns in the message can show through easily
2. It's easy to undo encryption with another XOR call by anyone who has the key
3. It's easy to tamper with by changing the hidden text and subsequently changing the decrypted message

### 3. Simple XOR encryption is as strong as the key

Some common best practices when generating a key:

1. Generate a random string instead of using a known word or phrase
2. Make the key about as long as the message to avoid key repetition
3. Use a unique key for each message you encode



## Writing it in C / Code examples

I wrote a single function, xor_cipher, that encrypts and decrypts. It XORs each character of the text with a character of the key, and the key repeats when it runs out:

```c
void xor_cipher(char *text, int len, const char *key) {
    int key_len = strlen(key);
    for (int i = 0; i < len; i++) {
        text[i] = text[i] ^ key[i % key_len];
    }
}
```

Encrypting the message `"Meet me at noon"` with the key `"secret"`:

```
Original:  Meet me at noon
Original (hex): 4d 65 65 74 20 6d 65 20 61 74 20 6e 6f 6f 6e
Encrypted: 3e 00 06 06 45 19 16 45 02 06 45 1a 1c 0a 0d
Decrypted: Meet me at noon
```

**Try it out!**: `src/xor.c` encrypts and decrypts a phrase. Enter your phrase and a nonempty key when prompted.

```sh
gcc src/xor.c -o xor
./xor
```


## Presentation materials

The slides from my presentation are in [`presentation/Yash_Gupta_-_XOR_Simple_Encryption.pdf`](presentation/Yash_Gupta_-_XOR_Simple_Encryption.pdf).


## Additional resources

- COMP 211 Lecture Slides (Bitwise Operators)
- Cryptographic Storage Cheat Sheet for key generation best practices: https://cheatsheetseries.owasp.org/cheatsheets/Cryptographic_Storage_Cheat_Sheet.html
- Claude for further research on the topic: https://claude.ai/share/02aa3969-d889-4358-8557-4f6ba998ac85


