#pragma once

#include <chrono>
#include <cstdarg>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#if defined(ANDROID) || defined(__ANDROID__)
#include <android/log.h>
#elif _WINDOWS
#pragma warning(disable : 4996)
#include <debugapi.h>
#endif

#define LOGSLOTH(szFormat, ...)             LogSlothLogger::PrintLog(__FILE__, __LINE__, __FUNCTION__, szFormat, ##__VA_ARGS__);
#define LOGSLOTH_ENTER()                    LogSlothLoggerScoped obj(__FILE__, __LINE__, __FUNCTION__);
#define LOGSLOTH_CALLER(szCallParam, ...)   LogSlothLogger::PrintLogCaller(__FILE__, __LINE__, __FUNCTION__, szCallParam, ##__VA_ARGS__);
#define LOGSLOTH_CALLEE(szCallParam, ...)   LogSlothLogger::PrintLogCallee(__FILE__, __LINE__, __FUNCTION__, szCallParam, ##__VA_ARGS__);
#define LOGSLOTH_VALUE(szValueName, valueValue)                         LogSlothLogger::PrintLogValue(__FILE__, __LINE__, __FUNCTION__, szValueName, valueValue);
#define LOGSLOTH_VALUE_PTR(szValueName, pValueValue)                    LogSlothLogger::PrintLogValueAsPtr(__FILE__, __LINE__, __FUNCTION__, szValueName, pValueValue);
#define LOGSLOTH_VALUE_HEX(szValueName, pValueValue, sizeValueValue)    LogSlothLogger::PrintLogValueAsHex(__FILE__, __LINE__, __FUNCTION__, szValueName, pValueValue, sizeValueValue);

class LogSlothLogger {
 public:
  static void init(bool showDetailLog = true) {
    _showDetailLog = showDetailLog;
  }

  static std::string PrintLogValue(std::string strFilePath,
                                   int nLineNum,
                                   std::string strFuncName,
                                   std::string strValueName,
                                   int iValueValue) {
    char szTmp[1024] = {};
    snprintf(szTmp, 1024, "%s:::%d", strValueName.c_str(), iValueValue);
    return LogSlothLogger::PrintLog(strFilePath, nLineNum, strFuncName, szTmp);
  }

  static std::string PrintLogValue(std::string strFilePath,
                                   int nLineNum,
                                   std::string strFuncName,
                                   std::string strValueName,
                                   long lValueValue) {
    char szTmp[1024] = {};
    snprintf(szTmp, 1024, "%s:::%ld", strValueName.c_str(), lValueValue);
    return LogSlothLogger::PrintLog(strFilePath, nLineNum, strFuncName, szTmp);
  }

  static std::string PrintLogValue(std::string strFilePath,
                                   int nLineNum,
                                   std::string strFuncName,
                                   std::string strValueName,
                                   float fValueValue) {
    char szTmp[1024] = {};
    snprintf(szTmp, 1024, "%s:::%f", strValueName.c_str(), fValueValue);
    return LogSlothLogger::PrintLog(strFilePath, nLineNum, strFuncName, szTmp);
  }

  static std::string PrintLogValue(std::string strFilePath,
                                   int nLineNum,
                                   std::string strFuncName,
                                   std::string strValueName,
                                   double dValueValue) {
    char szTmp[1024] = {};
    snprintf(szTmp, 1024, "%s:::%f", strValueName.c_str(), dValueValue);
    return LogSlothLogger::PrintLog(strFilePath, nLineNum, strFuncName, szTmp);
  }

  static std::string PrintLogValue(std::string strFilePath,
                                   int nLineNum,
                                   std::string strFuncName,
                                   std::string strValueName,
                                   std::string strValueValue) {
    char szTmp[1024] = {};
    snprintf(szTmp, 1024, "%s:::%s", strValueName.c_str(),
             strValueValue.c_str());
    return LogSlothLogger::PrintLog(strFilePath, nLineNum, strFuncName, szTmp);
  }

  static std::string PrintLogValue(std::string strFilePath,
                                   int nLineNum,
                                   std::string strFuncName,
                                   std::string strValueName,
                                   const char *szValueValue) {
    char szTmp[1024] = {};
    snprintf(szTmp, 1024, "%s:::%s", strValueName.c_str(), szValueValue);
    return LogSlothLogger::PrintLog(strFilePath, nLineNum, strFuncName, szTmp);
  }

  static std::string PrintLogValueAsPtr(std::string strFilePath,
                                        int nLineNum,
                                        std::string strFuncName,
                                        std::string strValueName,
                                        void *pValueValue) {
    char szTmp[1024] = {};
    snprintf(szTmp, 1024, "%s:::%p", strValueName.c_str(), pValueValue);
    return LogSlothLogger::PrintLog(strFilePath, nLineNum, strFuncName, szTmp);
  }

