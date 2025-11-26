#include "Package.hpp"
#include <list>
#include <string>
#include <algorithm>
#include <iostream>
#include <string>
#include <ctime>
#pragma once

class PackageList {
    public:
        PackageList() = default;
        //Push and pop functions
        void pushPackage(int method = 0 , Package p = Package());
        void pop_backPackage();
        void pop_frontPackage();
        void removePackageByTrackingNumber(const std::string& trackingNumber);
        void removePackageByPickUpCode(const std::string& pickupCode);
        //Find functions
        Package* FindByPickUpCode(const std::string& pickupCode);
        Package* FindByTrackingNumber(const std::string& trackingNumber);
        Package* FindByMember(const std::string& value , bool SenderOrReceiver , int index);
        Package* FindByDate(const std::string& date);
        // true for sender, false for receiver & index==1 -> name ; ==2 -> phone ; ==3 -> address
        //Sort functions
        void SortByStatus();
        //Display function
        void DisplayPackageDetails(const Package& package) const;
        void DisplayAllPackages() const;
        //edit functions
        void EditPackageStatus(const std::string& trackingNumber, const Status& newStatus);
        void EditPackageNote(const std::string& trackingNumber, const std::string& newNote);

    private:
        std::list<Package> packages;
};

void PackageList::pushPackage(int method , Package p = Package()) {
    if(method == 0) {
        // member setting
        std::string senderName, senderPhone, senderAddress;
        std::string receiverName, receiverPhone, receiverAddress;
        std::cout << "在下方输入栏中依次输入：收件人姓名 <空格> 电话 <空格> 地址\n";
        std::cin >> receiverName >> receiverPhone >> receiverAddress;
        Member receiver(receiverName, receiverPhone, receiverAddress);
        std::cout << "在下方输入栏中依次输入：寄件人姓名 <空格> 电话 <空格> 地址\n";
        std::cin >> senderName >> senderPhone >> senderAddress;
        Member sender(senderName, senderPhone, senderAddress);
        // package setting
        std::string trackingNumber, status, note, deliveryTime;
        double weight; 
        std::cout << "请输入或右键粘贴快递单号：";
        std::cin >> trackingNumber;
        std::cout << "请输入快递重量(kg)：";
        std::cin >> weight;
        status = "已入库";
        std::time_t now = std::time(nullptr);
        std::tm tm = *std::localtime(&now);
        char buf[11];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
        deliveryTime = buf;
        std::cout << "如需添加备注，请在下方输入栏中输入备注内容，若无备注请直接按回车键跳过：";
        std::cin.ignore(); // 清除前一个输入留下的换行符
        std::getline(std::cin, note);
        Package newPackage(sender, receiver, trackingNumber, weight, note, deliveryTime);
        packages.push_back(newPackage);
        std::cout << "包裹已成功添加到列表中！\n";
    } else if (method == 1) {
        packages.push_back(p);
        std::cout << "包裹已成功添加到列表中！\n";
    }
}

void PackageList::pop_backPackage() {
    if (!packages.empty()) {
        packages.pop_back();
        std::cout << "已移除列表末尾的包裹。\n";
    } else {
        std::cout << "包裹列表为空，无法移除包裹。\n";
    }
}

void PackageList::pop_frontPackage() {
    if (!packages.empty()) {
        packages.pop_front();
        std::cout << "已移除列表开头的包裹。\n";
    } else {
        std::cout << "包裹列表为空，无法移除包裹。\n";
    }
}

void PackageList::removePackageByTrackingNumber(const std::string& trackingNumber) {
    for(auto it = packages.begin(); it != packages.end(); ++it) {
        if(it->getTrackingNumber() == trackingNumber) {
            packages.erase(it);
            std::cout << "包裹已通过追踪号移除。\n";
            return;
        }
        else {
            std::cout << "未找到对应追踪号的包裹。\n";
        }
    }
}

void PackageList::removePackageByPickUpCode(const std::string& pickupCode) {
    for(auto it = packages.begin(); it != packages.end(); ++it) {
        if(it->getPickupCode() == pickupCode) {
            packages.erase(it);
            std::cout << "包裹已通过取件码移除。\n";
            return;
        }
        else {
            std::cout << "未找到对应取件码的包裹。\n";
        }
    }
}

