#include "Dependencies.h"
#include "ApplicationStatusLog.h"

#ifndef VIDEOEDITORAPP_APPLICATIONWORDLIST_H
#define VIDEOEDITORAPP_APPLICATIONWORDLIST_H


class ApplicationWordListGenerator {

    unordered_set<string> unique_words_list;
    vector<string> words_list;
    ifstream input_file;
    vector<string> random_word_list;
    ApplicationStatusLog* status_log {nullptr};

public:
    explicit ApplicationWordListGenerator(ApplicationStatusLog*);
    ~ApplicationWordListGenerator() = default;

    const vector<string> & get_current_list();
    const vector<string> & get_new_list(int word_count);

    void set_updated_list(vector<string> & updated_list);

private:

    vector<long int> get_random_index_list(int count);
    void verify_custom_list(const vector<string> & new_list);


};


#endif//VIDEOEDITORAPP_APPLICATIONWORDLIST_H
