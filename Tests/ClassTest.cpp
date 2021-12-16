#include "ClassTests.h"

Person::Person()
        : last_name(""), first_name(""), patronymic(std::nullopt) {}

Person::Person(std::string l_name, std::string f_name)
        : last_name(l_name), first_name(f_name), patronymic(std::nullopt) {}

Person::Person(std::string l_name, std::string f_name, std::string patr)
        : last_name{std::move(l_name)}, first_name{std::move(f_name)}, patronymic{std::move(patr)} {}

std::string Person::GetFirstName() const { return first_name; }

std::optional<std::string> Person::GetPatronymic() const { return patronymic; }

std::string Person::GetLastName() const {return last_name;}

Person Person::ReadFromStream(std::istringstream& iss) {
    Person person;
    constexpr int IGNORE_NUM = 1;
    std::string temp;
    if (iss.peek() == ' ')
        iss.ignore(IGNORE_NUM);
    iss >> person.last_name >> person.first_name >> temp;
    if (temp != "-")
        person.patronymic.emplace(temp);
    return person;
}

void Person::SetPerson(std::istringstream& iss) {
    std::string temp;
    iss >> last_name >> first_name >> temp;
    if (temp == "-")
        return;
    else
        patronymic.emplace(temp);
}

std::ostream& operator<< (std::ostream& out, const Person& person) {
    out << person.last_name << ' ' << person.first_name;
    if (person.patronymic.has_value())
        out << ' ' << person.patronymic.value();
    return out;
}

bool operator< (const Person& lhs, const Person& rhs) {
    return std::tie(lhs.last_name, lhs.first_name, lhs.patronymic) <
           std::tie(rhs.last_name, rhs.first_name, rhs.patronymic);
}

bool operator== (const Person& lhs, const Person& rhs) {
    return std::tie(lhs.last_name, lhs.first_name, lhs.patronymic) ==
           std::tie(rhs.last_name, rhs.first_name, rhs.patronymic);
}

PhoneNumber::PhoneNumber()
        : country_code(0), city_code(0), number("0000000"), add_number(std::nullopt) {}

PhoneNumber::PhoneNumber(int country, int city, std::string num, std::optional<int> add_num)
        : country_code{country}, city_code{city}, number{std::move(num)}, add_number{add_num} {}

PhoneNumber::PhoneNumber(int country, int city, std::string num)
        : country_code{country}, city_code{city}, number{std::move(num)} {}

int PhoneNumber::getCountryCode() const {
    return country_code;
}

int PhoneNumber::GetCityCode() const {
    return city_code;
}

std::string PhoneNumber::GetNumber() const {
    return number;
}

std::optional<int> PhoneNumber::GetAddNumber() const {
    if (const int add_num = add_number.value())
        return add_num;
    else
        return add_number;
}

PhoneNumber PhoneNumber::ReadFromStream(std::istringstream& iss) {
    PhoneNumber phonenumb;
    constexpr int IGNORE_NUM = 1;
    if (iss.peek() == ' ')
        iss.ignore(IGNORE_NUM);
    iss >> phonenumb.country_code >> phonenumb.city_code >>
        phonenumb.number;
    if (iss.peek() != '-') {
        iss >> phonenumb.add_number.emplace();
    }
    return phonenumb;
}

void PhoneNumber::SetPhoneNumber(std::istringstream& iss) {
    std::string temp;
    iss >> country_code >> city_code >> number >> temp;

    if (temp == "-")
        return;
    else
        add_number.emplace(std::stoi(temp));
}

std::ostream& operator<< (std::ostream& out, const PhoneNumber& phone_number) {
    out << '+' << phone_number.getCountryCode() << " (" << phone_number.GetCityCode() << ") " <<
        phone_number.GetNumber() << ' ';
    if (phone_number.add_number.has_value()) {
        out << phone_number.add_number.value();
    }
    return out;
}

bool operator< (const PhoneNumber& num1, const PhoneNumber& num2) {
    return std::tie(num1.country_code, num1.city_code, num1.number, num1.add_number) <
           std::tie(num2.country_code, num2.city_code, num2.number, num2.add_number);
}

PhoneBook::PhoneBook(std::ifstream& file)
{
    FileToObj(file);
    if (!file)
        std::cerr << "Cannot open the file\n";
}

PhoneBook::~PhoneBook() {
}

void PhoneBook::FileToObj(std::ifstream& file) {

    while (!file.eof()) {
        std::getline(file, string);
        std::istringstream istringstr(string);
        Person person;
        PhoneNumber number;
        person.SetPerson(istringstr);
        number.SetPhoneNumber(istringstr);
        phone_book.push_back(std::make_pair(person, number));
    }
}

void PhoneBook::SortByName() {
    std::sort(phone_book.begin(), phone_book.end(), [](std::pair<Person, PhoneNumber> lhs,
                                                       std::pair<Person, PhoneNumber> rhs) {
        return lhs.first < rhs.first;
    });
}

void PhoneBook::SortByPhone() {
    std::sort(phone_book.begin(), phone_book.end(), [](std::pair<Person, PhoneNumber> lhs,
                                                       std::pair<Person, PhoneNumber> rhs) {
        return lhs.second < rhs.second;
    });
}

std::tuple<std::string, PhoneNumber>
PhoneBook::GetPhoneNumber(const std::string& surname) {
    size_t count = 0;
    const PhoneNumber* number {};
    auto lambda = [&](auto& entry) {
        if (entry.first.GetLastName() == surname) {
            count++;
            number = &entry.second;
        }
    };
    std::for_each(phone_book.begin(), phone_book.end(), lambda);
    if (count == 0)
        return {"None found!", {}};
    else if (count > 1)
        return {"Found more than one!", *number};
    return {"", *number};
}

void PhoneBook::ChangePhoneNumber(const Person& person, PhoneNumber new_num) {
    auto user = std::find_if(phone_book.begin(), phone_book.end(), [&person](std::pair<Person, PhoneNumber>& user) {
        return user.first == person;
    });

    if (user != phone_book.end())
        user->second = new_num;
}

std::ostream& operator<< (std::ostream& out, PhoneBook& book) {
    for (const auto& iter : book.phone_book) {
        out << iter.first << ' ' << iter.second << std::endl;
    }
    return out;
}

