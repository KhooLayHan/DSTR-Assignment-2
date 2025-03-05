#include "./ConversionUtility.hpp"

#include "./FileHandling.hpp"
#include "./SearchLinearLinkedList.hpp"
#include "./SearchLinearDynamicArray.hpp"
#include "./Algorithm.hpp"
#include <iomanip>

namespace PerformanceEvaluation
{
    HashMap<std::string, int32_t> GetWordCount(const WordList& word_linked_list) {
        HashMap<std::string, int> word_count;

        WordListNode* temp = word_linked_list.GetHead();

        int i = 0;

        while (temp) {
            std::string word = temp->m_Data;
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            
            if (word_count.Contains(word))
                word_count[word]++;
            else    
                word_count.Insert(word, 1);

            i++;

            std::string str = word + ": " + std::to_string(word_count[word]) + "\n";
           
            FileHandling::AppendFileNewline("./Solutions/question_3_linked_list.txt", str);

            temp = temp->m_Next;
        }

        return word_count;
    };

    HashMap<std::string, int32_t> GetWordCount(const DynamicArray<std::string>& word_array) {
        HashMap<std::string, int> word_count;

        for (size_t i = 0; i != word_array.GetLength(); i++) {
            std::string word = word_array[i];
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            
            if (word_count.Contains(word))
                word_count[word]++;
            else    
                word_count.Insert(word, 1);

            std::string str = word + ": " + std::to_string(word_count[word]) + "\n";
           
            FileHandling::AppendFileNewline("./Solutions/question_3_array.txt", str);
        }

        return word_count;
    };

    WordList ConvertLinkedListToWordList(const LinkedList& linked_list, HashSet<std::string>& stopwords) {
        LinkedListNode* temp = linked_list.GetHead();
        WordList word_list;

        int line = 0;

        // Hard-coded that ends ups only reading the first line in fake.csv
        while (temp && line != 1) {
            if (line == 1) 
                break;
            
            const Dataset& dataset = temp->m_Data;
            
            auto text_parser = [](const std::string& text) {
                Vector<std::string> words;
                std::regex word_pattern(R"(\b([A-Za-z0-9]+(?:-[A-Za-z0-9]+)*|(?:[A-Za-z]\.){2,})\b)");
                
                std::sregex_iterator it(text.begin(), text.end(), word_pattern);
                std::sregex_iterator end;

                while (it != end) {
                    words.EmplaceBack(it->str());
                    ++it;
                }

                return words;
            };

            Vector<std::string> words = text_parser(dataset.m_Title + " " + dataset.m_Text);

            for (size_t i = 0; i != words.GetLength(); i++) {
                if (!stopwords.Contains(words[i])) {
                    word_list.InsertEnd(words[i]);
                }
            }
        
            temp = temp->m_Next;
            line++;
        }

        return word_list;
    };

    DynamicArray<std::string> ConvertDynamicArrayToWordArray(const DynamicArray<Dataset>& array, HashSet<std::string>& stopwords) {
        DynamicArray<std::string> word_array;
    
        int line = 0;
    
        // Hard-coded that ends ups only reading the first line in fake.csv
        // while (temp && line != 1) {
        for (size_t i = 0; i != array.GetLength(); i++) {
            if (line == 1)
                break;
    
            const Dataset& dataset = array[0];
    
            auto text_parser = [](const std::string& text) {
                DynamicArray<std::string> words;
                std::regex word_pattern(R"(\b([A-Za-z0-9]+(?:-[A-Za-z0-9]+)*|(?:[A-Za-z]\.){2,})\b)");
    
                std::sregex_iterator it(text.begin(), text.end(), word_pattern);
                std::sregex_iterator end;
    
                while (it != end) {
                    words.Insert(words.GetLength(), it->str());
                    ++it;
                }
    
                return words;
            };
    
            DynamicArray<std::string> words = text_parser(dataset.m_Title + " " + dataset.m_Text);
    
            for (size_t i = 0; i != words.GetLength(); i++) {
                if (!stopwords.Contains(words[i])) {
                    word_array.Insert(word_array.GetLength(), words[i]);
                }
            }

            line++;
        }
    
        return word_array;
    }

    // Extract word-count pairs and sort them to sorted word list
    WordListSorted CheckAndSortHashMapLinkedList(HashMap<std::string, int32_t>& word_count) {
        WordListSorted sorted_list;

        for (const auto& [key, value] : word_count) {
            sorted_list.InsertSorted(key, value);
        }

        return sorted_list;
    }
    
