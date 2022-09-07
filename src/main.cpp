#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <vector>
#include <random>

#include "logsloth.h"
#include "myutil.h"


void _p10_namespace() {
    auto tNow = std::chrono::system_clock::now();
    LOGSLOTH("tNow:%lu", tNow.time_since_epoch());
}

////////////////////////////////////////////////////////////////////////////////


void _p11_using() {
    using namespace std;
    cout << "hello" << endl;
}


////////////////////////////////////////////////////////////////////////////////


void _p12_using_alias() {
    using sysClock = std::chrono::system_clock;
    auto now = sysClock::now();
}


////////////////////////////////////////////////////////////////////////////////


void _p16_min_max() {
    std::cout << "std::min:" << std::min(2011, 2014) << std::endl;
    std::cout << "std::min array:" << std::min({1, 2, 3, 4, 5}) << std::endl;
    std::cout << "std::min lambda:"
              << std::min({1, 2, -3, -4, -5}, [](int a, int b) { return std::abs(a) < std::abs(b); }) << std::endl;
    auto minMaxRes = std::minmax({1, 2, -3, -4, -5});
    std::cout << "std::minmax:" << minMaxRes.first << ":" << minMaxRes.second << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void _p17_move() {
    auto myBigVec = std::vector<int>(10000000, 2011);
    LOGSLOTH("myBigVec:%lu:%p", myBigVec.size(), myBigVec.data());
    auto myVec = myBigVec;
    LOGSLOTH("myBigVec:%lu:%p", myBigVec.size(), myBigVec.data());
    LOGSLOTH("myVec:%lu:%p", myVec.size(), myVec.data());
    auto myVec2 = std::move(myBigVec);
    LOGSLOTH("myBigVec:%lu:%p", myBigVec.size(), myBigVec.data());
    LOGSLOTH("myVec:%lu:%p", myVec.size(), myVec.data());
    LOGSLOTH("myVec2:%lu:%p", myVec2.size(), myVec2.data());
}

////////////////////////////////////////////////////////////////////////////////

void _p19_swap() {
    auto a = 1;
    auto b = 2;
    LOGSLOTH("a:%d b:%d", a, b);
    std::swap(a, b);
    LOGSLOTH("a:%d b:%d", a, b);
}

////////////////////////////////////////////////////////////////////////////////

void _p22_pair() {
    auto myPair = std::make_pair("str", 3.14);
    LOGSLOTH("myPair:%s:%f", myPair.first, myPair.second);
}

////////////////////////////////////////////////////////////////////////////////

void _p23_tuple() {
    auto myTuple = std::make_tuple("str", 3.14, "hhd");
    LOGSLOTH("myTuple:%s:%f:%s", std::get<0>(myTuple), std::get<1>(myTuple), std::get<2>(myTuple));
}

////////////////////////////////////////////////////////////////////////////////

class MyInt {
public:
    int _i;

    MyInt() {
        LOGSLOTH("MyInt()");
    }

    MyInt(int i) {
        _i = i;
        LOGSLOTH("MyInt() _i:%d", _i);
    }

    ~MyInt() {
        LOGSLOTH("~MyInt() _i:%d", _i);
    }


};


void _p52_container_compare();

void _p29_unique_ptr() {

    auto up0 = std::make_unique<MyInt>(0);

    {
        auto up1 = std::make_unique<MyInt>(1);
    }

    auto up2 = std::make_unique<MyInt>(2);
    auto up3 = std::move(up2);
}

void _p32_shared_ptr() {
    auto sp0 = std::make_shared<MyInt>(0);

    {
        auto sp1 = std::make_shared<MyInt>(1);
    }

    auto sp2 = std::make_shared<MyInt>(2);
    std::shared_ptr<MyInt[]> spArray{new MyInt[3]};

    auto sp3 = sp2;
    LOGSLOTH("sp2:%d:%ld sp3:%d:%ld", sp2->_i, sp2.use_count(), sp3->_i, sp3.use_count());
    auto sp4 = sp2;
    LOGSLOTH("sp2:%d:%ld sp3:%d:%ld", sp2->_i, sp2.use_count(), sp3->_i, sp3.use_count());
}

void _p42_chrono_duration() {
    std::vector<int> myBigVec(10000000, 2011);
    std::vector<int> myEmptyVec;

    auto tStart = std::chrono::high_resolution_clock::now();
    myEmptyVec = myBigVec;
    auto tEnd = std::chrono::high_resolution_clock::now();
    auto ts = tEnd - tStart;
    LOGSLOTH("ts:%lld(ns)", ts.count());
    auto tsMs = std::chrono::duration_cast<std::chrono::milliseconds>(ts).count();
    LOGSLOTH("tsMs:%lld(ms)", tsMs);

    std::chrono::seconds ts100Sec(100);
    std::chrono::minutes ts5Min(5);
    std::chrono::milliseconds ts30Ms(30);
    auto tsSum = ts100Sec + ts5Min + ts30Ms;
    LOGSLOTH("tsSum:%ld(min)", std::chrono::duration_cast<std::chrono::minutes>(tsSum).count());
    LOGSLOTH("tsSum:%lld(sec)", std::chrono::duration_cast<std::chrono::seconds>(tsSum).count());
    LOGSLOTH("tsSum:%lld(ms)", std::chrono::duration_cast<std::chrono::milliseconds>(tsSum).count());

    auto sysClockStart = std::chrono::system_clock::now();
    myEmptyVec = myBigVec;
    auto sysClockEnd = std::chrono::system_clock::now();
    auto tsSysClock = sysClockEnd - sysClockStart;
    LOGSLOTH("tsSysClock:%lld(ms)", std::chrono::duration_cast<std::chrono::milliseconds>(tsSysClock).count());
}

void _p48_container_new_delete() {
    //기본
    std::vector<int> vec1;
    LOGSLOTH("vec1:%lu:%p", vec1.size(), vec1.data());

    //순차열
    std::vector<int> vec2{1, 2, 3, 4, 5};
    std::vector<int> vec2_1 = {1, 2, 3, 4, 5};
    LOGSLOTH("vec2:%lu:%p", vec2.size(), vec2.data());
    LOGSLOTH("vec2_1:%lu:%p", vec2_1.size(), vec2_1.data());

    //복사
    auto vec3 = vec2;
    LOGSLOTH("vec3:%lu:%p", vec3.size(), vec3.data());

    //이동
    auto vec4 = std::move(vec3);
    LOGSLOTH("vec3:%lu:%p", vec3.size(), vec3.data());
    LOGSLOTH("vec4:%lu:%p", vec4.size(), vec4.data());

    //요소삭제
    vec4.clear();
    LOGSLOTH("vec4:%lu:%p", vec4.size(), vec4.data());
}

void _p51_container_iter() {
    std::vector<int> myVec;
    myVec.push_back(1);
    myVec.emplace_back(3);
    myVec.push_back(5);
    myVec.emplace_back(7);
    myVec.insert(myVec.begin(), 9);
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
    myVec.pop_back();
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
    myVec.insert(myVec.begin() + 2, 100);
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
}

void _p52_container_compare() {
    std::vector<int> v1{1, 2, 3, 4};
    std::vector<int> v2{1, 2, 3, 4};
    LOGSLOTH("v1 == v2:%d", v1 == v2);
}


void _p69_map() {
    std::map<std::string, int> m{
            {"a", 1},
            {"b", 2},
            {"c", 3},
    };

    for (auto item: m) {
        LOGSLOTH("MAP_ITER %s:%d", item.first.c_str(), item.second);
    }

    auto a_exist = m.find("a") != m.end();
    LOGSLOTH("a_exist:%d", a_exist);
    auto d_exist = m.find("d") != m.end();
    LOGSLOTH("d_exist:%d", d_exist);
    m.erase("b");
    auto b_exist = m.find("b") != m.end();
    LOGSLOTH("b_exist:%d", b_exist);
    m["d"] = 4;

    std::map<std::string, int> m2{
            {"h", 10},
            {"i", 20},
            {"j", 30},
    };

    std::map<std::string, int> m3;
    m3.insert(m.begin(), m.end());
    m3.insert(m2.begin(), m2.end());

    for (auto item: m3) {
        LOGSLOTH("MAP_ITER %s:%d", item.first.c_str(), item.second);
    }
}

void _p88_copy() {
    std::vector v{1, 2, 3};
    std::vector<int> v2;
    v2.resize(v.size());
    std::copy(v.begin(), v.end(), v2.begin());
    auto infoStr = MyUtil::getVectorInfoStr(v2, "v2", "%d");
    LOGSLOTH(infoStr);

    std::vector<int> v3;
    v3.resize(v.size());
    std::copy(v.rbegin(), v.rend(), v3.begin());
    auto infoStr3 = MyUtil::getVectorInfoStr(v3, "v3", "%d");
    LOGSLOTH(infoStr3);
}

void _p100_lambda() {
    std::vector<int> myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::for_each(myVec.begin(), myVec.end(), [](int &i) {
        auto res = i * i;
        i = res;
    });

    LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
}

void _p105_foreach() {
    std::vector<int> myVec{1, 2, 3};
    auto myVec2 = std::for_each(myVec.begin(), myVec.end(), [](auto &item) { new MyInt(item); });
    //--------------------------------------------------------------------------------
    // MyInt MyInt() _i:1
    // MyInt MyInt() _i:2
    // MyInt MyInt() _i:3
    //--------------------------------------------------------------------------------
}

void _p107_count_if() {
    std::vector<int> myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto count_per_3 = std::count_if(myVec.begin(), myVec.end(), [](auto &item) -> bool {
        auto res = item % 3 == 0;
        return res;
    });
    LOGSLOTH("count_per_3:%d", count_per_3);
    //--------------------------------------------------------------------------------
    // count_per_3:3
    //--------------------------------------------------------------------------------
}

void _p112_copy_if() {
    std::vector myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> myVec2;
    myVec2.resize(myVec.size());
    std::copy_if(myVec.begin(), myVec.end(), myVec2.begin(), [](auto &item) -> bool { return item % 2 == 0; });
    myVec2.shrink_to_fit();
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec2, "myVec2", "%d"));
    //--------------------------------------------------------------------------------
    // myVec2:10:00000282e6cc3620:[2, 4, 6, 8, 10, 0, 0, 0, 0, 0, ]
    //--------------------------------------------------------------------------------
}

