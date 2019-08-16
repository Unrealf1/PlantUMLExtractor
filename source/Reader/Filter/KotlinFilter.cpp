//
// Created by fedor on 8/15/19.
//

#include "Reader/Filter/KotlinFilter.hpp"

std::vector<std::string> KotlinFilter::filterSource(std::ifstream& fileStream) const {
    filter_state state = filter_state::out_of_comment;
    char last = 0;
    char current = 0;

    std::vector<std::string> words;
    std::string current_word;

    while ((current = fileStream.get()) != EOF) {
        if (state == filter_state::out_of_comment) {
            if (current == '/' && last == '/') {
                state = filter_state::inside_inline;
                words.pop_back();
            } else if (current == '*' && last == '/') {
                state = filter_state::inside_multi;
                words.pop_back();
            } else if (isspace(current)) {
                if (!current_word.empty()) {
                    words.emplace_back(current_word);
                    current_word.clear();
                }
            } else if (current == '"') {
                state = filter_state::inside_string;
            } else if(!isalnum(current) && current != '_' && current != '-') {
                if (!current_word.empty()) {
                    words.emplace_back(current_word);
                    current_word.clear();
                }
                words.emplace_back(1, current);
            } else {
                    current_word.push_back(current);
            }
        }
        else if (state == filter_state::inside_inline && current == '\n') {
            state = filter_state::out_of_comment;
        }
        else if (state == filter_state::inside_multi && current == '/' && last == '*') {
            state = filter_state::out_of_comment;
        }
        else if (state == filter_state::inside_string) {
            if (current == '"') {
                state = filter_state::out_of_comment;
            }
        }
        last = current;
    }
    fileStream.close();
    return words;
}

