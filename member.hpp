# pragma once
# include <string>

class Member{
    public:
        Member() = default;
        Member(const std::string& name, const std::string& phone, const std::string& address)
            : name(name), phone(phone), address(address) {}

        std::string getName() const {
            return name;
        }

        std::string getPhone() const {
            return phone;
        }

        std::string getAddress() const {
            return address;
        }

        void editName(const std::string& newName) {
            name = newName;
        }

        void editPhone(const std::string& newPhone) {
            phone = newPhone;
        }

        void editAddress(const std::string& newAddress) {
            address = newAddress;
        }
    private:
        std::string name;
        std::string phone;
        std::string address;
};