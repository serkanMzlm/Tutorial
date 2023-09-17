## CMAKE Komutları
- `cmake_minimum_required(VERSION {cmake version})` : CMake dosyasının çalışabilmesi için işletim sisteminde kullanılacak minimum cmake sürümü belirlenir. Belirtilen sürümün altında bir sürüm mevcut ise hata verir.

- `project({project_name} LANGUAGES {project_lang} VERSION {project_ver})` : CMake projesine bir isim verilir. Ayrıca projede kullanılan diller ve proje versiyonu isteğe göre ayarlanabilmektedir.

- `add_executable({exe_name} {files})` : Derlenmesini istediğimiz dosyaları ayarlıyoruz ve ilk parametrede çalıştırılabilir dosyanın adını belirtiyoruz.

- `add_library({lib_name}  {lib_files})` : Tüm dosyaları add_executable ile derlemek büyük projelerde sorunlara neden olabilir, bu nedenle kütüphaneleri ana dosyamızdan ayrı olarak derlemek için add_library kullanıyoruz.

- `target_link_libraries({exe_name} PRIVATE {lib_1} {lib_2})` : add_library'yi add_executable'a bağlarız. Bu bölümde PUBLIC veya PRIVATE anahtar kelimeleri kullanılabilir. (default: PUBLIC)
  - **PUBLIC:** exe_name'min aldığı lib_1 ve lib_2'nin başka dosyalara aktarılmasına izin verir.
  - **PRIVATE:** exe_name'min aldığı lib_1 ve lib_2'nin başka dosyalara aktarılmasını engeler.