#include <iostream>
#include <ctime>
// TripleX


int rand_num_gen(int *level) {
    // helper function that generates a random int based of level
    return rand() % (*level + 1);
}


bool combination(int *level, int *tries) {
    /*
    * the combination game, return false if 'tries' is 0
    * return true if the user guesses the combinations correctly
    */
    // setup the secret combinations with random numbers
    srand(time(NULL));  // create new random sequence based on time of day
    int code_a = rand_num_gen(level),
        code_b = rand_num_gen(level),
        code_c = rand_num_gen(level);

    int code_sum = code_a + code_b + code_c;
    int code_product = code_a * code_b * code_c;
    int guess_a = 0, guess_b = 0, guess_c =0, guess_sum = 0, guess_product = 0;

    while (*tries > 0) {
        // ask for the user's combination inputs
        std::cout << "### Level " << *level << " ###" << std::endl;
        std::cout << "The sum of the combination is: " << code_sum << std::endl;
        std::cout << "The product of the combination is: " << code_product << std::endl;
        std::cout << "You need to enter the correct combinations to continue" << std::endl;
        std::cout << "Enter combinations ... (e.g. 5 16 2)" << std::endl;
        std::cin >> guess_a;
        std::cin >> guess_b;
        std::cin >> guess_c;

        // check whether the user has guessed the combinations correctly
        guess_sum = guess_a + guess_b + guess_c;
        guess_product = guess_a * guess_b * guess_c;

        // allow retry if 'tries' is greater than 0
        if (guess_sum != code_sum || guess_product != code_product) {
            --*tries;
            std::cout << "Combinations incorrect - Remaining chances: " << *tries << "\n" << std::endl;
        } else {
            ++*level;
            std::cout << "The combinations you entered is correct" << std::endl;
            std::cout << std::endl;
            return true;
        }
    }

    std::cout << "\n*** Mission failed :( ***\n" << std::endl;
    return false;
}


int main() {
    /*
     * TripleX - guess combinations and get into the server room
    */
    // print storyline messages
    const int max_level = 10;
    std::cout << "\n\nYou are a secret agent breaking into a secure server room." << std::endl;
    std::cout <<
        "There are " << max_level << " levels, and each requires 3 combinations to unlock ...\n\n"
    << std::endl;

    int level = 1, tries = 3;
    bool success = true;
    while (level <= max_level) {
        success = combination(&level, &tries);
        // clean up stdin buffer
        std::cin.clear();
        std::cin.ignore();

        if (success == false) {
            goto EXIT;
        }
    }
    std::cout << "\n*** You have successfully entered the server room! ***\n" << std::endl;

    EXIT:return 0;
}

