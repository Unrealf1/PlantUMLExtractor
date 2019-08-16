//
// Created by fedor on 8/10/19.
//

#include <cstdint>
#include <iostream>
#include "Reader/KotlinReader.hpp"

namespace PUMLE {
    KotlinReader::KotlinReader(std::ifstream& fileStream)
    :fileStream(fileStream) {}

    ClassType KotlinReader::checkForClassType(const std::string& word) const {
        if (word == "class") {
            return ClassType::Class;
        } else if(word == "object") {
            return ClassType::Object;
        }  else if(word == "enum") {
            return ClassType::Enum;
        } else {
            return ClassType::None;
        }
    }

    ClassSource KotlinReader::ExtractClass(const std::string &classname) {
        ClassSource result;
        result.classname = classname;

        InitWords();

        bool private_flag = false;
        ClassType lastClassType = ClassType::None;

        search_state current_state = search_state::normal;
        uint32_t figure_balance = 0;
        for(auto& word : words) {
            if (current_state == search_state::finished) {
                break;
            }

            switch (current_state){
                case search_state::normal: {
                    if (lastClassType != ClassType::Enum) {
                        lastClassType = checkForClassType(word);
                    }

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
                        result.type = lastClassType;
                        if (lastClassType == ClassType::Enum) {
                            current_state = search_state::in_correct_enum;
                        } else {
                            current_state = search_state::in_correct_class;
                        }
                    } else {
                        lastClassType = ClassType::None;
                        current_state = search_state::normal;
                    }
                    break;
                }
                case search_state::in_correct_enum: {
                    if (word == "{") {
                        ++figure_balance;
                    } else if (word == "}") {
                        --figure_balance;
                        if(figure_balance == 0) {
                            current_state = search_state::finished;
                        }
                    } else if (word != ",") {
                        result.public_members.emplace_back(word);
                    }
                    break;
                }

                case search_state::in_correct_class: {
                    bool balance = (figure_balance <= 1);

                    if (balance && word == "private") {
                        private_flag = true;
                    } else if (balance && word == "fun") {
                        current_state = search_state::in_function;
                    } else if (balance && (word == "val" || word == "var")) {
                        current_state = search_state ::in_member;
                    } else if((figure_balance == 1) && (word == "class" || word == "object")) {
                        current_state = search_state::in_inner;
                    } else if (word == "{") {
                        ++figure_balance;
                    } else if (word == "}") {
                        --figure_balance;
                        if(figure_balance == 0) {
                            current_state = search_state::finished;
                        }
                    } else if (figure_balance == 0 && (word == "class" || word == "object")) {
                        current_state = search_state::finished;
                    }
                    break;
                }
                case search_state::in_function: {
                    if (private_flag) {
                        private_flag = false;
                        result.private_functions.push_back(word);
                    } else {
                        result.public_functions.push_back(word);
                    }
                    current_state = search_state::in_correct_class;
                    break;
                }
                case search_state::in_member: {
                    if (private_flag) {
                        private_flag = false;
                        result.private_members.push_back(word);
                    } else {
                        result.public_members.push_back(word);
                    }
                    current_state = search_state::in_correct_class;
                    break;
                }
                case search_state::in_inner: {
                    if (word == "{") {
                        result.inner_classes.push_back(classname + "_companion");
                    } else {
                        private_flag = false;
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
                        //TODO: get, to what class this is a companion and produce correct name
                    } else if (word.size() == 1 && !isalnum(word[0])){
                        //do nothing
                    } else {
                        result.emplace_back(word);
                    }
                    current_state = search_state::normal;
                    break;
                }
                default: {
                    throw UnreachableCode();
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