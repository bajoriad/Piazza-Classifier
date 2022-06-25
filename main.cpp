// Project UID db1f506d06d84ab787baf250c265e24e

#include <cassert>
#include <iostream>
#include <string>
#include <array>
#include "csvstream.h"
#include <map>
#include <set>
#include <cmath>
#include <math.h>
using namespace std;

class Classifier
{
   private:

    string training_filename; // filename to train classifier
    string testing_filename; // filename to test the classifier
    std::map<string, string> row_train; //reading in column and row
    std::map<string, string> row_test; // reading testing data
    int num_posts = 0; // store number of posts in the
    std::set<string> unique_word; // storing the unique words of the entire string
    std::set<string> diff_labels; // different types of labels
    int vocab_size = 0; // size of the unique_words set
    std::map<string, int> word_count; // how many times a word appears in a post
    std::map<string, int> label_count; // how many posts associated with each label
    std::map<string,map<string,int>> my_map;
    //bool debug; // true if debug, otherwise false
    int test_num_posts = 0;
    int correct_num_posts = 0;
    
    
   public:
    
    Classifier(string train_file, string test_file) : training_filename
    (train_file), testing_filename(test_file) {}
    
    set<string> unique_words(const string &str)
    {
        istringstream source(str);
        set<string> words;
        string word;
        while (source >> word)
        {
          words.insert(word);
        }
        return words;
    }
    
    void training_the_classifier(bool debug)
    {
        csvstream read(training_filename);
        if (debug ==  true)
        {
            cout << "training data:" << endl;
        }
        
        while (read >> row_train)
        {
            ++num_posts;
            std::set<string> unique_word_copy;
            unique_word_copy = unique_words(row_train["content"]);
            for (auto &word: unique_word_copy)
            {
                unique_word.insert(word);
            }
            diff_labels.insert(row_train["tag"]);
            numposts_eachword_eachlabel(row_train);
            label_number_of_posts(row_train);
            if (debug == true)
            {
                cout << "  label = " << row_train["tag"] << ", content = " <<
                row_train["content"] << endl;
            }
            
        }
        cout << "trained on " << num_posts << " examples" << endl;
        vocab_size = int(unique_word.size());
        if(debug == true)
        {
            cout << "vocabulary size = " << vocab_size << endl;
        }
        cout << endl;
        if  (debug == true)
        {
            cout << "classes:" << endl;
            print_training_data_classes();
            cout << "classifier parameters:" << endl;
            print_label_each_word();
            cout << endl;
        }
    }
    
    void print_training_data_classes()
    {
        for (auto iterator = label_count.begin(); iterator != label_count.end();
             ++iterator )
        {
            double logarithm = logarithm_calculation(iterator->first);
            cout << "  " << iterator->first << ", " << iterator->second
            << " examples, log-prior = " << logarithm << endl;
        }
    }
    
    void print_label_each_word()
    {
        for (auto iterator = my_map.begin(); iterator != my_map.end(); ++iterator)
        {
            for (auto &word_num_count : my_map[iterator->first])
            {
                double logarithm = logarithm_label_word_cal(iterator->first,
                                                            word_num_count.first);
     cout << "  " << iterator->first << ":" << word_num_count.first << ", count = " <<
                word_num_count.second << ", log-likelihood = " << logarithm << endl;
            }
        }
    }
    
    void numposts_eachword_eachlabel(std::map<string,string> row_read_copy)
    {
        std::set<string> unique_words_copy;
        unique_words_copy = unique_words(row_read_copy["content"]);
        std::set<string> unique_words_copy_in;
        for (auto &word_copy : unique_words_copy)
        {
            unique_words_copy_in.insert(word_copy);
        }
        string label = row_read_copy["tag"];
        for (const auto &word : unique_words_copy_in)
        {
            word_count[word] += 1;
            my_map[label][word] += 1;
        }
    }
    
    void label_number_of_posts(std::map<string,string> row_read_copy1)
    {
        string label = row_read_copy1["tag"];
        label_count[label] += 1;
    }
    
