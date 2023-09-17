Bu projemizde yaptığımız kütüphaneleri /usr/local içerisinde belirli bölümlere kopyalayıp diğer projelerimizde çalışmasını sağlıyoruz.

```
make
sudo make install  
```

Not: "Sudo make install" olmadan cmake'de belirttiğimiz kurulum parçaları çalışmayacaktır. Bu örnekte sudo kullanmamızın sebebi kurulum yapacağımız yerin izin gerektirmesidir.

sürekli kullandığımız paketleri `/usr/local/` dizinine kurabiliriz

Başlık Dosyaları: /usr/local/include/<package_name>

Hedefler: /usr/local/lib/<paket_adı>
