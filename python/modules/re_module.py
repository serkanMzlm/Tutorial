import re # düzenli ifadelerin bulundugu modül
metin = "01: Adana 02: Adıyaman 03: Afyon "


nesne = re.match("01",metin) #match fonksiyonu arama yapar sadece en başta bulunan kısma bakar
print (nesne)
if nesne: #nesne bir şey var mı yok mu kontrol ediyoruz
    print (nesne.group()) # match gösterir search ortaktır
    print (nesne.span()) # span dösterir     "       "


nesne2 = re.search("Adana",metin) #match farkı metnin tamamında arama yapar
print (nesne2)


nesne3 = re.findall("a",metin) # aradığımız kelimenin kaç defa geçiyorsa hepsini bize liste verir
print (nesne3)


metin = "1FF ff4 sdfg 55f 3343 fghd"

nesne = re.search("\s\d+\w",metin) # \s bir boluk tutar \d bir sayı + 0 veya daha fazla sayı olabilir w ise alfanümerik
print(nesne.group())