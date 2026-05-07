#include <windows.h>
#include <vector>
#include <string>

using namespace std;

// ==================== ОБЪЯВЛЕНИЯ ФУНКЦИЙ ====================
void ShowWindowByClass(LPCWSTR className, WNDPROC proc, LPCWSTR title, int w, int h);
void ShowClientWindow();
void ShowOperatorWindow();
void ShowAdminWindow();
void ShowRegWindow();

// ==================== ДАННЫЕ ДЛЯ АДМИНИСТРАТОРА ====================
vector<wstring> users = { L"1 | Иванов | Клиент", L"2 | Петров | Оператор", L"3 | Сидоров | Админ" };
vector<wstring> tickets = { L"101 | Не работает сайт | В работе", L"102 | Нет письма | Закрыта" };
vector<wstring> articles = { L"1 | Ошибка 500", L"2 | Нет письма" };

int mode = 1;
HWND hList, hEdit;

void RefreshList(HWND list) {
    SendMessage(list, LB_RESETCONTENT, 0, 0);
    if (mode == 1)
        for (size_t i = 0; i < users.size(); i++)
            SendMessage(list, LB_ADDSTRING, 0, (LPARAM)users[i].c_str());
    else if (mode == 2)
        for (size_t i = 0; i < tickets.size(); i++)
            SendMessage(list, LB_ADDSTRING, 0, (LPARAM)tickets[i].c_str());
    else if (mode == 3)
        for (size_t i = 0; i < articles.size(); i++)
            SendMessage(list, LB_ADDSTRING, 0, (LPARAM)articles[i].c_str());
}

// ==================== АВТОРИЗАЦИЯ ====================
HWND hAuthLogin, hAuthPass;

LRESULT CALLBACK AuthProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"STATIC", L"Логин:", WS_VISIBLE | WS_CHILD, 20, 20, 60, 25, hwnd, NULL, NULL, NULL);
        hAuthLogin = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 20, 150, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"STATIC", L"Пароль:", WS_VISIBLE | WS_CHILD, 20, 60, 60, 25, hwnd, NULL, NULL, NULL);
        hAuthPass = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 90, 60, 150, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Войти", WS_VISIBLE | WS_CHILD, 90, 110, 100, 35, hwnd, (HMENU)1, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Регистрация", WS_VISIBLE | WS_CHILD, 200, 110, 100, 35, hwnd, (HMENU)2, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wp) == 1) {
            wchar_t login[100], pass[100];
            GetWindowTextW(hAuthLogin, login, 100);
            GetWindowTextW(hAuthPass, pass, 100);
            if (wcscmp(login, L"client") == 0 && wcscmp(pass, L"123") == 0) {
                DestroyWindow(hwnd);
                ShowClientWindow();
            }
            else if (wcscmp(login, L"operator") == 0 && wcscmp(pass, L"123") == 0) {
                DestroyWindow(hwnd);
                ShowOperatorWindow();
            }
            else if (wcscmp(login, L"admin") == 0 && wcscmp(pass, L"123") == 0) {
                DestroyWindow(hwnd);
                ShowAdminWindow();
            }
            else {
                MessageBoxW(hwnd, L"Неверный логин или пароль!", L"Ошибка", MB_OK);
            }
        }
        if (LOWORD(wp) == 2) {
            DestroyWindow(hwnd);
            ShowRegWindow();
        }
        break;
    case WM_DESTROY: PostQuitMessage(0); break;
    default: return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}