void _p112_replace_if() {
    std::vector myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::replace_if(myVec.begin(), myVec.end(), [](auto &item) -> bool { return item % 2 == 0; }, -100);
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
    //--------------------------------------------------------------------------------
    // myVec:10:0000022b9d7d2630:[1, -100, 3, -10, 0, 5, -100, 7, -100, 9, -100, ]
    //--------------------------------------------------------------------------------
}

void _p113_replace_copy_if() {
    std::vector myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> myVec2;
    myVec2.resize(myVec.size());
    std::replace_copy_if(myVec.begin(), myVec.end(), myVec2.begin(), [](auto &item) -> bool { return item % 2 == 0; }, -100);
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec2, "myVec2", "%d"));
    //--------------------------------------------------------------------------------
    // _p113_replace_copy_if myVec2:10:0000015fa58d3620:[1, -100, 3, -100, 5, -100, 7, -100, 9, -100, ]
    //--------------------------------------------------------------------------------
}

void _p114_remove_if() {
    std::vector myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> myVec2;
    myVec2.resize(myVec.size());
    std::remove_copy_if(myVec.begin(), myVec.end(), myVec2.begin(), [](auto &item) { return item % 2 == 0; });
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec2, "myVec2", "%d"));
    //--------------------------------------------------------------------------------
    // myVec2:10:000002bc7a4c3620:[1, 3, 5, 7, 9, 0, 0, 0, 0, 0, ]
    //--------------------------------------------------------------------------------
}

