import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

// Custom exception class for modulus errors
class customException extends Exception {
    public customException(String message) {
        super(message);
    }
}

public class VigenereCipherCustomASCII {

    // Custom ASCII array (Subset of characters)
    // static char ascii[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    //                        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    //                        '0','1','2','3','4','5','6','7','8','9'};
    
    static char ascii[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};
    //static char ascii[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    // Custom modulus function
    static int properModulus(int a, int b) throws customException {
        int r = 0;
        int q = 0;
        int newQ = 0;
        int newP = 0;
        int newR = 0;

        if(b > a)
        {
            int hold = a;
            a = b;
            b = hold;
        }

        // First, check for 0 value inputs.
        if (b == 0 || (a == 0 && b == 0)) {
            throw new customException("You input b = 0 or a = 0 and b = 0");
        }

        if (a >= 0 && b > 0 || a > 0 && b < 0) {  // Second, check for positive inputs.
            r = a % b;
            q = a / b;
            System.out.println(a + " = "+ b + " * " + newQ + " + " + r);
            return r;
        } else if (a < 0 && b > 0) {  // Third, check for negative a and positive b.
            newQ = a / b;
            newQ = newQ + -1;
            newP = newQ * b;
            newR = a - newP;
            System.out.println(a + " = "+ b + " * " + newQ + " + " + newR);

        } else if (a < 0 && b < 0) {  // Fourth, check for negative a and b.
            newQ = a / b;
            newQ = Math.abs(newQ);
            newQ = newQ + 1;
            newP = newQ * b;
            newR = a - newP;
            System.out.println(a + " = "+ b + " * " + newQ + " + " + newR);
        }

        return newR;
    }

    // Find the index of a character in the ascii array
    public static int findIndex(char c) {
        for (int i = 0; i < ascii.length; i++) {
            if (ascii[i] == c) {
                return i;
            }
        }
        return -1;  // Character not found
    }

    // Encrypt the text using the custom ascii array and key
    public static String encrypt(String text, String key) {
        StringBuilder result = new StringBuilder();
        
        for (int i = 0, j = 0; i < text.length(); i++) {
            char c = text.charAt(i);
            int textIndex = findIndex(c);

            if (textIndex != -1) {  // Character found in the custom array
                try {
                    int keyIndex = findIndex(key.charAt(j % key.length()));
                    int encryptedIndex = properModulus(textIndex + keyIndex, ascii.length);
                    result.append(ascii[encryptedIndex]);
                    j++;
                } catch (customException e) {
                    System.out.println("Error: " + e.getMessage());
                    return null;
                }
            } else {
                result.append(c);  // Keep non-custom characters unchanged
            }
        }
        return result.toString();
    }

    // Decrypt the text using the custom ascii array and key
    public static String decrypt(String text, String key) {
        StringBuilder result = new StringBuilder();
        
        for (int i = 0, j = 0; i < text.length(); i++) {
            char c = text.charAt(i);
            int textIndex = findIndex(c);

            if (textIndex != -1) {  // Character found in the custom array
                try {
                    int keyIndex = findIndex(key.charAt(j % key.length()));
                    int decryptedIndex = properModulus(textIndex - keyIndex, ascii.length);
                    result.append(ascii[decryptedIndex]);
                    j++;
                } catch (customException e) {
                    System.out.println("Error: " + e.getMessage());
                    return null;
                }
            } else {
                result.append(c);  // Keep non-custom characters unchanged
            }
        }
        return result.toString();
    }

    // Read the content of a file and return it as a string
    public static String readFile(String fileName) {
        StringBuilder content = new StringBuilder();
        try {
            File file = new File(fileName);
            Scanner fileReader = new Scanner(file);
            while (fileReader.hasNextLine()) {
                content.append(fileReader.nextLine()).append("\n");
            }
            fileReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("Error: File not found.");
            return null;
        }
        return content.toString();
    }

    // Main menu to select encryption, decryption, or file reading
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("Vigenère Cipher (Custom ASCII-based)");
            System.out.println("1. Encrypt");
            System.out.println("2. Decrypt");
            System.out.println("3. Encrypt file (plain.txt)");
            System.out.println("4. Exit");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline
            
            if (choice == 1) {
                System.out.print("Enter the text to encrypt: ");
                String text = scanner.nextLine();
                System.out.print("Enter the key: ");
                String key = scanner.nextLine();
                String encrypted = encrypt(text, key);
                if (encrypted != null) {
                    System.out.println("Encrypted text: " + encrypted);
                }
            } else if (choice == 2) {
                System.out.print("Enter the text to decrypt: ");
                String text = scanner.nextLine();
                System.out.print("Enter the key: ");
                String key = scanner.nextLine();
                String decrypted = decrypt(text, key);
                if (decrypted != null) {
                    System.out.println("Decrypted text: " + decrypted);
                }
            } else if (choice == 3) {
                // Read from plain.txt and encrypt the data
                System.out.print("Enter the key to encrypt the file: ");
                String key = scanner.nextLine();
                String fileContent = readFile("plain0.txt");
                if (fileContent != null) {
                    String encrypted = encrypt(fileContent, key);
                    if (encrypted != null) {
                        System.out.println("Encrypted file content: ");
                        System.out.println(encrypted);
                    }
                }
            } else if (choice == 4) {
                System.out.println("Exiting...");
                break;
            } else {
                System.out.println("Invalid option, please try again.");
            }
            System.out.println();
        }
        scanner.close();
    }
}
