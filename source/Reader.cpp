//
// Created by fedor on 8/10/19.
//

#include <cstdint>
#include "Reader.hpp"

namespace PUMLE {
    Reader::Reader(const std::string &filename)
    :ifstr(filename) {

    }

    std::string Reader::ClearName(const std::string& name) const {
        size_t length = 0;
        for (char c : name) {
            if (!isalpha(c)) {
                break;
            }
            ++length;
        }
        return name.substr(0, length);
    }

    ClassSource Reader::FindClass(const std::string &classname) {
        ClassSource result;
        result.classname = classname;

        auto words = filterSource();
        bool priv = false;
        search_state current_state = search_state::normal;
        uint32_t figure_balance = 0;
        for(auto& word : words) {
            if (current_state == search_state::finished) {
                break;
            }


            switch (current_state){
                case search_state::normal: {
                    if (word == "class") {
                        current_state = search_state::in_class;
                    }
                    break;
                }
                case search_state::finished: {
                    break;
                }
                case search_state::in_class: {
                    if (word.find(classname) != std::string::npos) {
                        current_state = search_state::in_correct_class;
                    } else {
                        current_state = search_state ::normal;
                    }
                    break;
                }
                case search_state::in_correct_class: {
                    if (figure_balance == 1 && word == "private") {
                        priv = true;
                    } else if (figure_balance == 1 && word == "fun") {
                        current_state = search_state::in_function;
                    } else if (figure_balance == 1 && (word == "val" || word == "var")) {
                        current_state = search_state ::in_member;
                    } else if(figure_balance == 1 && word == "class") {
                        current_state = search_state::in_inner;
                    } else if (word.find('{') != std::string::npos) {
                        ++figure_balance;
                    } else if (word.find('}') != std::string::npos) {
                        --figure_balance;
                        if(figure_balance == 0) {
                            current_state = search_state::finished;
                        }
                    }
                    break;
                }
                case search_state::in_function: {
                    word = ClearName(word);
                    if (priv) {
                        priv = false;
                        result.private_functions.push_back(word);
                    } else {
                        result.public_functions.push_back(word);
                    }
                    current_state = search_state::in_correct_class;
                    break;
                }
                case search_state::in_member: {
                    word = ClearName(word);
                    if (priv) {
                        priv = false;
                        result.private_members.push_back(word);
                    } else {
                        result.public_members.push_back(word);
                    }
                    current_state = search_state::in_correct_class;
                    break;
                }
                case search_state::in_inner: {
                    word = ClearName(word);
                    priv = false;
                    result.inner_classes.push_back(word);
                    current_state = search_state::in_correct_class;
                    break;
                }
            }
        }
        return result;
    }

    std::vector<std::string> Reader::filterSource() {
        filter_state state =filter_state ::out_of_comment;
        char last = 0;
        char current = 0;

        std::vector<std::string> words;
        std::string current_word;

        while ((current = ifstr.get()) != EOF) {
            if (state == filter_state::out_of_comment) {
                if (current == '/' && last == '/') {
                    state = filter_state::inside_inline;
                    current_word.pop_back();
                } else if (current == '*' && last == '/') {
                    state = filter_state::inside_multi;
                    current_word.pop_back();
                } else if (isspace(current)) {
                    if (!current_word.empty()) {
                        words.push_back(current_word);
                        current_word.clear();
                    }
                } else if (current == '"') {
                    state = filter_state::inside_string;
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
        return words;
    }
}