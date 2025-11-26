#include "member.hpp"
#include <string>
#include <iostream>

#pragma once

enum Status {
    Applied,
    InWarehouse,
    OutForDelivery,
    Delivered, 
    NULL_STATUS
};

class Package {
    public:
        Package(){
            status = 4;
            price = 0.0;
        };
        Package(const Member& sender, const Member& receiver, const std::string& trackingNumber,
                double weight,const std::string& note="" , const std::string &deliveryTime)
            : sender(sender), receiver(receiver), trackingNumber(trackingNumber),
              weight(weight), note(note),deliveryTime(deliveryTime) {}

        Member getSender() const {
            return sender;
        }

        Member getReceiver() const {
            return receiver;
        }

        std::string getTrackingNumber() const {
            return trackingNumber;
        }

        double getWeight() const {
            return weight;
        }

        double getPrice() const {
            return price;
        }

        Status getStatus() const {
            return status;
        }

        std::string getPickupCode() const {
            return pickupCode;
        }

        std::string getDeliveryTime() const {
            return deliveryTime;
        }

        std::string getNote() const {
            return note;
        }

        void editStatus(Status newStatus) {
            status = newStatus;
        }

        void editNote(const std::string& newNote) {
            note = newNote;
        }

        void setPickupCode(const std::string& code) {
            pickupCode = code;
        }
        void setPrice(double newPrice) {
            price = newPrice;
        }
        void setNote(const std::string& newNote) {
            note = newNote;
        }
    private:
        Member sender;
        Member receiver;
        std::string trackingNumber;
        double weight; // in kilograms
        double price;
        Status status;
        std::string pickupCode;
        std::string note;
        std::string deliveryTime;
};
