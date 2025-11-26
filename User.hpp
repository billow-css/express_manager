#pragma once
#include<iostream>
#include<string>
#include "Package.hpp"
#include "member.hpp"
#include "PackageList.hpp"

typedef int METHOD;

class Visitor{
    /*Visitor代码表述：建立一个基础的基类，仅仅包含查询、申请入库、自助出库操作*/
public:
    Visitor()=default;

    Package search_package(std::string value , METHOD code = 0 , PackageList p);
    void apply(Package c , PackageList p);
    void getpackage(METHOD code , std::string value , PackageList p);
private:
    std::string phone_number;
};

class StdUser : public Visitor{
    /*StdUser代码表述：标准用户，继承自游客，新增无条件入库和批量文件入库*/
public:
    StdUser() = default;
    void agreeapply(PackageList &p , std::string trackingNumber);
    void apply_unconditionally(Package c);
    void batch_apply(const std::string& filename);
    void getpackage(std::string trackingNumber);

private:
    std::string password;
};

class Admin : public StdUser{
    /*Admin代码表述：管理员，继承自标准用户，作为管理员，可以自行设定一切配置，包括出库的方法规则，运费，以及pickupcode的生成规则等*/
public:
    Admin() = default;
    void set_delivery_rule(std::string &config_address);
    void set_price_rule(std::string &config_address);
    void set_pickupcode_rule(std::string &config_address);
private:
    std::string admin_password;
};

Package Visitor::search_package(std::string value , METHOD code , PackageList p){
    /*根据不同的code，选择不同的查询方式*/
    Package* result = nullptr;
    switch(code){
        case 0: //tracking number
            result = p.FindByTrackingNumber(value);
            break;
        case 1: //pick up code
            result = p.FindByPickUpCode(value);
            break;
        case 2: //mobile number
            result = p.FindByMember(phone_number , false , 2); //search by receiver phone number
            break;
        case 3: //date
            result = p.FindByDate(value);
            break;
        default:
            std::cout << "无效的查询方式代码！" << std::endl;
            return;
    }
    if(result){
        return *result;
    } else {
        std::cout << "未找到对应包裹！" << std::endl;
        return;
    }
}

void Visitor::apply(Package c , PackageList p){
    
    p.pushPackage(1, c);
    std::cout << "包裹已成功申请入库！" << std::endl;
}

void Visitor::getpackage(METHOD code , std::string value , PackageList p){
/*当code = 0，只需要tracking number，code = 1，则需要手机号和tracking number， code = 2，暂停出库*/
    Package* result = nullptr;
    switch(code){
        case 0: //tracking number only
            result = p.FindByTrackingNumber(value);
            break;
        case 1: //phone number + tracking number
            result = p.FindByMember(phone_number , false , 2); //search by receiver phone number
            if(result && result->getTrackingNumber() == value){
                //match
            } else {
                result = nullptr; //not match
            }
            break;
        case 2: //suspend
            std::cout << "出库操作已暂停！" << std::endl;
            return;
        default:
            std::cout << "无效的出库方式代码！" << std::endl;
            return;
    }
    if(result){
        p.removePackageByTrackingNumber(result->getTrackingNumber());
        std::cout << "包裹已成功出库！" << std::endl;
    } else {
        std::cout << "未找到对应包裹，无法出库！" << std::endl;
    }
}

void StdUser::apply_unconditionally(Package c){
    /*标准用户无条件入库操作*/
    //假设有一个全局的PackageList对象packageList
    extern PackageList packageList;
    packageList.pushPackage(1, c);
    std::cout << "包裹已成功无条件申请入库！" << std::endl;
}

void StdUser::batch_apply(const std::string& filename){
    /*暂时不写*/
}

void StdUser::getpackage(std::string trackingNumber){
    /*标准用户出库操作*/
    //假设有一个全局的PackageList对象packageList
    extern PackageList packageList;
    Package* result = packageList.FindByTrackingNumber(trackingNumber);
    if(result){
        packageList.removePackageByTrackingNumber(trackingNumber);
        std::cout << "包裹已成功出库！" << std::endl;
    } else {
        std::cout << "未找到对应包裹，无法出库！" << std::endl;
    }
}

void StdUser::agreeapply(PackageList &p , std::string trackingNumber){
    Package *c = p.FindByTrackingNumber(trackingNumber); //假设通过某种方式获得需要同意入库的包裹
    c->editStatus(InWarehouse); //将包裹状态改为已入库
}