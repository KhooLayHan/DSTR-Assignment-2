#pragma once 

#include <iomanip>
#include <random>
#include <sstream>
#include <string>

namespace TCMS
{
    class UUID {
    public:
        UUID() {
            m_UUID = generateUUID();
        }

        explicit UUID(const std::string& uuid) : m_UUID(uuid) {

        }

        std::string toString() const {
            return m_UUID;
        }

        bool operator==(const UUID& other) const {
            return m_UUID == other.m_UUID;
        }
    private:
        std::string m_UUID;

        static std::string generateUUID() {
            static std::random_device random_number;
            static std::mt19937 generateRandomNumber(random_number());

            static std::uniform_int_distribution<int32_t> distribution(0, 15);

            std::stringstream string_stream;

            for (int32_t i = 0; i < 32; ++i) {
                int32_t value = distribution(generateRandomNumber);
                string_stream << std::hex << value;

                if (i == 7 || i == 11 || i == 15 || i == 19)
                    string_stream << "-";
            }

            return string_stream.str();
        };
    };
} // namespace TCMS
