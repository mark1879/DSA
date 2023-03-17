#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <unordered_map>
#include <memory>

#include "md5.h"

using UINT = unsigned int;

class PhysicalHost;

class VirtualHost
{
public:
    VirtualHost(const std::string& ip, std::shared_ptr<PhysicalHost> host)
        : ip_(ip)
        , physical_host_(host)
    {
        md5_ = ::getMD5(ip.c_str());
    }

    ~VirtualHost()
    {}

    bool operator<(const VirtualHost& host) const
    {
        return md5_ < host.md5_;
    }

    bool operator=(const VirtualHost& host) const
    {
        return ip_ == host.ip_;
    }

    UINT md5() const
    {
        return md5_;
    }

    const std::shared_ptr<PhysicalHost> physical_host() const
    {
        return physical_host_;
    }

private:
    std::string ip_;
    UINT md5_;
    std::shared_ptr<PhysicalHost> physical_host_;
};


class PhysicalHost : public std::enable_shared_from_this<PhysicalHost>
{
public:
    PhysicalHost(const std::string& ip)
        : ip_(ip)
    {}

    ~PhysicalHost()
    {}

    void CreateVirtualHosts(size_t virtual_host_num)
    {
        if (virtual_hosts_.size() > 0)
            return;
        
        for (size_t i = 0; i < virtual_host_num; i++)
        {
            virtual_hosts_.emplace_back(ip_ + "#" + std::to_string(i), shared_from_this());
        }
    }

    std::string ip() const 
    {
        return ip_;
    }

    const std::vector<VirtualHost>& virtual_hosts() const
    {
        return virtual_hosts_;
    }

private:
    std::string ip_;
    std::vector<VirtualHost> virtual_hosts_;
};


class ConsistentHash
{
public:
    void AddHost(const std::string physical_host_ip, size_t virtual_host_num)
    {
        std::shared_ptr<PhysicalHost> host_ptr(new PhysicalHost(physical_host_ip));
        host_ptr->CreateVirtualHosts(virtual_host_num);

        physical_hosts_.emplace(physical_host_ip, host_ptr);

        auto virtual_hosts = host_ptr->virtual_hosts();
        for (const auto& host : virtual_hosts)
        {
            hash_circle_.insert(host);
        }
    }

    void RemoveHost(const std::string physical_host_ip)
    {
        auto iter = physical_hosts_.find(physical_host_ip);
        if (iter == physical_hosts_.end())
            return;

        auto virtual_hosts = iter->second->virtual_hosts();
        for (const auto& host : virtual_hosts)
        {
            auto it = hash_circle_.find(host);
            if (it != hash_circle_.end())
            {
                hash_circle_.erase(it);
            }
        }
    }

    std::string GetHost(const std::string& client_ip)
    {
        UINT md5 = ::getMD5(client_ip.c_str());
        for(const auto& host : hash_circle_)
        {
            if (host.md5() > md5)
            {
                return host.physical_host()->ip();
            }
        }

        return hash_circle_.begin()->physical_host()->ip();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<PhysicalHost>> physical_hosts_;
    std::set<VirtualHost> hash_circle_;
};

