#pragma once
#include <functional>
#include <winrt/Windows.UI.Notifications.h>
#include <winrt/Windows.Foundation.Collections.h>
#define TOAST_ACTIVATED_LAUNCH_ARG "-ToastActivated"

namespace notification_rt {

class DesktopNotificationManagerCompat;
class DesktopNotificationActivatedEventArgsCompat;
class DesktopNotificationHistoryCompat;

class DesktopNotificationManagerCompat {
 public:
  static void Register(std::wstring aumid, std::wstring displayName, std::wstring iconPath, std::wstring clsid);
  static void OnActivated(std::function<void(DesktopNotificationActivatedEventArgsCompat)> callback);

  static winrt::Windows::UI::Notifications::ToastNotifier CreateToastNotifier();
  static DesktopNotificationHistoryCompat History();

  static void Uninstall();
};

class DesktopNotificationActivatedEventArgsCompat {
  std::wstring _argument;
  winrt::Windows::Foundation::Collections::StringMap _userInput;

 public:
  std::wstring Argument() { return _argument; }
  winrt::Windows::Foundation::Collections::StringMap UserInput() { return _userInput; }

  DesktopNotificationActivatedEventArgsCompat(std::wstring argument,
                                              winrt::Windows::Foundation::Collections::StringMap userInput) {
    _argument = argument;
    _userInput = userInput;
  }
};

class DesktopNotificationHistoryCompat {
  std::wstring _win32Aumid;
  winrt::Windows::UI::Notifications::ToastNotificationHistory _history = nullptr;

 public:
  void Clear();
  winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::UI::Notifications::ToastNotification> GetHistory();
  void Remove(std::wstring tag);
  void Remove(std::wstring tag, std::wstring group);
  void RemoveGroup(std::wstring group);

  DesktopNotificationHistoryCompat(std::wstring win32Aumid) {
    _win32Aumid = win32Aumid;
    _history = winrt::Windows::UI::Notifications::ToastNotificationManager::History();
  }
};

} // namespace notification_rt