    double logarithm_calculation(string label)
    {
        double probability_label_c = 0.0;
        probability_label_c = log (double(label_count[label]) / num_posts);
        return probability_label_c;
    }
    
    double logarithm_label_word_cal(string label, string word)
    {
        double word_probability = 0.0;
        if ((unique_word.find(word) != unique_word.end()) && (my_map[label].find(word) ==
                                                              my_map[label].end()))
        {
            word_probability = log ((double(word_count[word])) / num_posts);
        }
        else if (unique_word.find(word) == unique_word.end())
        {
            word_probability = log(1.00 / num_posts);
        }
        else
        {
            word_probability = log (double((my_map[label][word]))/ (label_count[label]));
        }
        return word_probability;
    }
    
    std::pair<string,double> prediction_highest_probability(std::map<string,string>
                                                            row_read_copy2)
    {
        std::pair<string, double> label_and_prob;
        std::map<string, double> label_probability;
        double log_c = 0.0;
        std::set<string> test_word = unique_words(row_read_copy2["content"]);
        for (auto &label_copy : diff_labels)
        {
            log_c = logarithm_calculation(label_copy);
            double sum = log_c;
            for (auto &words : test_word)
            {
                sum = sum + logarithm_label_word_cal(label_copy, words);
            }
            label_probability.insert(std::pair<string,double>(label_copy,sum));
        }
        string max_label = label_probability.begin()->first;
        double max_log = label_probability.begin()->second;
        for (auto iterator = label_probability.begin();
             iterator != label_probability.end();++iterator)
        {
            if (max_log < iterator->second)
            {
                max_log = iterator->second;
                max_label = iterator->first;
            }
        }
        label_and_prob.first = max_label;
        label_and_prob.second = max_log;
        return label_and_prob;
    }
    
    void testing_the_classifier()
    {
        csvstream test(testing_filename);
        std::pair<string, double> test_result;
        cout << "test data:" << endl;
        while (test >> row_test)
        {
            ++test_num_posts;
            test_result = prediction_highest_probability(row_test);
            string correct_label = row_test["tag"];
            string predicated_label = test_result.first;
            double log_score = test_result.second;
            if (correct_label == predicated_label)
            {
                ++correct_num_posts;
            }
         cout << "  correct = " << correct_label << ", predicted = " << predicated_label
            << ", log-probability score = " << log_score << endl;
            cout << "  content = " << row_test["content"] << endl;
            cout << endl << endl;
        }
    }
    
    void print_final_result()
    {
        cout << "performance: " << correct_num_posts << " / " << test_num_posts <<
        " posts predicted correctly" << endl;
    }
    
    void training_and_testing_data(bool debug_copy)
    {
        training_the_classifier(debug_copy);
        testing_the_classifier();
        print_final_result();
        cout << endl;
    }
    
};

void print_error_message()
{
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
}

void file_open_error_message(string filename)
{
    cout << "Error opening file: " << filename << endl;
}


int main(int argc, char *argv[])
{
    cout.precision(3);
    if (argc != 3 && argc != 4)
    {
        print_error_message();
        return 1;
    }
    
    string train_file = argv[1];
    string test_file = argv[2];
    
    ifstream fin(train_file);
    ifstream fin_copy(test_file);
    
    if (!fin.is_open())
    {
        file_open_error_message(train_file);
        return 2;
    }
    
    if (!fin_copy.is_open())
    {
        file_open_error_message(test_file);
        return 3;
    }
    
    if (argc == 3)
    {
        Classifier train_test_data(train_file,test_file);
        train_test_data.training_and_testing_data(false);
    }
    
    if (argc == 4)
    {
        string debug_name = argv[3];
        if (debug_name != "--debug")
        {
            print_error_message();
            return 5;
        }
    }
    
    if (argc == 4)
    {
        Classifier train_test_data_debug(train_file,test_file);
        train_test_data_debug.training_and_testing_data(true);
    }
    return 0;
}
