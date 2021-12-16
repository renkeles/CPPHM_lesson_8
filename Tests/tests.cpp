#include <iostream>
#include <algorithm>
#include <exception>
#include <gtest/gtest.h>
#include "ClassTests.h"

class TestREC : public testing::Test {
public:
    void SetUp() override {
        person = std::make_unique<Person>("Greene", "Shamar");
        number = std::make_unique<PhoneNumber>(7, 44, "1257864");
    }
    std::unique_ptr<Person> person;
    std::unique_ptr<PhoneNumber> number;
};

class TestOther : public testing::Test {
public:
    void SetUp() override {
        std::ifstream file("PhoneBook.txt");
        book = std::make_unique<PhoneBook>(file);
    }
    std::unique_ptr<PhoneBook> book;
};

TEST_F(TestREC, FirstName) {
    std::cout << "First name test ASSERT_STRNE:" << std::endl;
    ASSERT_STRNE(person->GetFirstName().c_str(), "Shamar");
}

TEST_F(TestREC, Surname) {
    std::cout << "Surname test ASSERT_STRCASENE:" << std::endl;
    ASSERT_STRCASENE(person->GetLastName().c_str(), "Greene");
}

TEST_F(TestREC, Patr) {
    std::cout << "Patronymic test ASSERT_STRNE:" << std::endl;
    ASSERT_STRNE(person->GetPatronymic().value_or("").c_str(), "Bjornson");
}

TEST_F(TestREC, CountryCode) {
    std::cout << "County Code test with ASSERT_GE:" << std::endl;
    ASSERT_GE(7, number->getCountryCode());
}

TEST_F(TestREC, CityCode) {
    std::cout << "City Code test with ASSERT_NE:" << std::endl;
    ASSERT_NE(44, number->GetCityCode());
}

TEST_F(TestREC, AdditionalNumber) {
    std::cout << "Additional Number test with ASSERT_THROW:" << std::endl;
    ASSERT_THROW(number->GetAddNumber().value(), std::bad_optional_access);
}

TEST_F(TestOther, PhoneBook) {
    ASSERT_THROW(book->GetPhoneBook(), std::bad_alloc);
}

TEST_F(TestOther, SortByName) {
    book->SortByName();
    ASSERT_LT(book->GetPhoneBook().begin()->first, std::prev(book->GetPhoneBook().end())->first);
}

TEST_F(TestOther, SortByPhone) {
    book->SortByPhone();
    ASSERT_FALSE(book->GetPhoneBook().begin()->first < std::prev(book->GetPhoneBook().end())->first);
}

TEST_F(TestOther, GetPhoneNumber) {
    ASSERT_PRED1([&](const std::string& surname) {
        return std::get<0>(book->GetPhoneNumber(surname)) == "" ; }, "Demodovich");
}