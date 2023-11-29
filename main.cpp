// Галкина Таисия Олеговна БПИ213
// среда разработки - Clion
// реализовано все из обязательного + Z-функция
// Хорошего дня!)

#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <fstream>

// кмп с уточненными гранями
long double thirdAlgo(std::string text, std::string str) {
    auto start = std::chrono::high_resolution_clock::now();

    std::string s3 = str;
    str += '#';
    std::vector<size_t> br(str.size());
    std::vector<size_t> brs(str.size());
    br[0] = 0;
    brs[0] = 0;
    size_t k = 0;
    for (size_t i = 1; i < str.size(); i++) {
        while (k > 0 && (str[k] == '?' || str[k] != str[i])) {
            k = br[k - 1];
        }
        if (str[k] == str[i] || str[k] == '?') {
            k = k + 1;
        }
        br[i] = k;
        if ((str[br[i - 1]] == '?' || str[br[i - 1]] != str[i]) &&
            (str[br[i - 1] + 1] == '*' || str[br[i - 1] + 1] != str[i + 1])) {
            brs[i] = br[i];
        } else {
            brs[i] = brs[br[i]];
        }
    }
    std::vector<size_t> ans;
    k = 0;
    for (size_t i = 0; i < text.size(); i++) {
        while ((k > 0) && (s3[k] == '?' || s3[k] != text[i])) {
            k = brs[k - 1];
        }
        if (s3[k] == text[i] || s3[k] == '?') {
            k = k + 1;
        }
        if (k == s3.size()) {
            ans.push_back(i - s3.size() + 1);
            k = brs[s3.size() - 1];
        }
    }
    auto end = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
}

// помощь для кмп обычного (вычисление префикс функции)
std::vector<int> compute_prefix(std::string pattern) {
    int m = pattern.size();
    std::vector<int> prefix(m);
    prefix[0] = 0;
    int k = 0;
    for (int i = 1; i < m; i++) {
        while (k > 0 && (pattern[k] != pattern[i] && pattern[k] != '?')) {
            k = prefix[k - 1];
        }
        if (pattern[k] == pattern[i] || pattern[k] == '?') {
            k++;
        }
        prefix[i] = k;
    }
    return prefix;
}

// обычное КМП
long double secondAlgo(std::string text, std::string pattern) {
    auto start = std::chrono::high_resolution_clock::now();
    int n = text.size();
    int m = pattern.size();
    std::vector<int> prefix = compute_prefix(pattern);
    std::vector<size_t> ans;
    int k = 0;
    int anss = -1;
    for (int i = 0; i < n; i++) {
        while (k > 0 && (pattern[k] != text[i] && pattern[k] != '?')) {
            k = prefix[k - 1];
        }
        if (pattern[k] == text[i] || pattern[k] == '?') {
            k++;
        }
        if (k == m) {
            ans.push_back(i - m + 1);
            k = prefix[k - 1];
            anss = i - m + 1;
        }
    }
    auto end = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
}


// наивная реализация - посимвольное сравнение
long double firstAlgo(std::string text, std::string pattern) {
    auto start = std::chrono::high_resolution_clock::now();
    int n = text.size();
    int m = pattern.size();
    std::vector<size_t> ans;
    int anss = -1;
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j] && pattern[j] != '?') {
                break;
            }
        }
        if (j == m) {
            ans.push_back(i);
            anss = i;
        }
    }
    auto end = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
}

// вычисление Zфункции
std::vector<int> z_function(std::string s) {
    int n = s.length();
    std::vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && (s[z[i]] == s[i + z[i]] || s[z[i]] == '?' || s[i + z[i]] == '?')) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

// сам 4ый алгоритм
long double forthAlgo(std::string s2, std::string s1) {
    auto start = std::chrono::high_resolution_clock::now();
    std::string combined = s1 + '#' + s2;
    std::vector<int> z = z_function(combined);
    auto end = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
}

// создаем строку из 2 букв
std::string get_two_str(int len) {
    std::string str;
    srand(time(nullptr));

    for (int i = 0; i < len; i++) {
        int r = rand() % 2;
        if (r == 0) {
            str.push_back('a');
        } else {
            str.push_back('b');
        }
    }
    return str;
}

// создаем строку из 4 букв
std::string get_four_str(int len) {
    std::string str;
    srand(time(nullptr));

    for (int i = 0; i < len; i++) {
        int r = rand() % 4;
        if (r == 0) {
            str.push_back('a');
        } else if (r == 1) {
            str.push_back('b');
        } else if (r == 2) {
            str.push_back('c');
        } else {
            str.push_back('d');
        }
    }
    return str;
}