// ==================== РЕГИСТРАЦИЯ ====================
LRESULT CALLBACK RegProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"STATIC", L"ФИО:", WS_VISIBLE | WS_CHILD, 20, 20, 60, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 20, 200, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"STATIC", L"Email:", WS_VISIBLE | WS_CHILD, 20, 55, 60, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 55, 200, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"STATIC", L"Логин:", WS_VISIBLE | WS_CHILD, 20, 90, 60, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 90, 200, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"STATIC", L"Пароль:", WS_VISIBLE | WS_CHILD, 20, 125, 60, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 90, 125, 200, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Зарегистрироваться", WS_VISIBLE | WS_CHILD, 90, 170, 160, 35, hwnd, (HMENU)1, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Назад", WS_VISIBLE | WS_CHILD, 260, 170, 80, 35, hwnd, (HMENU)2, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wp) == 1) {
            MessageBoxW(hwnd, L"Регистрация успешна!", L"Успех", MB_OK);
            DestroyWindow(hwnd);
            ShowWindowByClass(L"AuthApp", AuthProc, L"Авторизация", 350, 200);
        }
        if (LOWORD(wp) == 2) {
            DestroyWindow(hwnd);
            ShowWindowByClass(L"AuthApp", AuthProc, L"Авторизация", 350, 200);
        }
        break;
    case WM_DESTROY: PostQuitMessage(0); break;
    default: return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}

// ==================== КЛИЕНТ ====================
LRESULT CALLBACK ClientProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"STATIC", L"НОВАЯ ЗАЯВКА", WS_VISIBLE | WS_CHILD, 20, 20, 120, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"STATIC", L"Тема:", WS_VISIBLE | WS_CHILD, 20, 55, 50, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 80, 55, 200, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"STATIC", L"Описание:", WS_VISIBLE | WS_CHILD, 20, 90, 60, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 90, 190, 60, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Отправить", WS_VISIBLE | WS_CHILD, 90, 170, 100, 35, hwnd, (HMENU)1, NULL, NULL);
        CreateWindowW(L"STATIC", L"МОИ ЗАЯВКИ", WS_VISIBLE | WS_CHILD, 20, 230, 100, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"LISTBOX", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 260, 260, 100, hwnd, (HMENU)2, NULL, NULL);
        SendDlgItemMessageW(hwnd, 2, LB_ADDSTRING, 0, (LPARAM)L"101 | Не открывается сайт | В работе");
        SendDlgItemMessageW(hwnd, 2, LB_ADDSTRING, 0, (LPARAM)L"102 | Не приходит письмо | Закрыта");
        CreateWindowW(L"BUTTON", L"Выйти", WS_VISIBLE | WS_CHILD, 20, 380, 80, 35, hwnd, (HMENU)99, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wp) == 1) MessageBoxW(hwnd, L"Заявка отправлена!", L"Успех", MB_OK);
        if (LOWORD(wp) == 99) {
            DestroyWindow(hwnd);
            ShowWindowByClass(L"AuthApp", AuthProc, L"Авторизация", 350, 200);
        }
        break;
    case WM_DESTROY: PostQuitMessage(0); break;
    default: return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}

// ==================== ОПЕРАТОР ====================
LRESULT CALLBACK OperatorProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"STATIC", L"СПИСОК ЗАЯВОК", WS_VISIBLE | WS_CHILD, 20, 20, 120, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"LISTBOX", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 50, 250, 100, hwnd, (HMENU)1, NULL, NULL);
        SendDlgItemMessageW(hwnd, 1, LB_ADDSTRING, 0, (LPARAM)L"101 | Не открывается сайт | Высокий");
        SendDlgItemMessageW(hwnd, 1, LB_ADDSTRING, 0, (LPARAM)L"102 | Не приходит письмо | Средний");
        CreateWindowW(L"STATIC", L"ОТВЕТ КЛИЕНТУ", WS_VISIBLE | WS_CHILD, 20, 170, 120, 25, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 200, 250, 80, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Поиск в БЗ", WS_VISIBLE | WS_CHILD, 20, 300, 90, 35, hwnd, (HMENU)2, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Эскалировать", WS_VISIBLE | WS_CHILD, 120, 300, 90, 35, hwnd, (HMENU)3, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Закрыть", WS_VISIBLE | WS_CHILD, 220, 300, 70, 35, hwnd, (HMENU)4, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Выйти", WS_VISIBLE | WS_CHILD, 20, 360, 80, 35, hwnd, (HMENU)99, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wp) == 2) MessageBoxW(hwnd, L"Статья: Ошибка 500 - перезапуск сервера", L"База знаний", MB_OK);
        if (LOWORD(wp) == 3) MessageBoxW(hwnd, L"Заявка передана на вторую линию!", L"Эскалация", MB_OK);
        if (LOWORD(wp) == 4) MessageBoxW(hwnd, L"Заявка закрыта!", L"Успех", MB_OK);
        if (LOWORD(wp) == 99) {
            DestroyWindow(hwnd);
            ShowWindowByClass(L"AuthApp", AuthProc, L"Авторизация", 350, 200);
        }
        break;
    case WM_DESTROY: PostQuitMessage(0); break;
    default: return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}