  static std::string PrintLogValueAsHex(std::string strFilePath,
                                        int nLineNum,
                                        std::string strFuncName,
                                        std::string strValueName,
                                        char *pValueValue, int sizeValueValue) {
    std::string strLog;
    std::string strValueValue;
    char szHexWord[1024] = {};

    for (auto i = 0; i < sizeValueValue; i++) {
      snprintf(szHexWord, 1024, "%02x", *(pValueValue + i));
      strValueValue += szHexWord;
    }

    char szTmp[1024] = {};
    snprintf(szTmp, 1024, "%s:::(%d)%s", strValueName.c_str(), sizeValueValue,
             strValueValue.c_str());
    return LogSlothLogger::PrintLog(strFilePath, nLineNum, strFuncName, szTmp);
  }

  static std::string PrintLogCaller(std::string strFilePath,
                                    int nLineNum,
                                    std::string strFuncName,
                                    std::string strCallParam,
                                    ...) {
    char szCallParam[1024] = {};
    va_list args;
    va_start(args, strCallParam);
    vsprintf(szCallParam, strCallParam.c_str(), args);
    va_end(args);

    char szTmp[1024] = {};
    snprintf(szTmp, 1024, "→→→%s→→→", szCallParam);
    return LogSlothLogger::PrintLog(strFilePath, nLineNum, strFuncName, szTmp);
  }

  static std::string PrintLogCallee(std::string strFilePath,
                                    int nLineNum,
                                    std::string strFuncName,
                                    std::string strCallParam,
                                    ...) {
    char szCallParam[1024] = {};
    va_list args;
    va_start(args, strCallParam);
    vsprintf(szCallParam, strCallParam.c_str(), args);
    va_end(args);

    char szTmp[1024] = {};
    snprintf(szTmp, 1024, "←←←%s←←←", szCallParam);
    return LogSlothLogger::PrintLog(strFilePath, nLineNum, strFuncName, szTmp);
  }

  static std::string PrintLog(std::string strFilePath,
                              int nLineNum,
                              std::string strFuncName,
                              std::string strFormat,
                              ...) {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lg(mtx);

    auto curTime = std::time(nullptr);
    static char szCurTime[1024] = {};
    std::strftime(szCurTime, sizeof(szCurTime), "%m-%d %H:%M:%S", std::localtime(&curTime));
    static char szLog[1024] = {};
    va_list args;
    va_start(args, strFormat);
    vsprintf(szLog, strFormat.c_str(), args);
    va_end(args);
    static char szPrettyLog[1024] = {};
    std::string strFileName;

    if (not strFilePath.empty()) {
      auto iStart = strFilePath.find_last_of('/');

      if (iStart == std::string::npos) {
        iStart = strFilePath.find_last_of('\\');
      }

      strFileName = strFilePath.substr(iStart + 1, strFilePath.size() - iStart - 1);
    }

#if defined(ANDROID) || defined(__ANDROID__)
    snprintf(szPrettyLog, 1024, "%s:%d:%s %s", strFileName.c_str(), nLineNum,
             strFuncName.c_str(), szLog);

    __android_log_write(ANDROID_LOG_DEBUG, "LOGSLOTH", szPrettyLog);
#else
    auto now = std::chrono::system_clock::now();
    auto ms = (int) (std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) %
        1000)
        .count();
    auto pid = getpid();
    auto tid = (int) std::hash<std::thread::id>{}(std::this_thread::get_id());
    if (_showDetailLog) {
      snprintf(szPrettyLog, 1024, "%s.%03d %d %d D LOGSLOTH: %s:%d:%s %s \n", szCurTime, ms, pid, tid, strFileName.c_str(), nLineNum, strFuncName.c_str(), szLog);
    } else {
      snprintf(szPrettyLog, 1024, "%s \n", szLog);
    }

    std::cout << szPrettyLog;
#endif

#if _WINDOWS
    ::OutputDebugStringA(szPrettyLog);
#endif
    return std::string(szPrettyLog);
  }

 private:
  static bool _showDetailLog;
};

bool LogSlothLogger::_showDetailLog = true;

class LogSlothLoggerScoped {
 public:
  LogSlothLoggerScoped(std::string strFilePath,
                       int nLineNum,
                       std::string strFuncName) {
    LogSlothLogger::PrintLog(strFilePath, nLineNum, strFuncName, "↘↘↘");
    _strFilePath = strFilePath;
    _nLineNum = nLineNum;
    _strFuncName = strFuncName;
  }

  ~LogSlothLoggerScoped() {
    LogSlothLogger::PrintLog(_strFilePath, _nLineNum, _strFuncName, "↗↗↗");
  }

 private:
  std::string _strFilePath;
  int _nLineNum;
  std::string _strFuncName;
};