// вставляем вопросы в рандомные места
void insert_questions(std::string &s, int count) {
    srand(time(nullptr));
    for (auto i = 0; i < count; i++) {
        int r = rand() % s.size();
        s[r] = '?';
    }
}

// получаем подстроку из строки
std::string get_str(std::string &s, int len) {
    srand(time(nullptr));
    int beg = rand() % (s.size() - len);
    std::string ans = s.substr(beg, len);
    return ans;
}

// вектора с ответами по времени
std::vector<long long> two_zero_q_10000;
std::vector<long long> two_one_q_10000;
std::vector<long long> two_two_q_10000;
std::vector<long long> two_three_q_10000;
std::vector<long long> two_four_q_10000;

std::vector<long long> four_zero_q_10000;
std::vector<long long> four_one_q_10000;
std::vector<long long> four_two_q_10000;
std::vector<long long> four_three_q_10000;
std::vector<long long> four_four_q_10000;

std::vector<long long> two_zero_q_100000;
std::vector<long long> two_one_q_100000;
std::vector<long long> two_two_q_100000;
std::vector<long long> two_three_q_100000;
std::vector<long long> two_four_q_100000;

std::vector<long long> four_zero_q_100000;
std::vector<long long> four_one_q_100000;
std::vector<long long> four_two_q_100000;
std::vector<long long> four_three_q_100000;
std::vector<long long> four_four_q_100000;

// тут запускаются алгоритмы для двух строк
long long algo_runner(int fl, std::string text, std::string str, int cnt, int sz) {
    long long summ = 0;
    if (fl == 0) {
        for (int i = 0; i < 50; i++) {
            summ += firstAlgo(text, str);
        }
    } else if (fl == 1) {
        for (int i = 0; i < 50; i++) {
            summ += secondAlgo(text, str);
        }
    } else if (fl == 2) {
        for (int i = 0; i < 50; i++) {
            summ += thirdAlgo(text, str);
        }
    } else if (fl == 3) {
        for (int i = 0; i < 50; i++) {
            summ += forthAlgo(text, str);
        }
    }
    summ /= 50;
    if (text.size() == 10000) {
        if (sz == 2) {
            if (cnt == 0) {
                two_zero_q_10000.push_back(summ);
            } else if (cnt == 1) {
                two_one_q_10000.push_back(summ);
            } else if (cnt == 2) {
                two_two_q_10000.push_back(summ);
            } else if (cnt == 3) {
                two_three_q_10000.push_back(summ);
            } else if (cnt == 4) {
                two_four_q_10000.push_back(summ);
            }
        } else {
            if (sz == 4) {
                if (cnt == 0) {
                    four_zero_q_10000.push_back(summ);
                } else if (cnt == 1) {
                    four_one_q_10000.push_back(summ);
                } else if (cnt == 2) {
                    four_two_q_10000.push_back(summ);
                } else if (cnt == 3) {
                    four_three_q_10000.push_back(summ);
                } else if (cnt == 4) {
                    four_four_q_10000.push_back(summ);
                }
            }
        }
    } else {
        if (sz == 2) {
            if (cnt == 0) {
                two_zero_q_100000.push_back(summ);
            } else if (cnt == 1) {
                two_one_q_100000.push_back(summ);
            } else if (cnt == 2) {
                two_two_q_100000.push_back(summ);
            } else if (cnt == 3) {
                two_three_q_100000.push_back(summ);
            } else if (cnt == 4) {
                two_four_q_100000.push_back(summ);
            }
        } else {
            if (sz == 4) {
                if (cnt == 0) {
                    four_zero_q_100000.push_back(summ);
                } else if (cnt == 1) {
                    four_one_q_100000.push_back(summ);
                } else if (cnt == 2) {
                    four_two_q_100000.push_back(summ);
                } else if (cnt == 3) {
                    four_three_q_100000.push_back(summ);
                } else if (cnt == 4) {
                    four_four_q_100000.push_back(summ);
                }
            }
        }
    }
    return summ;
}

