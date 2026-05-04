#include <iostream>
#include "Array.h"

int main() {
    try {
        // Create an Array of integers with length 5
        Array<int> intArray(5);

        // Set values using the overloaded operator[]
        for (int i = 0; i < intArray.length(); ++i) {
            intArray[i] = i * 10;
        }

        // Get and print values using the overloaded operator[]
        std::cout << "intArray elements: ";
        for (int i = 0; i < intArray.length(); ++i) {
            std::cout << intArray[i] << " ";
        }
        std::cout << std::endl;

        // Demonstrate out-of-bounds access (will throw an exception)
        try {
            std::cout << "Accessing out of bounds: " << intArray[10] << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }

        // Create an Array of strings with length 3
        Array<std::string> strArray(3);

        // Set values
        strArray[0] = "Hello";
        strArray[1] = "World";
        strArray[2] = "Array";

        // Print values
        std::cout << "strArray elements: ";
        for (int i = 0; i < strArray.length(); ++i) {
            std::cout << strArray[i] << " ";
        }
        std::cout << std::endl;

        // Array will automatically be deleted when it goes out of scope

    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}
