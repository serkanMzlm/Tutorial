#include <iostream>
#include <ctime>

int main() {
    // Şu anki zaman bilgisini almak için time_t kullanıyoruz
    std::time_t currentTime = std::time(nullptr);

    // Zamanı yerel zamana çeviriyoruz
    std::tm* localTime = std::localtime(&currentTime);

    // Tarih ve saat bilgisini ekrana basıyoruz
    std::cout << "Current Date and Time: "
              << (localTime->tm_year + 1900) << '-'  // Yıl, 1900'den itibaren sayılır
              << (localTime->tm_mon + 1) << '-'      // Ay, 0'dan itibaren sayılır
              << localTime->tm_mday << ' '           // Gün
              << localTime->tm_hour << ':'           // Saat
              << localTime->tm_min << ':'            // Dakika
              << localTime->tm_sec << std::endl;     // Saniye

    return 0;
}