void _p115_fill() {
    std::vector<int> myVec(10);
    std::fill(myVec.begin(), myVec.end(), 100);
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
    //--------------------------------------------------------------------------------
    // myVec:10:00000229554535c0:[100, 100, 100, 100, 100, 100, 100, 100, 100, 100, ]
    //--------------------------------------------------------------------------------
}

void _p119_reverse() {
    std::vector myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::reverse(myVec.begin(), myVec.end());
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
    //--------------------------------------------------------------------------------
    // myVec:10:00000229554535c0:[10, 9, 8, 7, 6, 5, 4, 3, 2, 1, ]
    //--------------------------------------------------------------------------------
}

void _p120_random_shuffle() {
    std::vector myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::random_shuffle(myVec.begin(), myVec.end());
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
    //--------------------------------------------------------------------------------
    // myVec:10:000001e85f0035c0:[9, 2, 10, 3, 1, 6, 8, 4, 5, 7, ]
    //--------------------------------------------------------------------------------
}

void _p122_unique() {
    std::vector myVec{1, 2, 3, 4, 5, 5, 6, 7, 7, 8, 8, 9, 10};
    std::vector<int> myVec2;
    myVec2.resize(myVec.size());
    std::unique_copy(myVec.begin(), myVec.end(), myVec2.begin());
    auto size = std::find(myVec2.begin(), myVec2.end(), 0) - myVec2.begin();
    myVec2.resize(size);
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec2, "myVec2", "%d"));
    //--------------------------------------------------------------------------------
    // myVec2:10:000001f7ffaa3640:[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, ]
    //--------------------------------------------------------------------------------
}

