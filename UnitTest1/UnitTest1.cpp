#include "pch.h"
#include "CppUnitTest.h"
#include "../11.3 ЦЕЙ/11.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const std::string testFile = "testFile.dat";
            Product testProduct1 = { "TestProduct1", 50.0, 5, "кг" };
            Product testProduct2 = { "TestProduct2", 75.0, 7, "л" };

            std::ofstream outFile(testFile, std::ios::binary | std::ios::trunc);
            outFile.write(reinterpret_cast<char*>(&testProduct1), sizeof(Product));
            outFile.write(reinterpret_cast<char*>(&testProduct2), sizeof(Product));
            outFile.close();

            std::ifstream inFile(testFile, std::ios::binary);
            Assert::IsTrue(inFile.is_open(), L"Файл не відкрився для пошуку!");

            Product product;
            bool found = false;
            while (inFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
                if (std::string(product.name) == "TestProduct2") {
                    found = true;
                    break;
                }
            }
		}
	};
}
