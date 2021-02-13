#include "ApplicationWordListGenerator.h"

/**
 * Constructor opens the words dictionary and reads its contents. It also sets the application log data structure.
 *
 * @param curr_log application log object.
 */
ApplicationWordListGenerator::ApplicationWordListGenerator(ApplicationStatusLog* curr_log) {

    status_log = curr_log;
    status_log->add("Reading Word-List.txt");

    input_file.open("VideoEditor/src/util/Words-List-File/Words-List.txt", ifstream::in);
    string input_word {};

    while(getline(input_file, input_word)) {
    /* Build word list: */

        words_list.push_back(input_word);

    }

    input_file.close();

    status_log->add("[SUCCESS] Word list constructed.");

}

/**
 * Compute a fresh list of random words.
 *
 * @param word_count the number of words the list must contain.
 * @return random_word_list new random words list.
 */
const vector<string> &ApplicationWordListGenerator::get_new_list(int word_count) {

    status_log->add("Generating new random word list.");

    random_word_list = vector<string>();  // initializing vector of size word_count.
    vector<long> random_index {get_random_index_list(word_count)};

    for (int i = 0; i < word_count; ++i) {

        random_word_list.push_back(words_list.at(random_index.at(i)));  // add word at random index to new list.

    }

    status_log->add("[Success] New random word list generated.");

    return random_word_list;

}

/**
 * Traverse the word list being used currently and add words that aren't in Word-List.txt to the file.
 *
 * @param new_list the current list being used to build new application output.
 */
void ApplicationWordListGenerator::verify_custom_list(const vector<string> & current_list) {

    ofstream output_file("./Word-List-File/Word-List.txt", ofstream::app);

    if (unique_words_list.empty()) {

        for (const string & input_word: words_list) {
            /* Building word list by reading words from input file one line at a time: */

            unique_words_list.insert(input_word);
        }

    }

    for (const string & current_word: current_list) {
        /* Check if Word-List.txt has the current word in it, if it doesn't add it: */

        auto it {unique_words_list.find(current_word)};

        if (it == unique_words_list.end()) {

            unique_words_list.insert({current_word});
            output_file << current_word << endl;

        }

    }

    output_file.close();

}

/**
 * Compute a list of random indices that can be used to access elements in the ApplicationWordListGenerator::words_list object.
 *
 * @param target_count the number of random indices to return.
 * @return index_list the list of indices.
 */
vector<long int> ApplicationWordListGenerator::get_random_index_list(int target_count) {

    unsigned seed {static_cast<unsigned>(system_clock::now().time_since_epoch().count())};
    default_random_engine generator (seed);
    uniform_int_distribution<long> distribution(0, static_cast<long>(words_list.size() - 1));

    unordered_set<long> current_list_indices;
    vector<long> index_list(target_count);
    int current_count {0};

    while (current_count < target_count){

        long index_value {};
        auto it {current_list_indices.begin()};

        while (it != current_list_indices.end()) {

            index_value = distribution(generator);
            it = current_list_indices.find(index_value);

        }

        current_list_indices.insert(index_value);

        index_list.at(current_count) = index_value;
        ++current_count;

    }

    return index_list;

}

const vector<string> &ApplicationWordListGenerator::get_current_list() {

    return random_word_list;

}