// ==================== АДМИНИСТРАТОР ====================
LRESULT CALLBACK AdminProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"BUTTON", L"Пользователи", WS_VISIBLE | WS_CHILD, 20, 20, 100, 35, hwnd, (HMENU)1, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Заявки", WS_VISIBLE | WS_CHILD, 130, 20, 100, 35, hwnd, (HMENU)2, NULL, NULL);
        CreateWindowW(L"BUTTON", L"База знаний", WS_VISIBLE | WS_CHILD, 240, 20, 100, 35, hwnd, (HMENU)3, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Отчёты SLA", WS_VISIBLE | WS_CHILD, 350, 20, 100, 35, hwnd, (HMENU)4, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Работа с БД", WS_VISIBLE | WS_CHILD, 460, 20, 100, 35, hwnd, (HMENU)5, NULL, NULL);
        hList = CreateWindowW(L"LISTBOX", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 70, 560, 200, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Выйти", WS_VISIBLE | WS_CHILD, 20, 290, 80, 35, hwnd, (HMENU)99, NULL, NULL);
        RefreshList(hList);
        break;
    case WM_COMMAND:
        if (LOWORD(wp) == 1) { mode = 1; RefreshList(hList); SetWindowTextW(hwnd, L"Админ - Пользователи"); }
        if (LOWORD(wp) == 2) { mode = 2; RefreshList(hList); SetWindowTextW(hwnd, L"Админ - Заявки"); }
        if (LOWORD(wp) == 3) { mode = 3; RefreshList(hList); SetWindowTextW(hwnd, L"Админ - База знаний"); }
        if (LOWORD(wp) == 4) { MessageBoxW(hwnd, L"Всего заявок: 2\nРешено вовремя: 1", L"Отчёт SLA", MB_OK); }
        if (LOWORD(wp) == 5) { MessageBoxW(hwnd, L"Работа с БД (демонстрация)", L"БД", MB_OK); }
        if (LOWORD(wp) == 99) {
            DestroyWindow(hwnd);
            ShowWindowByClass(L"AuthApp", AuthProc, L"Авторизация", 350, 200);
        }
        break;
    case WM_DESTROY: PostQuitMessage(0); break;
    default: return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}

// ==================== ФУНКЦИИ ПОКАЗА ОКОН ====================
void ShowWindowByClass(LPCWSTR className, WNDPROC proc, LPCWSTR title, int w, int h) {
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = proc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = className;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassW(&wc);
    CreateWindowExW(0, className, title, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, wc.hInstance, NULL);
}

void ShowClientWindow() {
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = ClientProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"ClientApp";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassW(&wc);
    CreateWindowExW(0, L"ClientApp", L"Личный кабинет клиента", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 320, 450, NULL, NULL, wc.hInstance, NULL);
}

void ShowOperatorWindow() {
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = OperatorProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"OperatorApp";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassW(&wc);
    CreateWindowExW(0, L"OperatorApp", L"Рабочий стол оператора", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 350, 450, NULL, NULL, wc.hInstance, NULL);
}

void ShowAdminWindow() {
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = AdminProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"AdminApp";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassW(&wc);
    CreateWindowExW(0, L"AdminApp", L"Рабочий стол администратора", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 650, 400, NULL, NULL, wc.hInstance, NULL);
}

void ShowRegWindow() {
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = RegProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"RegApp";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassW(&wc);
    CreateWindowExW(0, L"RegApp", L"Регистрация", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 380, 260, NULL, NULL, wc.hInstance, NULL);
}

// ==================== ГЛАВНАЯ ФУНКЦИЯ ====================
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {
    ShowWindowByClass(L"AuthApp", AuthProc, L"Авторизация", 350, 200);
    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}