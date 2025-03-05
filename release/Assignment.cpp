#include "./Assignment.hpp"

namespace PerformanceEvaluation {
    void Assignment::Question_1_Array() {
        static constexpr int32_t MAX_DISPLAY_COUNT = 5;
                                
        Array<Dataset> array_true;
        Array<Dataset> array_fake;
        
        std::string file_path_true = "./CSV/true.csv"; 
        std::string file_path_fake = "./CSV/fake.csv";

        FileHandling::ReadFile(file_path_true, array_true);
        FileHandling::ReadFile(file_path_fake, array_fake);

        std::cout << "\033[35;1mBefore Sorting...\033[31;1mTRUE.CSV\033[0m\n";
        array_true.DisplayFirst(MAX_DISPLAY_COUNT);

        Algorithm::SortBy(array_true, std::make_unique<SortMergeArray>().get());
        // Algorithm::SortBy(array_true, std::make_unique<SortQuickArray>().get());
        // Algorithm::SortBy(array_true, std::make_unique<SortHeapArray>().get());
        
        std::cout << "\033[35;1mAfter Sorting...\033[31;1mTRUE.CSV\033[0m\n";
        array_true.DisplayFirst(MAX_DISPLAY_COUNT);
        
        std::cout << "\033[35;1mBefore Sorting...\033[31;1mFAKE.CSV\033[0m\n";
        array_fake.DisplayFirst(MAX_DISPLAY_COUNT);
        
        Algorithm::SortBy(array_fake, std::make_unique<SortMergeArray>().get());
        // Algorithm::SortBy(array_fake, std::make_unique<SortQuickArray>().get());
        // Algorithm::SortBy(array_fake, std::make_unique<SortHeapArray>().get());
            
        std::cout << "\033[35;1mAfter Sorting...\033[31;1mFAKE.CSV\033[0m\n";
        array_fake.DisplayFirst(MAX_DISPLAY_COUNT);

        array_true.DisplayLength(file_path_true);
        array_fake.DisplayLength(file_path_fake);
    }

    void Assignment::Question_1_LinkedList() {
        static constexpr int32_t MAX_DISPLAY_COUNT = 5;
        
        LinkedList linked_list_true;
        LinkedList linked_list_fake;

        std::string file_path_true = "./CSV/true.csv"; 
        std::string file_path_fake = "./CSV/fake.csv";
        
        FileHandling::ReadFile(file_path_true, linked_list_true);
        FileHandling::ReadFile(file_path_fake, linked_list_fake);

        std::cout << "\033[35;1mBefore Sorting...\033[31;1mTRUE\033[0m\n";
        linked_list_true.DisplayFirst(MAX_DISPLAY_COUNT);
;
        Algorithm::SortBy(linked_list_true, std::make_unique<SortMergeLinkedList>().get());
        
        std::cout << "\033[35;1mAfter Sorting...\033[31;1mTRUE.CSV\033[0m\n";
        linked_list_true.DisplayFirst(MAX_DISPLAY_COUNT);
        
        std::cout << "\033[35;1mBefore Sorting...\033[31;1mFAKE\033[0m\n";
        linked_list_fake.DisplayFirst(MAX_DISPLAY_COUNT);
        
        Algorithm::SortBy(linked_list_fake, std::make_unique<SortMergeLinkedList>().get());
        
        std::cout << "\033[35;1mAfter Sorting...\033[31;1mFAKE.CSV\033[0m\n";
        linked_list_fake.DisplayFirst(MAX_DISPLAY_COUNT);

        linked_list_true.DisplayLength(file_path_true);
        linked_list_fake.DisplayLength(file_path_fake);
    }

    void Assignment::Question_2_Array() {
        // Percentage of Fake News = (Number of Fake Political News Articles in 2016 / Total Political News Articles in 2016) × 100
            
        DynamicArray<Dataset> array_true;
        DynamicArray<Dataset> array_fake;
        DynamicArray<Dataset> array_combined;
        
        const FilePath& file_path_true = "./CSV/true.csv"; 
        const FilePath& file_path_fake = "./CSV/fake.csv";
        const FilePath& file_path_combined = "./CSV/combined.csv"; 

        FileHandling::AppendFileContent(file_path_true, file_path_combined);
        FileHandling::AppendFileContent(file_path_fake, file_path_combined);
        
        FileHandling::ReadFile(file_path_fake, array_fake);
        FileHandling::ReadFile(file_path_combined, array_combined);

        SearchLinearDynamicArray search_linear;
        
        // Denominator
        DynamicArray<Dataset> array_combined_impartial_search_date_2016 = search_linear.LinearSearchAndCopy("2016", array_combined, Criteria::DATE, SearchType::IMPARTIAL);
        
        DynamicArray<Dataset> array_combined_impartial_search_date_2016_and_impartial_search_subject_politics 
            = search_linear.LinearSearchAndCopy("politics", array_combined_impartial_search_date_2016, Criteria::SUBJECT, SearchType::IMPARTIAL);
        
        // Numerator    
        DynamicArray<Dataset> array_fake_impartial_search_date_2016 = search_linear.LinearSearchAndCopy("2016", array_fake, Criteria::DATE, SearchType::IMPARTIAL);

        DynamicArray<Dataset> array_fake_impartial_search_date_2016_and_impartial_search_subject_politics 
            = search_linear.LinearSearchAndCopy("politics", array_fake_impartial_search_date_2016, Criteria::SUBJECT, SearchType::IMPARTIAL);

        size_t numerator = array_fake_impartial_search_date_2016_and_impartial_search_subject_politics.GetLength();
        size_t denominator = array_combined_impartial_search_date_2016_and_impartial_search_subject_politics.GetLength();
        
        double percent = CalculatePercentage(numerator, denominator);

        std::cout << "Out of " << denominator << " true and fake articles from the year 2016, " 
            << percent << "% of political news articles are fake.\n";
    }