    // Extract word-count pairs and sort them to dynamic array
    DynamicArray<std::string> CheckAndSortHashMapArray(HashMap<std::string, int32_t>& word_count) {
        DynamicArray<std::string> sorted_array;

        // Function to check if a string contains only digits
        auto IsNumber = [](const std::string& str) {
            for (char c : str)
                if (!std::isdigit(c))
                    return false;
            return true;
        };

        for (auto it = word_count.begin(); it != word_count.end(); ++it) {
            if (!IsNumber((*it).first))
               sorted_array.Insert(sorted_array.GetLength(), (*it).first);
        }

        MergeSort(sorted_array);

        return sorted_array;
    }

    void Question_2_LinkedList_ExtraExclusive(const FilePath& true_file_path, const FilePath& fake_file_path) {  
        // Percentage of Fake News for Month = ( Number of Fake Political News Articles in Month / Total Political News Articles in Month ) × 100

        LinkedList linked_list_true;
        LinkedList linked_list_fake;

        FileHandling::ReadFile(true_file_path, linked_list_true);
        FileHandling::ReadFile(fake_file_path, linked_list_fake);

        auto search_interface = std::make_unique<SearchLinearLinkedList>();
        auto search_interface_2 = std::make_unique<SearchLinearLinkedList>();

        LinkedList linked_true_impartial_searched_2016 = Algorithm::LinearSearchAndCopy(linked_list_true, search_interface.get(), "2016", Criteria::DATE, SearchType::IMPARTIAL);
        LinkedList linked_fake_impartial_searched_2016 = Algorithm::LinearSearchAndCopy(linked_list_fake, search_interface.get(), "2016", Criteria::DATE, SearchType::IMPARTIAL);

        LinkedList linked_true_impartial_searched_2016_and_partial_search_subject_politics
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016, search_interface.get(), "politics", Criteria::SUBJECT, SearchType::IMPARTIAL);
        
