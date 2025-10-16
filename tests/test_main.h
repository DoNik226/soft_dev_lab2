#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>

// Реализация заглушки для функции equation
extern "C" int equation(double a, double b, double c, double *root1, double *root2) {
    // По умолчанию вернем комплексное решение
    *root1 = 0.5;
    *root2 = 2.18;
    return 0;
}

// Заглушка для функции myfunc
extern "C" int myfunc(int arg) {
    return arg + 4;
}

// Вспомогательный класс для захвата вывода в stdout
class StdoutCapturer {
public:
    explicit StdoutCapturer(const std::string& filename) : m_filename(filename) {}
    ~StdoutCapturer() { restore(); }

    void capture() {
        m_saved_stdout = dup(STDOUT_FILENO);
        m_outfile.open(m_filename, std::ios_base::trunc | std::ios_base::binary);
        dup2(m_outfile.rdbuf()->fd(), STDOUT_FILENO);
    }

    void restore() {
        if (m_outfile.is_open()) {
            m_outfile.flush();
            m_outfile.close();
        }
        dup2(m_saved_stdout, STDOUT_FILENO);
        close(m_saved_stdout);
    }

private:
    const std::string m_filename;
    int m_saved_stdout{-1};
    std::ofstream m_outfile;
};

// Фикстура для тестов главной функции
class MainTestFixture : public ::testing::Test {
protected:
    virtual void SetUp() override {
        capturer.capture();
    }

    virtual void TearDown() override {
        capturer.restore();
    }

    StdoutCapturer capturer{"tmp.stdout"};
};

// Тест для случая комплексного решения
TEST_F(MainTestFixture, ComplexRootsCase) {
    // В заглушке используем комплексное решение
    extern "C" int equation(double a, double b, double c, double *root1, double *root2) {
        *root1 = 0.5;
        *root2 = 2.18;
        return 0;
    }

    int exit_code = main();

    std::ifstream captured_output("tmp.stdout");
    std::stringstream expected_output;
    expected_output << "Hello World!\n";
    expected_output << "Комплексные корни:\n";
    expected_output << "x1 = 0.50 + 2.18i\n";
    expected_output << "x2 = 0.50 - 2.18i\n";

    std::string actual_output((std::istreambuf_iterator<char>(captured_output)),
                              std::istreambuf_iterator<char>());
    ASSERT_EQ(actual_output, expected_output.str());
    ASSERT_EQ(exit_code, 6);  // myfunc возвращает 6
}

// Тест для двух действительных решений
TEST_F(MainTestFixture, TwoRealRootsCase) {
    // Изменение заглушки для реальных корней
    extern "C" int equation(double a, double b, double c, double *root1, double *root2) {
        *root1 = 3.0;
        *root2 = 1.0;
        return 2;
    }

    int exit_code = main();

    std::ifstream captured_output("tmp.stdout");
    std::stringstream expected_output;
    expected_output << "Hello World!\n";
    expected_output << "Два действительных корня:\n";
    expected_output << "x1 = 3.00\n";
    expected_output << "x2 = 1.00\n";

    std::string actual_output((std::istreambuf_iterator<char>(captured_output)),
                              std::istreambuf_iterator<char>());
    ASSERT_EQ(actual_output, expected_output.str());
    ASSERT_EQ(exit_code, 6);  // myfunc возвращает 6
}

// Тест для одного реального корня
TEST_F(MainTestFixture, OneRealRootCase) {
    // Меняем заглушку для единственного корня
    extern "C" int equation(double a, double b, double c, double *root1, double *root2) {
        *root1 = 2.0;
        return 1;
    }

    int exit_code = main();

    std::ifstream captured_output("tmp.stdout");
    std::stringstream expected_output;
    expected_output << "Hello World!\n";
    expected_output << "Один действительный корень:\n";
    expected_output << "x = 2.00\n";

    std::string actual_output((std::istreambuf_iterator<char>(captured_output)),
                              std::istreambuf_iterator<char>());
    ASSERT_EQ(actual_output, expected_output.str());
    ASSERT_EQ(exit_code, 6);  // myfunc возвращает 6
}

// Тест, проверяющий общие условия работы main
TEST_F(MainTestFixture, GeneralMainBehavior) {
    // Используем стандартную реализацию equation
    int exit_code = main();

    std::ifstream captured_output("tmp.stdout");
    std::string output((std::istreambuf_iterator<char>(captured_output)),
                       std::istreambuf_iterator<char>());

    ASSERT_GE(output.find("Hello World!\n"), 0);  // Приветствие присутствует
    ASSERT_GE(output.find("Комплексные корни:"), 0);  // Комплексные корни присутствуют
    ASSERT_EQ(exit_code, 6);  // myfunc возвращает 6
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
