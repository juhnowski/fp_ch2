#include <vector>
#include <execution>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

vector<int> v = {7, 5, 16, 8};

double average_score(const std::vector<int>& scores)
{
    return std::reduce(
        std::execution::par,
        scores.cbegin(), scores.cend(),
        0
        ) / (double) scores.size();
}

double scores_product(const std::vector<int>& scores)
{
    return std::reduce(
        std::execution::par,
        scores.cbegin(), scores.cend(),
        1,
        std::multiplies<int>()
        ) / (double) scores.size();
}

int f(int previous_count, char c)
{
    return (c != '\n') ? previous_count
                       : previous_count + 1;
}

int count_lines(const std::string& s)
{
    return std::accumulate(
                s.cbegin(), s.cend(),
                0,
                f
            );
}

bool is_not_space (char s) {
  return isspace(s)==0;
}

string trim_left(string s)
{
    s.erase(s.begin(),
        find_if(s.begin(), s.end(), is_not_space)
    );
    return s;
}

string trim_right(string s) {
    s.erase(
        find_if(s.rbegin(), s.rend(), is_not_space).base(),
        s.end()
    );
    return s;
}

string trim(std::string s)
{
    return trim_left(trim_right(std::move(s)));
}

struct person_t
{
    string name;
    bool is_female;
    bool selected;
};

bool is_female(const person_t& person){
    return person.is_female;
}

bool is_not_female(const person_t& person){
    return !person.is_female;
}

std::string name(const person_t& person) {
    return person.name;
}

vector<person_t> persons = {
        {"Ann", true,false}, 
        {"Peter", false, false},
        {"Jane", true, false},
        {"Tom", false, false},
        {"Martha", true, false},
        {"David", false, false},
        {"Rose", true, false},
    };

vector<person_t> people = {
        {"Ann", true,false}, 
        {"Peter", false, false},
        {"Jane", true, false},
        {"Tom", false, false},
        {"Martha", true, false},
        {"David", false, false},
        {"Rose", true, false},
    };

void print(const vector<person_t>& persons){
    for (person_t p:persons){
        cout << p.name << endl;
    }
    cout << "------------------------------" << endl;
}

void sprint(const vector<string>& strings){
    for (string s:strings){
        cout << s << endl;
    }
    cout << "------------------------------" << endl;
}

template <typename FilterFunction>
std::vector<std::string> names_for(const std::vector<person_t>& people, FilterFunction filter) {
    
    std::vector<std::string> result;

    for (const person_t& person : people) {
        if (filter(person)) {
            result.push_back(name(person));
        }
    }
    return result;
}


template <typename FilterFunction, typename Iterator>
std::vector<std::string> names_for_helper(
    Iterator people_begin,
    Iterator people_end,
    FilterFunction filter,
    std::vector<std::string> previously_collected)
    {
        if (people_begin == people_end) {
        return previously_collected;
    } else {
        const auto head = *people_begin;
        if (filter(head)) {
            previously_collected.push_back(name(head));
        }
        return names_for_helper(
            people_begin + 1,
            people_end,
            filter,
            std::move(previously_collected)
            );
    }
}

template <typename FilterFunction, typename Iterator>
std::vector<std::string> names_for_1(
    Iterator people_begin, 
    Iterator people_end, 
    FilterFunction filter) {
    return names_for_helper(people_begin, people_end, filter, {});
}

/*
    std::vector<std::string> append_name_if(
        std::vector<std::string> previously_collected,
        const person_t& person) {
        if (filter(person)) {
            previously_collected.push_back(name(person));
        }
        return previously_collected;
    }

template <typename FilterFunction, typename Iterator>
std::vector<std::string> names_for_2(
    Iterator people_begin, 
    Iterator people_end, 
    FilterFunction filter) {



    return std::accumulate(
        people.cbegin(),
        people.cend(),
        std::vector<std::string>{},
        append_name_if);
}
*/

int main(int argc, char *argv[])
{
    using std::execution::par;
    std::string multiline = R"( Earth is a planet.




So is the Jupiter)";

    std::vector<int> xs(100000000);

    std::fill(par, std::begin(xs), std::end(xs), 42);
    std::cout
        << std::reduce(par, std::begin(xs), std::end(xs), 0)
        << std::endl;

    cout << "average_score: " << average_score(v) << endl;
    cout << "scores_product: " << scores_product(v) << endl;
    cout << "lines: " << count_lines(multiline) << endl; 

    string s = "   qqq   ";
    string s1 = trim(s);
    cout << "trim:|" << s1 << "|" << endl;
    
    cout << "original ------------------------------" << endl;
    print(persons);

    cout << "partitioned ------------------------------" << endl;
    std::partition(
        persons.begin(), persons.end(),
        is_female
    );
    print(persons);

    cout << "erased ------------------------------" << endl;
    persons.erase(
        std::remove_if(persons.begin(), persons.end(), is_not_female),
        persons.end()
    );
    print(persons);

    cout << "filtered ------------------------------" << endl;
    vector<person_t> females;
    copy_if(people.cbegin(), people.cend(),
            back_inserter(females),
            is_female
    );
    print(females);

    cout << "transformed ------------------------------" << endl;
    vector<std::string> names(females.size());
    transform(females.cbegin(), females.cend(),
            names.begin(),
            name
    );
    sprint(names);

    cout << "separated ------------------------------" << endl;
    std::vector<person_t> separated(people.size());
    
    const auto last = std::copy_if(
        people.cbegin(), people.cend(),
        separated.begin(),
        is_female);

    std::copy_if(
        people.cbegin(), people.cend(),
        last,
        is_not_female);
    print(separated);

    cout << "recursion femail:-----------------------------" << endl;
    auto females_name = names_for(people,is_female);
    sprint(females_name);

    cout << "recursion mail:-----------------------------" << endl;
    auto males_name = names_for(people,is_not_female);
    sprint(males_name);

    cout << "recursion 1 femail:-----------------------------" << endl;
    auto females_name_1 = names_for_1(people.begin(), people.end(), is_female);
    sprint(females_name_1);
/*
    cout << "recursion 2 femail:-----------------------------" << endl;
    auto females_name_2 = names_for_2(people.begin(), people.end(), is_female);
    sprint(females_name_2);
*/    

    std::vector<int> v(10, 2);
    std::partial_sum(v.cbegin(), v.cend(), v.begin());
    std::cout << "Among the numbers: ";
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
 
    if (std::all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
        std::cout << "All numbers are even\n";
    }
    if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(), 
                                                     std::placeholders::_1, 2))) {
        std::cout << "None of them are odd\n";
    }
    struct DivisibleBy
    {
        const int d;
        DivisibleBy(int n) : d(n) {}
        bool operator()(int n) const { return n % d == 0; }
    };
 
    if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7))) {
        std::cout << "At least one number is divisible by 7\n";
    }
}