        LinkedList linked_fake_impartial_searched_2016_and_partial_search_subject_politics
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016, search_interface.get(), "politics", Criteria::SUBJECT, SearchType::IMPARTIAL);
        
        LinkedList linked_true_impartial_searched_2016_january 
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "jan", Criteria::DATE, SearchType::IMPARTIAL);

        LinkedList linked_true_impartial_searched_2016_february 
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "feb", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_true_impartial_searched_2016_march 
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "mar", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_true_impartial_searched_2016_april 
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "apr", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_true_impartial_searched_2016_may 
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "may", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_true_impartial_searched_2016_june 
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "jun", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_true_impartial_searched_2016_july 
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "jul", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_true_impartial_searched_2016_august 
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "aug", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_true_impartial_searched_2016_september 
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "sep", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_true_impartial_searched_2016_october 
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "oct", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_true_impartial_searched_2016_november 
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "nov", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_true_impartial_searched_2016_december 
            = Algorithm::LinearSearchAndCopy(linked_true_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "dec", Criteria::DATE, SearchType::IMPARTIAL);


        // Fake
        
        LinkedList linked_fake_impartial_searched_2016_january 
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "jan", Criteria::DATE, SearchType::IMPARTIAL);

        LinkedList linked_fake_impartial_searched_2016_february 
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "feb", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_fake_impartial_searched_2016_march 
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "mar", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_fake_impartial_searched_2016_april 
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "apr", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_fake_impartial_searched_2016_may 
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "may", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_fake_impartial_searched_2016_june 
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "jun", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_fake_impartial_searched_2016_july 
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "jul", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_fake_impartial_searched_2016_august 
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "aug", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_fake_impartial_searched_2016_september 
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "sep", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_fake_impartial_searched_2016_october 
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "oct", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_fake_impartial_searched_2016_november 
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "nov", Criteria::DATE, SearchType::IMPARTIAL);
        
        LinkedList linked_fake_impartial_searched_2016_december 
            = Algorithm::LinearSearchAndCopy(linked_fake_impartial_searched_2016_and_partial_search_subject_politics, search_interface.get(), "dec", Criteria::DATE, SearchType::IMPARTIAL);

        size_t true_january      = linked_true_impartial_searched_2016_january.GetLength(); 
        size_t true_february     = linked_true_impartial_searched_2016_february.GetLength();
        size_t true_march        = linked_true_impartial_searched_2016_march.GetLength();
        size_t true_april        = linked_true_impartial_searched_2016_april.GetLength();
        size_t true_may          = linked_true_impartial_searched_2016_may.GetLength();
        size_t true_june         = linked_true_impartial_searched_2016_june.GetLength();
        size_t true_july         = linked_true_impartial_searched_2016_july.GetLength();
        size_t true_august       = linked_true_impartial_searched_2016_august.GetLength();
        size_t true_september    = linked_true_impartial_searched_2016_september.GetLength();
        size_t true_october      = linked_true_impartial_searched_2016_october.GetLength();
        size_t true_november     = linked_true_impartial_searched_2016_november.GetLength();
        size_t true_december     = linked_true_impartial_searched_2016_december.GetLength();

        size_t fake_january      = linked_fake_impartial_searched_2016_january.GetLength(); 
        size_t fake_february     = linked_fake_impartial_searched_2016_february.GetLength();
        size_t fake_march        = linked_fake_impartial_searched_2016_march.GetLength();
        size_t fake_april        = linked_fake_impartial_searched_2016_april.GetLength();
        size_t fake_may          = linked_fake_impartial_searched_2016_may.GetLength();
        size_t fake_june         = linked_fake_impartial_searched_2016_june.GetLength();
        size_t fake_july         = linked_fake_impartial_searched_2016_july.GetLength();
        size_t fake_august       = linked_fake_impartial_searched_2016_august.GetLength();
        size_t fake_september    = linked_fake_impartial_searched_2016_september.GetLength();
        size_t fake_october      = linked_fake_impartial_searched_2016_october.GetLength();
        size_t fake_november     = linked_fake_impartial_searched_2016_november.GetLength();
        size_t fake_december     = linked_fake_impartial_searched_2016_december.GetLength();

        double total_january     = true_january + fake_january;
        double total_february    = true_february + fake_february;
        double total_march       = true_march + fake_march;
        double total_april       = true_april + fake_april;
        double total_may         = true_may + fake_may;
        double total_june        = true_june + fake_june;
        double total_july        = true_july + fake_july;
        double total_august      = true_august + fake_august;
        double total_september   = true_september + fake_september;
        double total_october     = true_october + fake_october;
        double total_november    = true_november + fake_november;
        double total_december    = true_december + fake_december;

        // std::cout << "January - True: " << true_january << ", Fake: " << fake_january << ", Total: " << total_january << std::endl;
        // std::cout << "February - True: " << true_february << ", Fake: " << fake_february << ", Total: " << total_february << std::endl;
        // std::cout << "March - True: " << true_march << ", Fake: " << fake_march << ", Total: " << total_march << std::endl;
        // std::cout << "April - True: " << true_april << ", Fake: " << fake_april << ", Total: " << total_april << std::endl;
        // std::cout << "May - True: " << true_may << ", Fake: " << fake_may << ", Total: " << total_may << std::endl;
        // std::cout << "June - True: " << true_june << ", Fake: " << fake_june << ", Total: " << total_june << std::endl;
        // std::cout << "July - True: " << true_july << ", Fake: " << fake_july << ", Total: " << total_july << std::endl;
        // std::cout << "August - True: " << true_august << ", Fake: " << fake_august << ", Total: " << total_august << std::endl;
        // std::cout << "September - True: " << true_september << ", Fake: " << fake_september << ", Total: " << total_september << std::endl;
        // std::cout << "October - True: " << true_october << ", Fake: " << fake_october << ", Total: " << total_october << std::endl;
        // std::cout << "November - True: " << true_november << ", Fake: " << fake_november << ", Total: " << total_november << std::endl;
        // std::cout << "December - True: " << true_december << ", Fake: " << fake_december << ", Total: " << total_december << std::endl;

        double jan_fake_2016_percent = CalculatePercentage(fake_january, total_january); 
        double feb_fake_2016_percent = CalculatePercentage(fake_february, total_february);
        double mar_fake_2016_percent = CalculatePercentage(fake_march, total_march);
        double apr_fake_2016_percent = CalculatePercentage(fake_april, total_april);
        double may_fake_2016_percent = CalculatePercentage(fake_may, total_may);
        double jun_fake_2016_percent = CalculatePercentage(fake_june, total_june);
        double jul_fake_2016_percent = CalculatePercentage(fake_july, total_july);
        double aug_fake_2016_percent = CalculatePercentage(fake_august, total_august);
        double sep_fake_2016_percent = CalculatePercentage(fake_september, total_september);
        double oct_fake_2016_percent = CalculatePercentage(fake_october, total_october);
        double nov_fake_2016_percent = CalculatePercentage(fake_november, total_november);
        double dec_fake_2016_percent = CalculatePercentage(fake_december, total_december);

        std::cout << "\nPercentage of Fake Political News Articles in 2016 (LinkedList)\n"; 

        double percentages[] = {jan_fake_2016_percent, feb_fake_2016_percent, mar_fake_2016_percent, apr_fake_2016_percent, may_fake_2016_percent, jun_fake_2016_percent, jul_fake_2016_percent, aug_fake_2016_percent, sep_fake_2016_percent, oct_fake_2016_percent, nov_fake_2016_percent, dec_fake_2016_percent};
        std::string months[] = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };

        // Print table header
        std::cout << "----------------------------------------------------------\n";
        std::cout << std::left << std::setw(12) << "Month"
              << "| " << std::setw(30) << "Graph"
              << "| Percentage\n";
        std::cout << "----------------------------------------------------------\n"; // Divider line

        for (int i = 0; i < 12; i++) {
            int numStars = static_cast<int>(percentages[i] / 2); // Each '*' represents 2%
            
            std::cout << std::left << std::setw(12) << months[i] << "| ";
    
            for (int j = 0; j < numStars; j++) {
                std::cout << "*";
            }
    
            std::cout << std::setw(30 - numStars) << "" << "| " 
                      << std::fixed << std::setprecision(2) << percentages[i] << "%" << std::endl;
        }
        std::cout << "----------------------------------------------------------\n"; // Divider line
        std::cout << "\n\033[31mNote: Each '*' represents approximately 2% of fake political news articles.\033[0m\n"; 
    }

    void DisplayFirst(size_t count, const DynamicArray<Dataset>& array) {
        if (array.GetLength() == 0) {
            std::cout << "The array is empty." << std::endl;
            return;
        }
    
        count = (count > array.GetLength()) ? array.GetLength() : count; // Ensure we don't exceed array size
    
        for (size_t i = 0; i < count; i++) {
            const Dataset& data = array[i];
            std::cout << "ID: " << data.m_Id << "\n"
                      << "Title: " << data.m_Title << "\n"
                      << "Text: " << data.m_Text << "\n"
                      << "Subject: " << data.m_Subject << "\n"
                      << "Date: " << data.m_Date << "\n"
                      << "-----------------------\n";
        }
    }

    void Question_2_Array_ExtraExclusive(const FilePath& true_file_path, const FilePath& fake_file_path) {    
        DynamicArray<Dataset> array_true;
        DynamicArray<Dataset> array_fake;

        FileHandling::ReadFile(true_file_path, array_true);
        FileHandling::ReadFile(fake_file_path, array_fake);

        SearchLinearDynamicArray search_linear;

        DynamicArray<Dataset> array_true_impartial_searched_2016 = search_linear.LinearSearchAndCopy("2016", array_true, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_fake_impartial_searched_2016 = search_linear.LinearSearchAndCopy("2016", array_fake, Criteria::DATE, SearchType::IMPARTIAL);

        DynamicArray<Dataset> array_true_impartial_searched_2016_and_partial_search_subject_politics
            = search_linear.LinearSearchAndCopy("politics", array_true_impartial_searched_2016, Criteria::SUBJECT, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_fake_impartial_searched_2016_and_partial_search_subject_politics = search_linear.LinearSearchAndCopy("politics", array_fake_impartial_searched_2016, Criteria::SUBJECT, SearchType::PARTIAL);
        
        DynamicArray<Dataset> array_true_impartial_searched_2016_january    = search_linear.LinearSearchAndCopy("jan", array_true_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_true_impartial_searched_2016_february   = search_linear.LinearSearchAndCopy("feb", array_true_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_true_impartial_searched_2016_march      = search_linear.LinearSearchAndCopy("mar", array_true_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_true_impartial_searched_2016_april      = search_linear.LinearSearchAndCopy("apr", array_true_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_true_impartial_searched_2016_may        = search_linear.LinearSearchAndCopy("may", array_true_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_true_impartial_searched_2016_june       = search_linear.LinearSearchAndCopy("jun", array_true_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_true_impartial_searched_2016_july       = search_linear.LinearSearchAndCopy("jul", array_true_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_true_impartial_searched_2016_august     = search_linear.LinearSearchAndCopy("aug", array_true_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_true_impartial_searched_2016_september  = search_linear.LinearSearchAndCopy("sep", array_true_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_true_impartial_searched_2016_october    = search_linear.LinearSearchAndCopy("oct", array_true_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_true_impartial_searched_2016_november   = search_linear.LinearSearchAndCopy("nov", array_true_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_true_impartial_searched_2016_december   = search_linear.LinearSearchAndCopy("dec", array_true_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);

        DynamicArray<Dataset> array_fake_impartial_searched_2016_january    = search_linear.LinearSearchAndCopy("jan", array_fake_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_fake_impartial_searched_2016_february   = search_linear.LinearSearchAndCopy("feb", array_fake_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_fake_impartial_searched_2016_march      = search_linear.LinearSearchAndCopy("mar", array_fake_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_fake_impartial_searched_2016_april      = search_linear.LinearSearchAndCopy("apr", array_fake_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);       
        DynamicArray<Dataset> array_fake_impartial_searched_2016_may        = search_linear.LinearSearchAndCopy("may", array_fake_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_fake_impartial_searched_2016_june       = search_linear.LinearSearchAndCopy("jun", array_fake_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_fake_impartial_searched_2016_july       = search_linear.LinearSearchAndCopy("jul", array_fake_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_fake_impartial_searched_2016_august     = search_linear.LinearSearchAndCopy("aug", array_fake_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_fake_impartial_searched_2016_september  = search_linear.LinearSearchAndCopy("sep", array_fake_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_fake_impartial_searched_2016_october    = search_linear.LinearSearchAndCopy("oct", array_fake_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_fake_impartial_searched_2016_november   = search_linear.LinearSearchAndCopy("nov", array_fake_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);
        DynamicArray<Dataset> array_fake_impartial_searched_2016_december   = search_linear.LinearSearchAndCopy("dec", array_fake_impartial_searched_2016_and_partial_search_subject_politics, Criteria::DATE, SearchType::IMPARTIAL);

        size_t true_january      = array_true_impartial_searched_2016_january.GetLength(); 
        size_t true_february     = array_true_impartial_searched_2016_february.GetLength();
        size_t true_march        = array_true_impartial_searched_2016_march.GetLength();
        size_t true_april        = array_true_impartial_searched_2016_april.GetLength();
        size_t true_may          = array_true_impartial_searched_2016_may.GetLength();
        size_t true_june         = array_true_impartial_searched_2016_june.GetLength();
        size_t true_july         = array_true_impartial_searched_2016_july.GetLength();
        size_t true_august       = array_true_impartial_searched_2016_august.GetLength();
        size_t true_september    = array_true_impartial_searched_2016_september.GetLength();
        size_t true_october      = array_true_impartial_searched_2016_october.GetLength();
        size_t true_november     = array_true_impartial_searched_2016_november.GetLength();
        size_t true_december     = array_true_impartial_searched_2016_december.GetLength();

        size_t fake_january      = array_fake_impartial_searched_2016_january.GetLength();
        size_t fake_february     = array_fake_impartial_searched_2016_february.GetLength();
        size_t fake_march        = array_fake_impartial_searched_2016_march.GetLength();
        size_t fake_april        = array_fake_impartial_searched_2016_april.GetLength();
        size_t fake_may          = array_fake_impartial_searched_2016_may.GetLength();
        size_t fake_june         = array_fake_impartial_searched_2016_june.GetLength();
        size_t fake_july         = array_fake_impartial_searched_2016_july.GetLength();
        size_t fake_august       = array_fake_impartial_searched_2016_august.GetLength();
        size_t fake_september    = array_fake_impartial_searched_2016_september.GetLength();
        size_t fake_october      = array_fake_impartial_searched_2016_october.GetLength();
        size_t fake_november     = array_fake_impartial_searched_2016_november.GetLength();
        size_t fake_december     = array_fake_impartial_searched_2016_december.GetLength();

        double total_january     = true_january + fake_january;
        double total_february    = true_february + fake_february;
        double total_march       = true_march + fake_march;
        double total_april       = true_april + fake_april;
        double total_may         = true_may + fake_may;
        double total_june        = true_june + fake_june;
        double total_july        = true_july + fake_july;
        double total_august      = true_august + fake_august;
        double total_september   = true_september + fake_september;
        double total_october     = true_october + fake_october;
        double total_november    = true_november + fake_november;
        double total_december    = true_december + fake_december;

        // std::cout << "January - True: " << true_january << ", Fake: " << fake_january << ", Total: " << total_january << std::endl;
        // std::cout << "February - True: " << true_february << ", Fake: " << fake_february << ", Total: " << total_february << std::endl;
        // std::cout << "March - True: " << true_march << ", Fake: " << fake_march << ", Total: " << total_march << std::endl;
        // std::cout << "April - True: " << true_april << ", Fake: " << fake_april << ", Total: " << total_april << std::endl;
        // std::cout << "May - True: " << true_may << ", Fake: " << fake_may << ", Total: " << total_may << std::endl;
        // std::cout << "June - True: " << true_june << ", Fake: " << fake_june << ", Total: " << total_june << std::endl;
        // std::cout << "July - True: " << true_july << ", Fake: " << fake_july << ", Total: " << total_july << std::endl;
        // std::cout << "August - True: " << true_august << ", Fake: " << fake_august << ", Total: " << total_august << std::endl;
        // std::cout << "September - True: " << true_september << ", Fake: " << fake_september << ", Total: " << total_september << std::endl;
        // std::cout << "October - True: " << true_october << ", Fake: " << fake_october << ", Total: " << total_october << std::endl;
        // std::cout << "November - True: " << true_november << ", Fake: " << fake_november << ", Total: " << total_november << std::endl;
        // std::cout << "December - True: " << true_december << ", Fake: " << fake_december << ", Total: " << total_december << std::endl;

        double jan_fake_2016_percent = CalculatePercentage(fake_january, total_january); 
        double feb_fake_2016_percent = CalculatePercentage(fake_february, total_february);
        double mar_fake_2016_percent = CalculatePercentage(fake_march, total_march);
        double apr_fake_2016_percent = CalculatePercentage(fake_april, total_april);
        double may_fake_2016_percent = CalculatePercentage(fake_may, total_may);
        double jun_fake_2016_percent = CalculatePercentage(fake_june, total_june);
        double jul_fake_2016_percent = CalculatePercentage(fake_july, total_july);
        double aug_fake_2016_percent = CalculatePercentage(fake_august, total_august);
        double sep_fake_2016_percent = CalculatePercentage(fake_september, total_september);
        double oct_fake_2016_percent = CalculatePercentage(fake_october, total_october);
        double nov_fake_2016_percent = CalculatePercentage(fake_november, total_november);
        double dec_fake_2016_percent = CalculatePercentage(fake_december, total_december);

        std::cout << "\nPercentage of Fake Political News Articles in 2016 (Array)\n"; 

        double percentages[] = {jan_fake_2016_percent, feb_fake_2016_percent, mar_fake_2016_percent, apr_fake_2016_percent, may_fake_2016_percent, jun_fake_2016_percent, jul_fake_2016_percent, aug_fake_2016_percent, sep_fake_2016_percent, oct_fake_2016_percent, nov_fake_2016_percent, dec_fake_2016_percent};
        std::string months[] = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };

        // Print table header
        std::cout << "----------------------------------------------------------\n";
        std::cout << std::left << std::setw(12) << "Month"
              << "| " << std::setw(30) << "Graph"
              << "| Percentage\n";
        std::cout << "----------------------------------------------------------\n"; // Divider line

        for (int i = 0; i < 12; i++) {
            int numStars = static_cast<int>(percentages[i] / 2); // Each '*' represents 2%
            
            std::cout << std::left << std::setw(12) << months[i] << "| ";
    
            for (int j = 0; j < numStars; j++) {
                std::cout << "*";
            }
    
            std::cout << std::setw(30 - numStars) << "" << "| " 
                      << std::fixed << std::setprecision(2) << percentages[i] << "%" << std::endl;
        }
        std::cout << "----------------------------------------------------------\n"; // Divider line
        std::cout << "\n\033[31mNote: Each '*' represents approximately 2% of fake political news articles.\033[0m\n";
       
    }

    void DisplayAll(const DynamicArray<std::string>& array) {
        if (array.GetLength() == 0) {
            std::cout << "The array is empty." << std::endl;
            return;
        }
    
        for (size_t i = 0; i < array.GetLength(); i++) {
            std::cout << "\n\033[34;1m" << i + 1 << "\033[0m " << array[i] << "\n";
        }
    }
} // namespace PerformanceEvaluation