    void Assignment::Question_2_LinkedList() {
        LinkedList linked_list_true;
        LinkedList linked_list_fake;
        LinkedList linked_list_combined;

        const FilePath& file_path_true = "./CSV/true.csv"; 
        const FilePath& file_path_fake = "./CSV/fake.csv";
        const FilePath& file_path_combined = "./CSV/combined.csv"; 
        
        FileHandling::AppendFileContent(file_path_true, file_path_combined);
        FileHandling::AppendFileContent(file_path_fake, file_path_combined);
        
        FileHandling::ReadFile(file_path_fake, linked_list_fake);
        FileHandling::ReadFile(file_path_combined, linked_list_combined);

        // Denominator
        LinkedList linked_list_combined_impartial_search_date_2016 = Algorithm::LinearSearchAndCopy(
            linked_list_combined, std::make_unique<SearchLinearLinkedList>().get(), 
            "2016", Criteria::DATE, SearchType::IMPARTIAL
        );

        LinkedList linked_list_combined_impartial_search_date_2016_and_impartial_search_subject_politics = Algorithm::LinearSearchAndCopy(
            linked_list_combined_impartial_search_date_2016, std::make_unique<SearchLinearLinkedList>().get(), 
            "politics", Criteria::SUBJECT, SearchType::IMPARTIAL
        );

        // Numerator
        LinkedList linked_list_fake_impartial_search_date_2016 =  Algorithm::LinearSearchAndCopy(
            linked_list_fake, std::make_unique<SearchLinearLinkedList>().get(), 
            "2016", Criteria::DATE, SearchType::IMPARTIAL
        );

        LinkedList linked_list_fake_impartial_search_date_2016_and_impartial_search_subject_politics =  Algorithm::LinearSearchAndCopy(
            linked_list_fake_impartial_search_date_2016, std::make_unique<SearchLinearLinkedList>().get(), 
            "politics", Criteria::SUBJECT, SearchType::IMPARTIAL
        );

        size_t numerator = linked_list_fake_impartial_search_date_2016_and_impartial_search_subject_politics.GetLength();
        size_t denominator = linked_list_combined_impartial_search_date_2016_and_impartial_search_subject_politics.GetLength();
        
        double percent = CalculatePercentage(numerator, denominator);

        std::cout << "Out of " << denominator << " true and fake articles from the year 2016, " 
            << percent << "% of political news articles are fake.\n";
    }

    void Assignment::Question_3_Array() {
        const FilePath& file_path_fake = "./CSV/fake.csv";

        DynamicArray<Dataset> array_fake;
        FileHandling::ReadFile(file_path_fake, array_fake);

        SearchLinearDynamicArray search_linear;
        
        DynamicArray<Dataset> array_fake_impartial_searched_subject_government = 
            search_linear.LinearSearchAndCopy("government", array_fake, Criteria::SUBJECT, SearchType::IMPARTIAL);

        HashSet<std::string> stopwords = {
            "a", "an", "and", "are", "as", "at", "be", "but", "by", 
            "for", "if", "in", "into", "is", "it", "no", "not", "of", 
            "on", "or", "such", "that", "the", "their", "then", "there", 
            "these", "they", "this", "to", "was", "will", "with", "the"
        };

        DynamicArray<std::string> word_array_fake = ConvertDynamicArrayToWordArray(array_fake_impartial_searched_subject_government, stopwords);

        HashMap<std::string, int32_t> word_map = GetWordCount(word_array_fake);
        
        DynamicArray<std::string> word_array_sorted = CheckAndSortHashMapArray(word_map);

        DisplayAll(word_array_sorted);
    }

    void Assignment::Question_3_LinkedList() {
        const FilePath& file_path_fake = "./CSV/fake.csv";

        LinkedList linked_list_fake;
        FileHandling::ReadFile(file_path_fake, linked_list_fake);

        auto search_interface = std::make_unique<SearchLinearLinkedList>();

        LinkedList linked_list_fake_impartial_searched_subject_government = 
            Algorithm::LinearSearchAndCopy(linked_list_fake, search_interface.get(), "government", Criteria::SUBJECT, SearchType::IMPARTIAL);

        HashSet<std::string> stopwords = {
            "a", "an", "and", "are", "as", "at", "be", "but", "by", 
            "for", "if", "in", "into", "is", "it", "no", "not", "of", 
            "on", "or", "such", "that", "the", "their", "then", "there", 
            "these", "they", "this", "to", "was", "will", "with", "the"
        };

        WordList word_list_fake = ConvertLinkedListToWordList(linked_list_fake_impartial_searched_subject_government, stopwords);

        HashMap<std::string, int32_t> word_map = GetWordCount(word_list_fake);
        
        WordListSorted word_list_sorted = CheckAndSortHashMapLinkedList(word_map);

        word_list_sorted.DisplayAll();
    }
} // namespace PerformanceEvaluation