Package* PackageList::FindByPickUpCode(const std::string& pickupCode) {
    for(auto& package : packages) {
        if(package.getPickupCode() == pickupCode) {
            return &package;
        }
    }
    return nullptr;
}

Package* PackageList::FindByTrackingNumber(const std::string& trackingNumber) {
    for(auto& package : packages) {
        if(package.getTrackingNumber() == trackingNumber) {
            return &package;
        }
    }
    return nullptr;
}

Package* PackageList::FindByMember(const std::string& value , bool SenderOrReceiver , int index) {
    for(auto& package : packages) {
        if(SenderOrReceiver) { // true for sender
            if(index == 1 && package.getSender().getName() == value) {
                return &package;
            }
            else if(index == 2 && package.getSender().getPhone() == value) {
                return &package;
            }
            else if(index == 3 && package.getSender().getAddress() == value) {
                return &package;
            }
        } else { // false for receiver
            if(index == 1 && package.getReceiver().getName() == value) {
                return &package;
            }
            else if(index == 2 && package.getReceiver().getPhone() == value) {
                return &package;
            }
            else if(index == 3 && package.getReceiver().getAddress() == value) {
                return &package;
            }
        }
    }
    return nullptr;
}

Package* PackageList::FindByDate(const std::string& date) {
    for(auto& package : packages) {
        if(package.getDeliveryTime() == date) {
            return &package;
        }
    }
    return nullptr;
}

void PackageList::SortByStatus() {
    packages.sort([](const Package& a, const Package& b) {
        return a.getStatus() < b.getStatus();
    });//lambda表达式用于定义排序规则
    std::cout << "包裹列表已按状态排序。\n";
}

void PackageList::DisplayPackageDetails(const Package& package) const {
    std::cout << "快递单号: " << package.getTrackingNumber() << "\n"
              << "寄件人: " << package.getSender().getName() << ", "
              << package.getSender().getPhone() << ", "
              << package.getSender().getAddress() << "\n"
              << "收件人: " << package.getReceiver().getName() << ", "
              << package.getReceiver().getPhone() << ", "
              << package.getReceiver().getAddress() << "\n"
              << "重量: " << package.getWeight() << " kg\n"
              << "状态: " << package.getStatus() << "\n"
              << "备注: " << package.getNote() << "\n"
              << "取件码: " << package.getPickupCode() << "\n"
              << "入库时间: " << package.getDeliveryTime() << "\n";
}

void PackageList::DisplayAllPackages() const {
    if (packages.empty()) {
        std::cout << "包裹列表为空。\n";
        return;
    }
    for (const auto& package : packages) {
        std::cout << "快递单号: " << package.getTrackingNumber() << "\n"
                  << "寄件人: " << package.getSender().getName() << ", "
                  << package.getSender().getPhone() << ", "
                  << package.getSender().getAddress() << "\n"
                  << "收件人: " << package.getReceiver().getName() << ", "
                  << package.getReceiver().getPhone() << ", "
                  << package.getReceiver().getAddress() << "\n"
                  << "重量: " << package.getWeight() << " kg\n"
                  << "状态: " << package.getStatus() << "\n"
                  << "备注: " << package.getNote() << "\n"
                  << "取件码: " << package.getPickupCode() << "\n"
                  << "入库时间: " << package.getDeliveryTime() << "\n"
                  << "--------------------------\n";
    }
}

void PackageList::EditPackageStatus(const std::string& trackingNumber, const Status& newStatus) {
    Package* package = FindByTrackingNumber(trackingNumber);
    if(package) {
        package->editStatus(newStatus);
        std::cout << "包裹状态已更新。\n";
    } else {
        std::cout << "未找到对应追踪号的包裹，无法更新状态。\n";
    }
}

void PackageList::EditPackageNote(const std::string& trackingNumber, const std::string& newNote) {
    Package* package = FindByTrackingNumber(trackingNumber);
    if(package) {
        package->editNote(newNote);
        std::cout << "包裹备注已更新。\n";
    } else {
        std::cout << "未找到对应追踪号的包裹，无法更新备注。\n";
    }
}