// тут запись ответов в файлы
void write_in_file(std::string name, int fl) {
    std::vector<long long> times;
    if (fl == 0) {
        times = two_zero_q_10000;
    } else if (fl == 1) {
        times = two_one_q_10000;
    } else if (fl == 2) {
        times = two_two_q_10000;
    } else if (fl == 3) {
        times = two_three_q_10000;
    } else if (fl == 4) {
        times = two_four_q_10000;
    } else if (fl == 5) {
        times = four_zero_q_10000;
    } else if (fl == 6) {
        times = four_one_q_10000;
    } else if (fl == 7) {
        times = four_two_q_10000;
    } else if (fl == 8) {
        times = four_three_q_10000;
    } else if (fl == 9) {
        times = four_four_q_10000;
    } else if (fl == 10) {
        times = two_zero_q_100000;
    } else if (fl == 11) {
        times = two_one_q_100000;
    } else if (fl == 12) {
        times = two_two_q_100000;
    } else if (fl == 13) {
        times = two_three_q_100000;
    } else if (fl == 14) {
        times = two_four_q_100000;
    } else if (fl == 15) {
        times = four_zero_q_100000;
    } else if (fl == 16) {
        times = four_one_q_100000;
    } else if (fl == 17) {
        times = four_two_q_100000;
    } else if (fl == 18) {
        times = four_three_q_100000;
    } else if (fl == 19) {
        times = four_four_q_100000;
    }
    std::ofstream file;
    file.open(name);
    for (int i = 0; i < times.size(); i++) {
        if (i % 4 == 3) {
            file << times[i] << ";" << "\n";
        } else {
            file << times[i] << ";";
        }
    }
    file.close();
}

// главный ранер где все и запускается
void runner() {
    std::string s1, s2;
    s2 = get_two_str(10000);
    for (int i = 100; i <= 3000; i += 100) {
        s1 = get_str(s2, i);
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 5; k++) {
                std::string s3 = s1;
                insert_questions(s3, k);
                algo_runner(j, s2, s3, k, 2);
                //std::cout << i << ' ' << algo_runner(j, s2, s3, k, 2) << ' ' << s2  << ' '<< s3<< '\n';
            }
        }
    }
    s2 = get_four_str(10000);
    for (int i = 100; i <= 3000; i += 100) {
        s1 = get_str(s2, i);
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 5; k++) {
                std::string s3 = s1;
                insert_questions(s3, k);
                algo_runner(j, s2, s3, k, 4);
                // std::cout << i << ' ' << algo_runner(j, s2, s3, k, 4) << ' ' << s2  << ' '<< s3<< '\n';
            }
        }
    }
    s2 = get_two_str(100000);
    for (int i = 100; i <= 3000; i += 100) {
        s1 = get_str(s2, i);
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 5; k++) {
                std::string s3 = s1;
                insert_questions(s3, k);
                algo_runner(j, s2, s3, k, 2);
                // std::cout << i << ' ' << algo_runner(j, s2, s3, k, 2) << ' ' << s2  << ' '<< s3<< '\n';
            }
        }
    }
    s2 = get_four_str(100000);
    for (int i = 100; i <= 3000; i += 100) {
        s1 = get_str(s2, i);
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 5; k++) {
                std::string s3 = s1;
                insert_questions(s3, k);
                algo_runner(j, s2, s3, k, 4);
                // std::cout << i << ' ' << algo_runner(j, s2, s3, k, 4) << ' ' << s2  << ' '<< s3<< '\n';
            }
        }
    }
    write_in_file("time_for_10000_two_zero_q.csv", 0);
    write_in_file("time_for_10000_two_one_q.csv", 1);
    write_in_file("time_for_10000_two_two_q.csv", 2);
    write_in_file("time_for_10000_two_three_q.csv", 3);
    write_in_file("time_for_10000_two_four_q.csv", 4);
    write_in_file("time_for_10000_four_zero_q.csv", 5);
    write_in_file("time_for_10000_four_one_q.csv", 6);
    write_in_file("time_for_10000_four_two_q.csv", 7);
    write_in_file("time_for_10000_four_three_q.csv", 8);
    write_in_file("time_for_10000_four_four_q.csv", 9);
    write_in_file("time_for_100000_two_zero_q.csv", 10);
    write_in_file("time_for_100000_two_one_q.csv", 11);
    write_in_file("time_for_100000_two_two_q.csv", 12);
    write_in_file("time_for_100000_two_three_q.csv", 13);
    write_in_file("time_for_100000_two_four_q.csv", 14);
    write_in_file("time_for_100000_four_zero_q.csv", 15);
    write_in_file("time_for_100000_four_one_q.csv", 16);
    write_in_file("time_for_100000_four_two_q.csv", 17);
    write_in_file("time_for_100000_four_three_q.csv", 18);
    write_in_file("time_for_100000_four_four_q.csv", 19);
}

// просто мейн
int main() {
    runner();
    return 0;
}
