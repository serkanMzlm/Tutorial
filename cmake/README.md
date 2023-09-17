## CMAKE Komutları
- `cmake_minimum_required(VERSION {cmake version})` : CMake dosyasının çalışabilmesi için işletim sisteminde kullanılacak minimum cmake sürümü belirlenir. Belirtilen sürümün altında bir sürüm mevcut ise hata verir.

- `project({project_name} LANGUAGES {project_lang} VERSION {project_ver})` : CMake projesine bir isim verilir. Ayrıca projede kullanılan diller ve proje versiyonu isteğe göre ayarlanabilmektedir.

- `add_executable({exe_name} {files})` : Derlenmesini istediğimiz dosyaları ayarlıyoruz ve ilk parametrede çalıştırılabilir dosyanın adını belirtiyoruz.

- `add_library({lib_name}  {lib_files})` : Tüm dosyaları add_executable ile derlemek büyük projelerde sorunlara neden olabilir, bu nedenle kütüphaneleri ana dosyamızdan ayrı olarak derlemek için add_library kullanıyoruz.

- `target_link_libraries({exe_name} PRIVATE {lib_1} {lib_2})` : add_library'yi add_executable'a bağlarız. Bu bölümde PUBLIC veya PRIVATE anahtar kelimeleri kullanılabilir. (default: PUBLIC)
  - **PUBLIC:** exe_name'min aldığı lib_1 ve lib_2'nin başka dosyalara aktarılmasına izin verir.
  - **PRIVATE:** exe_name'min aldığı lib_1 ve lib_2'nin başka dosyalara aktarılmasını engeler.

- `add_subdirectory({add_dir}):` Dizinler arasında geçiş yapmanızı sağlar. Cmake dosyasını geçerli dizinde çalıştırır ve eski cmake dosyasına geri döner. CMake dosyası belirtilen dizinde olmalıdır.

- `target_include_directories({lib_name} PUBLIC ${PROJECT_SOURCE_DIR}/inc)`: .h dosyalarının bulunduğu dizini belirtir. PUBLIC , PRIVATE , INTERFACE gibi anahtar kelimeler kullanılabilir. <u>PROJECT_SOURCE_DIR</u> (proje dizini)
  - PUBLIC : Hem yürütülebilir dosyada hem de kütüphanede kullanılıyorsa
  - PRIVATE : Yalnızca kütüphanede kullanılıyorsa
  - INTERFACE: Kütüphanede kullanılmıyor ancak çalıştırılabilir dosyada kullanılıyorsa

- `set({varvariable_name} {variable1} {variable2} ...)` : Bir cmake değişkeni oluşturur. "\${}" cmake değişkeninde bulunan değere erişmek için kullanılır. `"` ile işaretleme zorunluluğu yoktur. `"` atlanırsa her boşluk bir sonraki dizi elemanına geçer. Eğer değişkenler çağrılırken "\${}" içinde belirtilirse, değişkenin içinde bir dizi varsa hepsi bitişik olarak yazılacaktır. yalnızca ${} ile çağrılırsa diziler arasında `;` olarak ayrılmıştır. Ayarlarken boşluk yerine ";" aynı anlam kullanılabilir.
  - set(number 1 2 3) = set(number 1;2;3)
  - set(name "aa;bb;cc") = set(name aa bb cc)

- `unset({variable})`: Değişkeni tanımsız yapar.

- `message()`: Ekrana çıkış verilemsini sağlar. Çıkış türü belirlenebilir
  - message(STATUS "Cmake File Status Worked...")
  - message(DEBUG "Cmake File Debug Worked...")
  - message(WARNING "Cmake File WARNING Worked...")
  - message(FATAL ERROR "Cmake File FATAL ERROR Worked...")
  - message("Cmake File Worked...") 

