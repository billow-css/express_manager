#include "Package.h"
#include <list>
#include <string>
#pragma once

class PackageList {
    public:
        PackageList() = default;
        //Push and pop functions
        void pushPackage();
        void pop_backPackage();
        void pop_frontPackage();
        void removePackageByTrackingNumber(const std::string& trackingNumber);
        void removePackageByPickUpCode(const std::string& pickupCode);
        //Find functions
        Package* FindByPickUpCode(const std::string& pickupCode);
        Package* FindByTrackingNumber(const std::string& trackingNumber);
        Package* FindByMember(const Member& member , bool SenderOrReceiver , int index);
        Package* FindByDate(const std::string& date);
        // true for sender, false for receiver & index==1 -> name ; ==2 -> phone ; ==3 -> address
        //Sort functions
        void SortByStatus();
        //Display function
        void DisplayPackageDetails(const Package& package) const;
        void DisplayAllPackages() const;
        //edit functions
        void EditPackageStatus(const std::string& trackingNumber, const std::string& newStatus);
        void EditPackageNote(const std::string& trackingNumber, const std::string& newNote);

    private:
        std::list<Package> packages;
};