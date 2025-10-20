# 快递驿站管理系统

# 开发文档

## 0.0.0 2025/10/17 environment test：
commit：陈俊亦202483290008

10月17日，创建工程文件，测试编译命令，一切正常。
并且，完善了相关规则

## 0.0.1 2025/10/18 member
commit：陈俊亦202483290008

新建了快递包裹上收件人与寄件人的统一类：member，记录收件人与寄件人的姓名，电话，地址，避免全部放在packet中要素过多。
并且member支持创建后编辑，但是原则上不可删除。

## 0.0.2 2025/10/20 package-alpha
commit: 陈俊亦202483290008

新建了package类，手册如下：
# Package 类摘要


## 类概述  
`Package` 类用于封装包裹的相关信息，包括寄件人、收件人、追踪号、重量、价格、状态、取件码及备注等，并提供了获取和修改这些信息的方法。


## 私有成员变量  
- `Member sender`：寄件人信息（`Member` 类型）  
- `Member receiver`：收件人信息（`Member` 类型）  
- `std::string trackingNumber`：包裹追踪号  
- `double weight`：包裹重量（单位：千克）  
- `double price`：包裹价格  
- `std::string status`：包裹状态（如“已发出”“已签收”等）  
- `std::string pickupCode`：取件码  
- `std::string note`：备注信息  


## 构造函数  
- 禁用默认构造函数（`Package() = delete`）。  
- 带参构造函数：  
  ```cpp  
  Package(const Member& sender, const Member& receiver, const std::string& trackingNumber,
          double weight, const std::string& status, const std::string& note="")  
  ```  
  作用：初始化包裹信息，参数依次为寄件人、收件人、追踪号、重量、状态，`note` 为可选参数（默认空字符串）。  


## 公共成员函数  

### Getter 方法（获取属性）  
- `Member getSender() const`：返回寄件人信息  
- `Member getReceiver() const`：返回收件人信息  
- `std::string getTrackingNumber() const`：返回追踪号  
- `double getWeight() const`：返回重量（千克）  
- `double getPrice() const`：返回价格  
- `std::string getStatus() const`：返回包裹状态  
- `std::string getPickupCode() const`：返回取件码  
- `std::string getNote() const`：返回备注  


### 修改/设置方法  
- `void editStatus(const std::string& newStatus)`：修改包裹状态  
- `void editNote(const std::string& newNote)`：修改备注（与 `setNote` 功能重复）  
- `void setPickupCode(const std::string& code)`：设置取件码  
- `void setPrice(double newPrice)`：设置价格  
- `void setNote(const std::string& newNote)`：修改备注（与 `editNote` 功能重复）

## 0.0.3 2025/10/20 packagelist-head
commit：陈俊亦202483290008

新建了package的链表类，声明了函数，函数实现功能如下：
# PackageList 类功能摘要

## 1. 类概述
`PackageList` 类用于管理 `Package` 对象集合，基于 `std::list<Package>` 容器实现，支持包裹的增删查改、排序及展示等核心操作，适配更细致的查询与删除需求。


## 2. 核心功能分类

### 2.1 包裹增减操作
- `pushPackage(const Package& package)`：添加包裹到列表
- `pop_backPackage()`：移除列表末尾包裹
- `pop_frontPackage()`：移除列表开头包裹
- `removePackageByTrackingNumber(const std::string& trackingNumber)`：按追踪号移除指定包裹
- `removePackageByPickUpCode(const std::string& pickupCode)`：按取件码移除指定包裹


### 2.2 包裹查询功能
- `FindByPickUpCode(const std::string& pickupCode)`：通过取件码查找包裹（返回 `Package*`）
- `FindByTrackingNumber(const std::string& trackingNumber)`：通过追踪号查找包裹（返回 `Package*`）
- `FindByMember(const Member& member, bool SenderOrReceiver, int index)`：按会员信息查找（寄件人/收件人，匹配姓名/电话/地址）
- `FindByMemberName(const std::string& name, bool SenderOrReceiver)`：按寄件人/收件人姓名查找包裹（返回 `Package*`）
- `FindByMemberPhone(const std::string& phone, bool SenderOrReceiver)`：按寄件人/收件人电话查找包裹（返回 `Package*`）
- `FindByDate(const std::string& date)`：通过日期查找包裹（返回 `Package*`）
- `FindByStatus(const std::string& status)`：通过状态查找包裹（返回 `Package*`）


### 2.3 排序与展示
- `SortByStatus()`：按包裹状态排序
- `DisplayAllPackages() const`：展示所有包裹信息


### 2.4 包裹信息编辑
- `EditPackageStatus(const std::string& trackingNumber, const std::string& newStatus)`：按追踪号修改状态
- `EditPackageNote(const std::string& trackingNumber, const std::string& newNote)`：按追踪号修改备注


## 3. 底层存储
- 私有成员 `std::list<Package> packages`：存储所有包裹对象，适合频繁增删场景