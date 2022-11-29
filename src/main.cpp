#include "logsloth.h"
#include "myutil.h"
#include "my_int.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <condition_variable>
#include <filesystem>
#include <future>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <random>
#include <set>
#include <vector>

void _p10_namespace() {
  auto tNow = std::chrono::system_clock::now();
  LOGSLOTH("tNow:%lu", tNow.time_since_epoch());
  //--------------------------------------------------------------------------------
  // tNow:3222359556
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p11_using() {
  using namespace std;
  cout << "hello" << endl;
  //--------------------------------------------------------------------------------
  // hello
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////


void _p12_using_alias() {
  using sysClock = std::chrono::system_clock;
  auto now = sysClock::now();
  LOGSLOTH("now:%lu", now.time_since_epoch());
  //--------------------------------------------------------------------------------
  // now:1540286116
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////


void _p16_min_max() {
  std::cout << "std::min:" << std::min(2011, 2014) << std::endl;
  std::cout << "std::min array:" << std::min({1, 2, 3, 4, 5}) << std::endl;
  std::cout << "std::min lambda:" << std::min({1, 2, -3, -4, -5}, [](int a, int b) { return std::abs(a) < std::abs(b); }) << std::endl;
  auto minMaxRes = std::minmax({1, 2, -3, -4, -5});
  std::cout << "std::minmax:" << minMaxRes.first << ":" << minMaxRes.second << std::endl;
  //--------------------------------------------------------------------------------
  // std::min:2011
  // std::min array:1
  // std::min lambda:1
  // std::minmax:-5:2
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p17_move() {
  auto myBigVec = std::vector<int>(10000000, 2011);
  LOGSLOTH("myBigVec:%lu:%p", myBigVec.size(), myBigVec.data());
  //--------------------------------------------------------------------------------
  // myBigVec:10000000:0000023acbe89040
  //--------------------------------------------------------------------------------

  auto myVec = myBigVec;
  LOGSLOTH("myBigVec:%lu:%p", myBigVec.size(), myBigVec.data());
  LOGSLOTH("myVec:%lu:%p", myVec.size(), myVec.data());
  //--------------------------------------------------------------------------------
  // myBigVec:10000000:0000023acbe89040
  // myVec:10000000:0000023ace4be040
  //--------------------------------------------------------------------------------

  auto myVec2 = std::move(myBigVec);
  LOGSLOTH("myBigVec:%lu:%p", myBigVec.size(), myBigVec.data());
  LOGSLOTH("myVec:%lu:%p", myVec.size(), myVec.data());
  LOGSLOTH("myVec2:%lu:%p", myVec2.size(), myVec2.data());
  //--------------------------------------------------------------------------------
  // myBigVec:0:0000000000000000
  // myVec:10000000:0000023ace4be040
  // myVec2:10000000:0000023acbe89040
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p19_swap() {
  auto a = 1;
  auto b = 2;
  LOGSLOTH("a:%d b:%d", a, b);
  std::swap(a, b);
  LOGSLOTH("a:%d b:%d", a, b);
  //--------------------------------------------------------------------------------
  // a:1 b:2
  // a:2 b:1
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p22_pair() {
  auto myPair = std::make_pair("str", 3.14);
  LOGSLOTH("myPair:%s:%f", myPair.first, myPair.second);
  //--------------------------------------------------------------------------------
  // myTuple:str:3.140000:hhd
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p23_tuple() {
  auto myTuple = std::make_tuple("str", 3.14, "hhd");
  LOGSLOTH("myTuple:%s:%f:%s", std::get<0>(myTuple), std::get<1>(myTuple), std::get<2>(myTuple));
  //--------------------------------------------------------------------------------
  // myTuple:str:3.140000:hhd
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p29_unique_ptr() {

  auto up0 = std::make_unique<MyInt>(0);

  {
    auto up1 = std::make_unique<MyInt>(1);
  }

  auto up2 = std::make_unique<MyInt>(2);
  auto up3 = std::move(up2);
  //--------------------------------------------------------------------------------
  //MyInt MyInt() _i:0
  //MyInt MyInt() _i:1
  //~MyInt ~MyInt() _i:1
  //MyInt MyInt() _i:2
  //~MyInt ~MyInt() _i:2
  //~MyInt ~MyInt() _i:0
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p32_shared_ptr() {
  auto sp0 = std::make_shared<MyInt>(0);
  //--------------------------------------------------------------------------------
  // MyInt MyInt() _i:0
  //--------------------------------------------------------------------------------

  {
    auto sp1 = std::make_shared<MyInt>(1);
    //--------------------------------------------------------------------------------
    // MyInt MyInt() _i:1
    // ~MyInt ~MyInt() _i:1
    //--------------------------------------------------------------------------------
  }

  auto sp2 = std::make_shared<MyInt>(2);
  //--------------------------------------------------------------------------------
  // MyInt MyInt() _i:2
  //--------------------------------------------------------------------------------

  std::shared_ptr<MyInt[]> spArray{new MyInt[3]};
  //--------------------------------------------------------------------------------
  // MyInt MyInt()
  // MyInt MyInt()
  // MyInt MyInt()
  //--------------------------------------------------------------------------------

  auto sp3 = sp2;
  LOGSLOTH("sp2:%d:%ld sp3:%d:%ld", sp2->_i, sp2.use_count(), sp3->_i, sp3.use_count());
  //--------------------------------------------------------------------------------
  // TestBody sp2:2:2 sp3:2:2
  //--------------------------------------------------------------------------------

  auto sp4 = sp2;
  LOGSLOTH("sp2:%d:%ld sp3:%d:%ld", sp2->_i, sp2.use_count(), sp3->_i, sp3.use_count());
  //--------------------------------------------------------------------------------
  // TestBody sp2:2:3 sp3:2:3
  //--------------------------------------------------------------------------------

  //--------------------------------------------------------------------------------
  // ~MyInt ~MyInt() _i:-1163005939
  // ~MyInt ~MyInt() _i:-1163005939
  // ~MyInt ~MyInt() _i:-1163005939
  // ~MyInt ~MyInt() _i:2
  // ~MyInt ~MyInt() _i:0
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p42_chrono_duration() {
  std::vector<int> myBigVec(10000000, 2011);
  std::vector<int> myEmptyVec;

  auto tStart = std::chrono::high_resolution_clock::now();
  myEmptyVec = myBigVec;
  auto tEnd = std::chrono::high_resolution_clock::now();
  auto ts = tEnd - tStart;
  LOGSLOTH("ts:%lld(ns)", ts.count());
  //--------------------------------------------------------------------------------
  // ts:11237000(ns)
  //--------------------------------------------------------------------------------

  auto tsMs = std::chrono::duration_cast<std::chrono::milliseconds>(ts).count();
  LOGSLOTH("tsMs:%lld(ms)", tsMs);
  //--------------------------------------------------------------------------------
  // tsMs:11(ms)
  //--------------------------------------------------------------------------------

  std::chrono::seconds ts100Sec(100);
  std::chrono::minutes ts5Min(5);
  std::chrono::milliseconds ts30Ms(30);
  auto tsSum = ts100Sec + ts5Min + ts30Ms;
  LOGSLOTH("tsSum:%ld(min)", std::chrono::duration_cast<std::chrono::minutes>(tsSum).count());
  LOGSLOTH("tsSum:%lld(sec)", std::chrono::duration_cast<std::chrono::seconds>(tsSum).count());
  LOGSLOTH("tsSum:%lld(ms)", std::chrono::duration_cast<std::chrono::milliseconds>(tsSum).count());
  //--------------------------------------------------------------------------------
  // tsSum:6(min)
  // tsSum:400(sec)
  // tsSum:400030(ms)
  //--------------------------------------------------------------------------------

  auto sysClockStart = std::chrono::system_clock::now();
  myEmptyVec = myBigVec;
  auto sysClockEnd = std::chrono::system_clock::now();
  auto tsSysClock = sysClockEnd - sysClockStart;
  LOGSLOTH("tsSysClock:%lld(ms)", std::chrono::duration_cast<std::chrono::milliseconds>(tsSysClock).count());
  //--------------------------------------------------------------------------------
  // tsSysClock:15(ms)
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p48_container_new_delete() {
  //기본
  std::vector<int> vec1;
  LOGSLOTH("vec1:%lu:%p", vec1.size(), vec1.data());
  //--------------------------------------------------------------------------------
  // vec1:0:0000000000000000
  //--------------------------------------------------------------------------------

  //순차열
  std::vector<int> vec2{1, 2, 3, 4, 5};
  std::vector<int> vec2_1 = {1, 2, 3, 4, 5};
  LOGSLOTH("vec2:%lu:%p", vec2.size(), vec2.data());
  LOGSLOTH("vec2_1:%lu:%p", vec2_1.size(), vec2_1.data());
  //--------------------------------------------------------------------------------
  // vec2:5:00000212ebaf1b40
  // vec2_1:5:00000212ebaf1d60
  //--------------------------------------------------------------------------------

  //복사
  auto vec3 = vec2;
  LOGSLOTH("vec3:%lu:%p", vec3.size(), vec3.data());
  //--------------------------------------------------------------------------------
  // vec3:5:00000212eb9734e0
  //--------------------------------------------------------------------------------

  //이동
  auto vec4 = std::move(vec3);
  LOGSLOTH("vec3:%lu:%p", vec3.size(), vec3.data());
  LOGSLOTH("vec4:%lu:%p", vec4.size(), vec4.data());
  //--------------------------------------------------------------------------------
  // vec3:0:0000000000000000
  // vec4:5:00000212eb9734e0
  //--------------------------------------------------------------------------------

  //요소삭제
  vec4.clear();
  LOGSLOTH("vec4:%lu:%p", vec4.size(), vec4.data());
  //--------------------------------------------------------------------------------
  // vec4:0:00000212eb9734e0
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p51_container_iter() {
  std::vector<int> myVec;
  myVec.push_back(1);
  myVec.emplace_back(3);
  myVec.push_back(5);
  myVec.emplace_back(7);
  myVec.insert(myVec.begin(), 9);
  LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
  //--------------------------------------------------------------------------------
  // myVec:5:000001e7b9871d60:[9, 1, 3, 5, 7, ]
  //--------------------------------------------------------------------------------

  myVec.pop_back();
  LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
  //--------------------------------------------------------------------------------
  // myVec:4:000001e7b9871b40:[9, 1, 3, 5, ]
  //--------------------------------------------------------------------------------

  myVec.insert(myVec.begin() + 2, 100);
  LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
  //--------------------------------------------------------------------------------
  // myVec:5:000001e7b9871d60:[9, 1, 100, 3, 5, ]
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p52_container_compare() {
  std::vector<int> v1{1, 2, 3, 4};
  std::vector<int> v2{1, 2, 3, 4};
  LOGSLOTH("v1 == v2:%d", v1 == v2);
  //--------------------------------------------------------------------------------
  // v1 == v2:1
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p69_map() {
  std::map<std::string, int> m{
      {"a", 1},
      {"b", 2},
      {"c", 3},
  };

  for (auto item : m) {
    LOGSLOTH("MAP_ITER %s:%d", item.first.c_str(), item.second);
  }
  //--------------------------------------------------------------------------------
  // MAP_ITER a:1
  // MAP_ITER b:2
  // MAP_ITER c:3
  //--------------------------------------------------------------------------------

  auto a_exist = m.find("a") != m.end();
  LOGSLOTH("a_exist:%d", a_exist);
  //--------------------------------------------------------------------------------
  // a_exist:1
  //--------------------------------------------------------------------------------

  auto d_exist = m.find("d") != m.end();
  LOGSLOTH("d_exist:%d", d_exist);
  //--------------------------------------------------------------------------------
  // d_exist:0
  //--------------------------------------------------------------------------------

  m.erase("b");
  auto b_exist = m.find("b") != m.end();
  LOGSLOTH("b_exist:%d", b_exist);
  //--------------------------------------------------------------------------------
  // b_exist:0
  //--------------------------------------------------------------------------------

  m["d"] = 4;

  std::map<std::string, int> m2{
      {"h", 10},
      {"i", 20},
      {"j", 30},
  };

  std::map<std::string, int> m3;
  m3.insert(m.begin(), m.end());
  m3.insert(m2.begin(), m2.end());

  for (auto item : m3) {
    LOGSLOTH("MAP_ITER %s:%d", item.first.c_str(), item.second);
  }
  //--------------------------------------------------------------------------------
  // MAP_ITER a:1
  // MAP_ITER c:3
  // MAP_ITER d:4
  // MAP_ITER h:10
  // MAP_ITER i:20
  // MAP_ITER j:30
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p88_copy() {
  std::vector v{1, 2, 3};
  std::vector<int> v2;
  v2.resize(v.size());
  std::copy(v.begin(), v.end(), v2.begin());
  auto infoStr = MyUtil::getVectorInfoStr(v2, "v2", "%d");
  LOGSLOTH(infoStr);
  //--------------------------------------------------------------------------------
  // v2:3:0000021124321d60:[1, 2, 3, ]
  //--------------------------------------------------------------------------------

  std::vector<int> v3;
  v3.resize(v.size());
  std::copy(v.rbegin(), v.rend(), v3.begin());
  auto infoStr3 = MyUtil::getVectorInfoStr(v3, "v3", "%d");
  LOGSLOTH(infoStr3);
  //--------------------------------------------------------------------------------
  // v3:3:0000021124321da0:[3, 2, 1, ]
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p100_lambda() {
  std::vector<int> myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::for_each(myVec.begin(), myVec.end(), [](int &i) {
    auto res = i * i;
    i = res;
  });

  LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
  //--------------------------------------------------------------------------------
  // myVec:10:0000029455dfa1d0:[1, 4, 9, 16, 25, 36, 49, 64, 81, 100, ]
  //--------------------------------------------------------------------------------
}


////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

void _p112_copy_if() {
  std::vector myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> myVec2;
  myVec2.resize(myVec.size());
  std::copy_if(myVec.begin(), myVec.end(), myVec2.begin(), [](auto &item) -> bool { return item % 2 == 0; });
  auto newSize = std::find(myVec2.begin(), myVec2.end(), 0) - myVec2.begin();
  myVec2.resize(newSize);
  LOGSLOTH(MyUtil::getVectorInfoStr(myVec2, "myVec2", "%d"));
  //--------------------------------------------------------------------------------
  // myVec2:5:0000020696c01dc0:[2, 4, 6, 8, 10, ]
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p112_replace_if() {
  std::vector myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::replace_if(myVec.begin(), myVec.end(), [](auto &item) -> bool { return item % 2 == 0; }, -100);
  LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
  //--------------------------------------------------------------------------------
  // myVec:10:0000022b9d7d2630:[1, -100, 3, -10, 0, 5, -100, 7, -100, 9, -100, ]
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

void _p114_remove_if() {
  std::vector myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> myVec2;
  myVec2.resize(myVec.size());
  std::remove_copy_if(myVec.begin(), myVec.end(), myVec2.begin(), [](auto &item) { return item % 2 == 0; });
  auto newSize = std::find(myVec2.begin(), myVec2.end(), 0) - myVec2.begin();
  myVec2.resize(newSize);
  LOGSLOTH(MyUtil::getVectorInfoStr(myVec2, "myVec2", "%d"));
  //--------------------------------------------------------------------------------
  // myVec2:5:00000168b43c1dc0:[1, 3, 5, 7, 9, ]
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p115_fill() {
  std::vector<int> myVec(10);
  std::fill(myVec.begin(), myVec.end(), 100);
  LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
  //--------------------------------------------------------------------------------
  // myVec:10:00000229554535c0:[100, 100, 100, 100, 100, 100, 100, 100, 100, 100, ]
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p119_reverse() {
  std::vector myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::reverse(myVec.begin(), myVec.end());
  LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
  //--------------------------------------------------------------------------------
  // myVec:10:00000229554535c0:[10, 9, 8, 7, 6, 5, 4, 3, 2, 1, ]
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p120_random_shuffle() {
  std::vector myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::random_shuffle(myVec.begin(), myVec.end());
  LOGSLOTH(MyUtil::getVectorInfoStr(myVec, "myVec", "%d"));
  //--------------------------------------------------------------------------------
  // myVec:10:000001e85f0035c0:[9, 2, 10, 3, 1, 6, 8, 4, 5, 7, ]
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

void _p142_random() {
  std::random_device seed;
  std::mt19937 gen(seed());
  std::uniform_int_distribution<> uniformDist(0, 20);
  std::normal_distribution<> normalDist(50, 8);
  for (int i = 0; i < 10; ++i) {
    auto u = uniformDist(gen);
    auto n = normalDist(gen);
    LOGSLOTH("uniformDist:%d normalDist:%.2f", u, n);
  }
  //--------------------------------------------------------------------------------
  //  uniformDist:7 normalDist:46.60
  //  uniformDist:16 normalDist:54.78
  //  uniformDist:5 normalDist:47.45
  //  uniformDist:8 normalDist:45.69
  //  uniformDist:17 normalDist:61.53
  //  uniformDist:11 normalDist:54.39
  //  uniformDist:19 normalDist:53.72
  //  uniformDist:9 normalDist:49.54
  //  uniformDist:17 normalDist:40.89
  //  uniformDist:13 normalDist:50.09
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p153_read_from_file() {
  auto strFilePath = "C:\\Users\\hhd20\\project\\mycpp\\src\\main.cpp";
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

////////////////////////////////////////////////////////////////////////////////

void _p159_to_string_stox() {
  auto res = std::to_string(123);
  auto res2 = std::to_string(1.23);
  auto res3 = std::to_string(123456789.123456789);
  auto res4 = std::stoi("123");
  auto res5 = std::stod("123.456");
  auto res6 = std::stol("123456789");
  auto res7 = std::stof("123.456");
  //--------------------------------------------------------------------------------
  // res = {std::string} "123"
  // res2 = {std::string} "1.230000"
  // res3 = {std::string} "123456789.123457"
  // res4 = {int} 123
  // res5 = {double} 123.456
  // res6 = {long} 123456789
  // res7 = {float} 123.456001
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p191_file_rw() {
  std::ofstream of("test.txt");
  std::string szTmp;
  szTmp = "hello world\n";
  of.write(szTmp.c_str(), szTmp.size());
  auto curP = of.tellp();
  //--------------------------------------------------------------------------------
  // curP = {std::fpos<int>}
  // _M_off = {std::streamoff} 12
  // _M_state = {int} 0
  //--------------------------------------------------------------------------------

  of.seekp(100);
  szTmp = "100\n";
  of.write(szTmp.c_str(), szTmp.size());
  of.seekp(200);
  szTmp = "200\n";
  of.write(szTmp.c_str(), szTmp.size());

  std::vector<unsigned char> buf = {0x50, 0x51, 0x52, 0x53};
  of.write(reinterpret_cast<const char *>(buf.data()), buf.size());

  of.close();
  //--------------------------------------------------------------------------------
  // hello world
  //                                                                                       100
  //                                                                                               200
  // PQRS
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _funcCopy(MyInt obj) {
  LOGSLOTH("FUNC_COPY obj:%d", obj._i);
}

void _funcRef(const MyInt &obj) {
  LOGSLOTH("FUNC_REF obj:%d", obj._i);
}

void _p201_thread_pass_param() {
  MyInt param(123);
  //--------------------------------------------------------------------------------
  // MyInt() _i:123
  //--------------------------------------------------------------------------------

  std::thread tCopy0([=] { LOGSLOTH("T_COPY_0 %d", param._i) });
  std::thread tCopy1(_funcCopy, param);
  //--------------------------------------------------------------------------------
  // ~MyInt() _i:123
  // T_COPY_0 123
  //--------------------------------------------------------------------------------

  tCopy0.join();
  tCopy1.join();
  //--------------------------------------------------------------------------------
  // ~MyInt() _i:123
  // FUNC_COPY obj:123
  // ~MyInt() _i:123
  // ~MyInt() _i:123
  //--------------------------------------------------------------------------------

  std::thread tRef0([&] { LOGSLOTH("T_REF_0 %d", param._i) });
  std::thread tRef1([&] { _funcRef(param); });
  //--------------------------------------------------------------------------------
  // T_REF_0 123
  // FUNC_REF obj:123
  //--------------------------------------------------------------------------------

  tRef0.join();
  tRef1.join();
  //--------------------------------------------------------------------------------
  // ~MyInt() _i:123
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p206_thread_mutex() {
  auto num = 0;
  std::mutex mtx;

  std::thread t0([&] {
    while (true) {
      mtx.lock();
      LOGSLOTH("T0_START num:%d", num);
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      num++;
      LOGSLOTH("T0_FIN num:%d", num);
      mtx.unlock();
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  std::thread t1([&] {
    while (true) {
      mtx.lock();
      LOGSLOTH("T1_START num:%d", num);
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      num++;
      LOGSLOTH("T1_FIN num:%d", num);
      mtx.unlock();
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  std::thread t2([&] {
    while (true) {
      mtx.lock();
      LOGSLOTH("T2_START num:%d", num);
      std::this_thread::sleep_for(std::chrono::milliseconds(3000));
      num++;
      LOGSLOTH("T2_FIN num:%d", num);
      mtx.unlock();
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  //--------------------------------------------------------------------------------
  // T0_START num:0
  // T0_FIN num:1
  // T1_START num:1
  // T1_FIN num:2
  // T2_START num:2
  // T2_FIN num:3
  // T0_START num:3
  // T0_FIN num:4
  // T1_START num:4
  // T1_FIN num:5
  // T2_START num:5
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p209_thread_lock_guard() {
  auto num = 0;
  std::mutex mtx;

  std::thread t0([&] {
    while (true) {
      {
        std::lock_guard lg(mtx);
        LOGSLOTH("T0_START num:%d", num);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        num++;
        LOGSLOTH("T0_FIN num:%d", num);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  std::thread t1([&] {
    while (true) {
      {
        std::lock_guard lg(mtx);
        LOGSLOTH("T1_START num:%d", num);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        num++;
        LOGSLOTH("T1_FIN num:%d", num);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  std::thread t2([&] {
    while (true) {
      {
        std::lock_guard lg(mtx);
        LOGSLOTH("T2_START num:%d", num);
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        num++;
        LOGSLOTH("T2_FIN num:%d", num);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(10000));

  //--------------------------------------------------------------------------------
  // T0_START num:0
  // T0_FIN num:1
  // T1_START num:1
  // T1_FIN num:2
  // T2_START num:2
  // T2_FIN num:3
  // T0_START num:3
  // T0_FIN num:4
  // T1_START num:4
  // T1_FIN num:5
  // T2_START num:5
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p216_cond_var() {
  std::mutex mtx;
  std::condition_variable cv;

  std::thread t0([&] {
    LOGSLOTH("T0_SLEEP_START");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    LOGSLOTH("T0_SLEEP_FIN");
    LOGSLOTH("T0_NOTIFY");
    cv.notify_all();
    LOGSLOTH("T0_FIN");
  });

  std::thread t1([&] {
    LOGSLOTH("T1_LOCK_START");
    auto lock = std::unique_lock(mtx);
    LOGSLOTH("T1_WAIT");
    cv.wait(lock);
    LOGSLOTH("T1_WAIT_FIN");
    LOGSLOTH("T1_FIN");
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  //--------------------------------------------------------------------------------
  // T0_SLEEP_START
  // T1_LOCK_START
  // T1_WAIT
  // T0_SLEEP_FIN
  // T0_NOTIFY
  // T0_FIN
  // T1_WAIT_FIN
  // T1_FIN
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p220_async_get_deferred() {
  auto tsStart = std::chrono::system_clock::now();
  auto jobDef = std::async(std::launch::deferred, [] { return std::chrono::system_clock::now(); });
  auto jobAsync = std::async(std::launch::async, [] { return std::chrono::system_clock::now(); });
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  auto defDuration = jobDef.get() - tsStart;
  auto asyncDuration = jobAsync.get() - tsStart;
  LOGSLOTH("defDuration:%.3f", std::chrono::duration<double>(defDuration).count());
  LOGSLOTH("asyncDuration:%.3f", std::chrono::duration<double>(asyncDuration).count());
  //--------------------------------------------------------------------------------
  // defDuration:1.008
  // asyncDuration:0.001
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _product(std::promise<int> &&intPromise, int a, int b) {
  intPromise.set_value(a * b);
}

void _p224_future_promise() {
  std::promise<int> intPromise;
  auto intFuture = intPromise.get_future();
  std::thread t(_product, std::move(intPromise), 123, 456);
  t.detach();
  auto res = intFuture.get();
  LOGSLOTH("res:%d", res);
  //--------------------------------------------------------------------------------
  // res:56088
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

std::optional<int> _get_str_len(std::string&& str) {
  if (str.size() == 0) {
    return std::nullopt;
  } else {
    return str.size();
  }
}

void _p230_optional() {
  auto res = _get_str_len("hello");
  LOGSLOTH("res:%d:%d", res.has_value(), res);
  //--------------------------------------------------------------------------------
  // res:1:5
  //--------------------------------------------------------------------------------

  auto res2 = _get_str_len("");
  LOGSLOTH("res2:%d:%d", res2.has_value(), res2);
  //--------------------------------------------------------------------------------
  // res2:0:240569052
  //--------------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

void _p237_file_system() {
  std::filesystem::create_directories("a/b/c");
  std::ofstream newFile("a/b/c/d.txt");
  auto res = std::filesystem::exists("a/b/c/d.txt");
  //--------------------------------------------------------------------------------
  // true
  //--------------------------------------------------------------------------------

  for (auto&& item : std::filesystem::directory_iterator("a/b/c")) {
    LOGSLOTH("item:%s", item.path().c_str());
  }
  newFile.close();
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
  LogSlothLogger::init(false);
//  _p10_namespace();
//  _p11_using();
//  _p12_using_alias();
//  _p16_min_max();
//  _p17_move();
//  _p19_swap();
//  _p22_pair();
//  _p23_tuple();
//  _p29_unique_ptr();
//  _p32_shared_ptr();
//  _p42_chrono_duration();
//  _p48_container_new_delete();
//  _p51_container_iter();
//  _p52_container_compare();
//  _p69_map();
//  _p88_copy();
//  _p100_lambda();
//  _p107_count_if();
//  _p112_copy_if();
//  _p112_replace_if();
//  _p113_replace_copy_if();
//  _p114_remove_if();
//  _p115_fill();
//  _p119_reverse();
//  _p120_random_shuffle();
//  _p122_unique();
//  _p126_sort();
//  _p142_random();
//  _p153_read_from_file();
//  _p159_to_string_stox();
//  _p191_file_rw();
//  _p201_thread_pass_param();
//  _p206_thread_mutex();
//  _p209_thread_lock_guard();
//  _p216_cond_var();
//  _p220_async_get_deferred();
//  _p224_future_promise();
//  _p230_optional();
  _p237_file_system();
}