void _p126_sort() {
    std::vector myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::random_shuffle(myVec.begin(), myVec.end());
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
    //--------------------------------------------------------------------------------
    // myVec:10:000002b7dfbb35c0:[7, 5, 10, 8, 4, 1, 2, 9, 6, 3, ]
    //--------------------------------------------------------------------------------
    std::sort(myVec.begin(), myVec.end());
    LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
    //--------------------------------------------------------------------------------
    // myVec:10:000002b7dfbb35c0:[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, ]
    //--------------------------------------------------------------------------------
}

void _p142_random() {
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<> uniformDist(0, 20);
    std::normal_distribution<> normalDist(50, 8);
    for (int i = 0; i < 10; ++i) {
        LOGSLOTH("uniformDist:%d normalDist:%d", uniformDist(gen), normalDist(gen));
    }
    //--------------------------------------------------------------------------------
    // uniformDist:6 normalDist:-534649070
    // uniformDist:5 normalDist:-1814886017
    // uniformDist:19 normalDist:1658355070
    // uniformDist:3 normalDist:-871453507
    // uniformDist:3 normalDist:-1234805393
    // uniformDist:3 normalDist:827039816
    // uniformDist:6 normalDist:-1656674378
    // uniformDist:5 normalDist:-381255395
    // uniformDist:5 normalDist:-54442328
    // uniformDist:0 normalDist:1685725992
    //--------------------------------------------------------------------------------
}

void _p153_read_from_file() {
    auto strFilePath = "C:\\Users\\hhd20\\project\\mycpp\\main.cpp";
    auto vLine = MyUtil::readFromFile(strFilePath);
    std::for_each(vLine.begin(), vLine.begin() + 10, [](auto &item) {
        LOGSLOTH("item:%s", item.c_str());
    });

    //--------------------------------------------------------------------------------
    // item:#include <algorithm>
    // item:#include <array>
    // item:#include <chrono>
    // item:#include <iostream>
    // item:#include <map>
    // item:#include <memory>
    // item:#include <set>
    // item:#include <vector>
    // item:#include <random>
    // item:
    //--------------------------------------------------------------------------------
}

void _p159_to_string_stox() {
    auto res = std::to_string(123);
    auto res2 = std::to_string(1.23);
    auto res3 = std::to_string(123456789.123456789);
    auto res4 = std::stoi("123");
    auto res5 = std::stod("123.456");
    auto res6 = std::stol("123456789");
    auto res7 = std::stof("123.456");
}

int main() {
    _p10_namespace();
    _p11_using();
    _p12_using_alias();
    _p16_min_max();
    _p17_move();
    _p19_swap();
    _p22_pair();
    _p23_tuple();
    _p29_unique_ptr();
    _p32_shared_ptr();
    _p42_chrono_duration();
    _p48_container_new_delete();
    _p51_container_iter();
    _p52_container_compare();
    _p69_map();
    _p88_copy();
    _p100_lambda();
    _p105_foreach();
    _p107_count_if();
    _p112_copy_if();
    _p112_replace_if();
    _p113_replace_copy_if();
    _p114_remove_if();
    _p115_fill();
    _p119_reverse();
    _p120_random_shuffle();
    _p122_unique();
    _p126_sort();
    _p142_random();
    _p153_read_from_file();
    _p159_to_string_stox();
    return 0;
}



