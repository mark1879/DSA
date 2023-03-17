#include "consistent_hash.hpp"
#include <gtest/gtest.h>
#include <vector>

// std::pair<physical_host_ip, virtual_hosts_num>
void TestCase(const std::vector<std::pair<std::string, size_t>>& hosts, const std::string& client_ip)
{
    ConsistentHash consistent_hash;

    for (const auto& it : hosts)
    {
        consistent_hash.AddHost(it.first, it.second);
    }

    std::string host = consistent_hash.GetHost(client_ip);

    EXPECT_EQ(host.compare(consistent_hash.GetHost(client_ip)) == 0, true);

    consistent_hash.RemoveHost(host);

    EXPECT_EQ(host.compare(consistent_hash.GetHost(client_ip)) != 0, true);
}

int main()
{
    std::cout << "test_consistent_hash..." << std::endl;

    std::vector<std::pair<std::string, size_t>> hosts;
    hosts.push_back(std::make_pair("10.117.124.10", 150));
    hosts.push_back(std::make_pair("10.117.124.20", 150));
    hosts.push_back(std::make_pair("10.117.124.30", 150));

    TestCase(hosts, "192.168.1.123");

    std::cout << "test done!" << std::endl;

    return 0;
}