//
// Created by fedor on 8/10/19.
//

#include <cstdint>
#include <iostream>
#include "Reader/KotlinReader.hpp"

namespace PUMLE {
    KotlinReader::KotlinReader(std::ifstream& fileStream)
    :fileStream(fileStream) {}

    std::string KotlinReader::ClearName(const std::string& name) const {
        size_t length = 0;
        for (char c : name) {
            if (!isalpha(c)) {
                break;
            }
            ++length;
        }
        return name.substr(0, length);
    }

    ClassSource KotlinReader::ExtractClass(const std::string &classname) {
        ClassSource result;
        result.classname = classname;

        InitWords();

        bool priv = false;
        search_state current_state = search_state::normal;
        uint32_t figure_balance = 0;
        for(auto& word : words) {
            if (current_state == search_state::finished) {
                break;
            }

            switch (current_state){
                case search_state::normal: {
                    if (word == "class" || word == "object") {
                        current_state = search_state::in_class;
                    }
                    break;
                }
                case search_state::finished: {
                    break;
                }
                case search_state::in_class: {
                    if (word == classname) {
                        current_state = search_state::in_correct_class;
                    } else {
                        current_state = search_state ::normal;
                    }
                    break;
                }
                case search_state::in_correct_class: {
                    bool balance = (figure_balance <= 1);

                    if (balance && word == "private") {
                        priv = true;
                    } else if (balance && word == "fun") {
                        current_state = search_state::in_function;
                    } else if (balance && (word == "val" || word == "var")) {
                        current_state = search_state ::in_member;
                    } else if(balance && (word == "class" || word == "object")) {
                        current_state = search_state::in_inner;
                    } else if (word == "{") {
                        ++figure_balance;
                    } else if (word == "}") {
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
                    if (word == "{") {
                        result.inner_classes.push_back("companion(" + classname + ")");
                    } else {
                        word = ClearName(word);
                        priv = false;
                        result.inner_classes.push_back(word);
                    }
                    current_state = search_state::in_correct_class;
                    break;
                }
            }
        }
        return result;
    }

    std::vector<std::string> KotlinReader::GetAllClasses() {
        auto initialStreamPosition = fileStream.tellg();

        search_state current_state = search_state::normal;
        std::vector<std::string> result;
        InitWords();

        for (auto& word : words) {
            switch (current_state) {
                case search_state::normal: {
                    if (word == "class" || word == "object") {
                        current_state = search_state::in_class;
                    }
                    break;
                }
                case search_state::in_class: {
                    if (word == "{") {
                        //TODO: get, to what class thi is a companion and produce correct name
                    } else if (word.size() == 1 && !isalnum(word[0])){
                        //do nothing
                    } else {
                        result.emplace_back(word);
                    }
                    current_state = search_state::normal;
                    break;
                }
            }
        }

        fileStream.seekg(initialStreamPosition);

        return result;
    }

    void KotlinReader::InitWords() {
        if (words.empty()) {
            words = KotlinFilter().filterSource(fileStream);
        }
        if (words.empty()) {
            throw NoWords();
        }
    }
}