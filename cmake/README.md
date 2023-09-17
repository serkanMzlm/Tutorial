## CMAKE Komutları
- `cmake_minimum_required(VERSION {cmake version})` : CMake dosyasının çalışabilmesi için işletim sisteminde kullanılacak minimum cmake sürümü belirlenir. Belirtilen sürümün altında bir sürüm mevcut ise hata verir.

- `project({project_name} LANGUAGES {project_lang} VERSION {project_ver})` : CMake projesine bir isim verilir. Ayrıca projede kullanılan diller ve proje versiyonu isteğe göre ayarlanabilmektedir.

- `add_executable({exe_name} {files})` : Derlenmesini istediğimiz dosyaları ayarlıyoruz ve ilk parametrede çalıştırılabilir dosyanın adını belirtiyoruz.

- ``