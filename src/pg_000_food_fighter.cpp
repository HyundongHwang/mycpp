#include <string>
#include <vector>
#include <algorithm>

#include "logsloth.h"
#include "gtest/gtest.h"

//https://school.programmers.co.kr/learn/courses/30/lessons/134240
std::string solution(std::vector<int> food) {
  if (food.empty())
    return "";

  std::string answer = "";
  struct _NameCount {
    int name;
    int count;
  };
  std::vector<_NameCount> vNameCount;
  for (int i = 1; i < food.size(); i++) {
    vNameCount.push_back(_NameCount{i, food[i]});
  }
  std::reverse(vNameCount.begin(), vNameCount.end());
  answer += "0";
  for (auto nc : vNameCount) {
    for (int _ = 0; _ < int(nc.count / 2); _++) {
      answer = std::to_string(nc.name) + answer;
      answer = answer + std::to_string(nc.name);
    }
  }
  return answer;
}

TEST(solution, solution) {
  std::vector food{1, 3, 4, 6};
  auto res = solution(std::move(food));
  EXPECT_TRUE(res == "1223330333221");
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  auto res = RUN_ALL_TESTS();
}