---
Cmake dosyasını çıktı olmadan çalıştırmak için alta bulunan komutunu çalıştırın.
```
cmake -P CmakeLists.txt
```
---
- `list(param1 param2 ...)`: 
  - param1 listesi ne yapılacağını belirtir.
      - APPEND
      - REMOVE_AT
      - REMOVE_ITEM
      - REMOVE_DUPLICATES
      - SORT
      - INSERT
      - REVERSE
      - LENGTH
      - GET
      - SUBLIST
      - JOIN
      - FIND
  - param2 listenin adıdır
  - Eklenecek diğer parametreler param1'e bağlıdır.
- `string(param1 param2 ... param_out)`: 
  - param1 ne yapılacağını belirler
      - FIND
      - REPLACE
      - PREPEND
      - APPEND
      - TOLOWER
      - TOUPPER
      - LENGTH
  - param2 dize ifadesidir
  - son parametre çıktıyı tutan değişkendir (param_out)

- `if-elseif-endif` ​​"1, TRUE, Y, YES, a non-zero number" değerleri koşulun doğru olmasını sağlar. ​​"0, OFF, NO , FALSE, N, IGNORE, NOTFOUND, the empty string" değerleri koşulun yanlış olmasını sağlar.
  - DEFINED Değişkenin tanımlı olup olmadığı kontrol edilir.
  - COMMAND Komutun mevcut olup olmadığını kontrol edin
  - EXISTS  Belirtilen lokasyonda dosyanın bulunup bulunmadığı kontrol edilir.
  - NOT
  - AND
  - OR
  - STRLESS
  - STRGREATER
  - STREQUAL

- `while()`: belirtilen koşul doğru olduğu sürece döngünün içinde kalır

- `foreach()`: İçerisindeki liste elemanlarını tek tek alır ve belirtilen değişkene atar. Liste bitene kadar döngüde kalır.

```
foreach(x RANGE 10)  start
foreach(x RANGE 10 20)  start, end
foreach(x RANGE 10 20 5) start, end, increment amount
```

- `function(func_name , fanc_args)`: Fonksiyon içerisinde global değişkenin değerini değiştirsek bile bu değer global alanda değil sadece local kısımda değişir. (bu olay add_subdirectory'de geçerlidir) global alandaki değeri değiştirmek için "PARENT_SCOPE" anahtar kelimesi kullanılır. PARENT_SCOPE işlevin içindeki değişkeni değil, işlevin dışındaki değişkeni değiştirir.
  - ARGC kaç tane argüman girildi
  - ARGV tüm argümanları içeren bir liste
  - ARGN Fonksiyonun parametre olarak aldığı değerlerin dışındaki değerleri alır
  - ARGn n yerine koyduğumuz sayı belirtilen sırada ki argümanın alınmasını sağlar.

- `macro(func_name , fanc_args)`: Fonksiyonda her şey aynı sayılır, fonksiyonlar makroya dönüştürülürse kod hatasız çalışacaktır. Aralarındaki fark, bir global değişkenin değeri makro fonksiyonun içinde değiştiğinde, bunun doğrudan etkisinin dışarıdaki değişken üzerinde olmasıdır. (PARENT_SCOPE kullanmaya gerek yok)

- `cache variable`: Bir değişkeni önbellek değişkeni olarak tanımlamak, o değişkenin değerinin her seferinde yeniden hesaplanmasını  engeler. Bu özellik, projenin inşa sürecinin her seferinde tekrarlanan ve zaman alan süreçlerini optimize etmeye yardımcı olabilir. 
  - Bu sayede inşaat sürecinde tekrar eden süreçler en aza indirilir ve hızlandırılır.
  - Derleme klasöründe bulunan CMakeCache.txt dosyasına kaydedilir.
  -Belirttiğimiz değişkeni başka bir yere koysak bile önbellek değişmeyecek, sabit kalacaktır. -D parametresini değiştirmek veya `cmake -Dvariable` değiştirmek için "FORCE" kullanılmalıdır.

- `EVN`: Bir ortam değişkenine erişmek, onu değiştirmek vb. istiyorsak kullanılır. 
