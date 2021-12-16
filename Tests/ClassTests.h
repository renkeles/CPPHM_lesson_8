#pragma once

#include <tuple>
#include <optional>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>

class Person {
public:
    Person();

    Person(std::string l_name, std::string f_name);

    Person(std::string l_name, std::string f_name, std::string patr);

    std::string GetFirstName() const;

    std::optional<std::string> GetPatronymic() const;

    std::string GetLastName() const;

    static Person ReadFromStream(std::istringstream& iss);

    void SetPerson(std::istringstream& iss);

    friend std::ostream& operator<< (std::ostream& out, const Person& person);

    friend bool operator< (const Person& lhs, const Person& rhs);

    friend bool operator== (const Person& lhs, const Person& rhs);

private:
    std::string last_name;
    std::string first_name;
    std::optional<std::string> patronymic;
};

class PhoneNumber {
public:
    PhoneNumber();

    PhoneNumber(int country, int city, std::string num, std::optional<int> add_num);

    PhoneNumber(int country, int city, std::string num);

    int getCountryCode() const;

    int GetCityCode() const;

    std::string GetNumber() const;

    std::optional<int> GetAddNumber() const;

    static PhoneNumber ReadFromStream(std::istringstream& iss);

    void SetPhoneNumber(std::istringstream& iss);

    friend std::ostream& operator<< (std::ostream& out, const PhoneNumber& phone_number);

    friend bool operator< (const PhoneNumber& num1, const PhoneNumber& num2);

private:
    int country_code;
    int city_code;
    std::string number;
    std::optional<int> add_number;
};

class PhoneBook {
public:
    PhoneBook(std::ifstream& file);

    ~PhoneBook();

    void FileToObj(std::ifstream& file);

    bool ComparePersons(std::pair<Person, PhoneNumber> lhs, std::pair<Person, PhoneNumber> rhs);

    std::vector<std::pair<Person, PhoneNumber>> GetPhoneBook() { return phone_book; }

    void SortByName();

    void SortByPhone();

    std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string& surname);

    void ChangePhoneNumber(const Person& person, PhoneNumber number);

    friend std::ostream& operator<< (std::ostream& out, PhoneBook& book);

private:
    std::string string;
    std::vector<std::pair<Person, PhoneNumber>> phone_book;
};
